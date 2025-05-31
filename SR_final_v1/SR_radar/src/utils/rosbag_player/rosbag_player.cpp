#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/detail/image__struct.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/u_int16.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <rosbag2_cpp/reader.hpp>
#include <rosbag2_cpp/readers/sequential_reader.hpp>
#include <rosbag2_storage/serialized_bag_message.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <vision_interface/msg/match_info.hpp>
#include <radar_interface/msg/game_robot_hp.hpp>
#include <radar_interface/msg/radar_info.hpp>
#include <radar_interface/msg/radar_mark_data.hpp>
#include <thread>
#include <unordered_map>
#include <functional>

using namespace std::chrono_literals;

void on_exit([[maybe_unused]] int sig) {
    RCUTILS_LOG_INFO("Exit by Ctrl+C");
    rclcpp::shutdown();
    exit(0);
}

class RosbagPlayer : public rclcpp::Node {
public:
    RosbagPlayer(const rclcpp::NodeOptions & options)
        : Node("rosbag_player_node", options) {
        RCLCPP_INFO(this->get_logger(), "Starting RosbagPlayer node");
        
        this->declare_parameter<std::string>("rosbag_file", "");
        this->declare_parameter<bool>("use_original_timestamps", true);
        this->declare_parameter<double>("playback_rate", 1.0);
        
        this->get_parameter("rosbag_file", rosbag_file);
        this->get_parameter("use_original_timestamps", use_original_timestamps_);
        this->get_parameter("playback_rate", playback_rate_);
        
        RCLCPP_INFO(this->get_logger(), "Rosbag file: %s", rosbag_file.c_str());
        RCLCPP_INFO(this->get_logger(), "Use original timestamps: %s", use_original_timestamps_ ? "true" : "false");
        RCLCPP_INFO(this->get_logger(), "Playback rate: %.2f", playback_rate_);

        // 创建所有需要的发布器
        image_publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/camera_image", rclcpp::SensorDataQoS());
        judge_color_publisher_ = this->create_publisher<std_msgs::msg::Bool>("/judge/color", 10);
        judge_remain_time_publisher_ = this->create_publisher<std_msgs::msg::UInt16>("/judge/remain_time", 10);
        judge_game_robot_hp_publisher_ = this->create_publisher<radar_interface::msg::GameRobotHP>("/judge/game_robot_hp", 10);
        judge_radar_cmd_publisher_ = this->create_publisher<std_msgs::msg::UInt8>("/judge/radar_cmd", 10);
        judge_radar_info_publisher_ = this->create_publisher<radar_interface::msg::RadarInfo>("/judge/radar_info", 10);
        judge_radar_mark_data_publisher_ = this->create_publisher<radar_interface::msg::RadarMarkData>("/judge/radar_mark_data", 10);
        
        // 初始化消息处理器映射
        init_message_handlers();

        signal(SIGINT, on_exit);
        
        // 创建一个新的线程来处理bag文件
        RCLCPP_INFO(this->get_logger(), "Opening rosbag file...");
        reader_.open(rosbag_file);
        RCLCPP_INFO(this->get_logger(), "Rosbag file opened successfully");
        
        processing_thread_ = std::make_shared<std::thread>(&RosbagPlayer::play_bag, this);
        RCLCPP_INFO(this->get_logger(), "RosbagPlayer initialized");
    }

    ~RosbagPlayer() {
        if (processing_thread_ && processing_thread_->joinable()) {
            processing_thread_->join();
        }
    }

private:
    void init_message_handlers() {
        // 为每个话题设置消息处理函数
        message_handlers_["/camera_image"] = [this](auto bag_message, auto ros_time) {
            handle_image_message(bag_message, ros_time);
        };
        
        message_handlers_["/judge/color"] = [this](auto bag_message, auto ros_time) {
            handle_bool_message(bag_message, ros_time, judge_color_publisher_);
        };
        
        message_handlers_["/judge/remain_time"] = [this](auto bag_message, auto ros_time) {
            handle_uint16_message(bag_message, ros_time);
        };
        
        message_handlers_["/judge/game_robot_hp"] = [this](auto bag_message, auto ros_time) {
            handle_game_robot_hp_message(bag_message, ros_time);
        };
        
        message_handlers_["/judge/radar_cmd"] = [this](auto bag_message, auto ros_time) {
            handle_uint8_message(bag_message, ros_time);
        };
        
        message_handlers_["/judge/radar_info"] = [this](auto bag_message, auto ros_time) {
            handle_radar_info_message(bag_message, ros_time);
        };
        
        message_handlers_["/judge/radar_mark_data"] = [this](auto bag_message, auto ros_time) {
            handle_radar_mark_data_message(bag_message, ros_time);
        };
    }
    
    void handle_image_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
        auto image_msg = std::make_shared<sensor_msgs::msg::Image>();
        rclcpp::Serialization<sensor_msgs::msg::Image> serialization;
        rclcpp::SerializedMessage serialized_msg(*bag_message->serialized_data);
        serialization.deserialize_message(&serialized_msg, image_msg.get());
        
        if (!use_original_timestamps_) {
            image_msg->header.stamp = ros_time;
        }
        
        image_publisher_->publish(*image_msg);
        RCLCPP_DEBUG(this->get_logger(), "Published image message");
    }
    
    void handle_bool_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time, 
                            rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher) {
        auto bool_msg = std::make_shared<std_msgs::msg::Bool>();
        rclcpp::Serialization<std_msgs::msg::Bool> serialization;
        rclcpp::SerializedMessage serialized_msg(*bag_message->serialized_data);
        serialization.deserialize_message(&serialized_msg, bool_msg.get());
        publisher->publish(*bool_msg);
        RCLCPP_DEBUG(this->get_logger(), "Published bool message");
    }
    
    void handle_uint16_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
        auto uint16_msg = std::make_shared<std_msgs::msg::UInt16>();
        rclcpp::Serialization<std_msgs::msg::UInt16> serialization;
        rclcpp::SerializedMessage serialized_msg(*bag_message->serialized_data);
        serialization.deserialize_message(&serialized_msg, uint16_msg.get());
        judge_remain_time_publisher_->publish(*uint16_msg);
        RCLCPP_DEBUG(this->get_logger(), "Published UInt16 message");
    }
    
    void handle_uint8_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
        auto uint8_msg = std::make_shared<std_msgs::msg::UInt8>();
        rclcpp::Serialization<std_msgs::msg::UInt8> serialization;
        rclcpp::SerializedMessage serialized_msg(*bag_message->serialized_data);
        serialization.deserialize_message(&serialized_msg, uint8_msg.get());
        judge_radar_cmd_publisher_->publish(*uint8_msg);
        RCLCPP_DEBUG(this->get_logger(), "Published UInt8 message");
    }
    
    void handle_game_robot_hp_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
        auto msg = std::make_shared<radar_interface::msg::GameRobotHP>();
        rclcpp::Serialization<radar_interface::msg::GameRobotHP> serialization;
        rclcpp::SerializedMessage serialized_msg(*bag_message->serialized_data);
        serialization.deserialize_message(&serialized_msg, msg.get());
        judge_game_robot_hp_publisher_->publish(*msg);
        RCLCPP_DEBUG(this->get_logger(), "Published GameRobotHP message");
    }
    
    void handle_radar_info_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
        auto msg = std::make_shared<radar_interface::msg::RadarInfo>();
        rclcpp::Serialization<radar_interface::msg::RadarInfo> serialization;
        rclcpp::SerializedMessage serialized_msg(*bag_message->serialized_data);
        serialization.deserialize_message(&serialized_msg, msg.get());
        judge_radar_info_publisher_->publish(*msg);
        RCLCPP_DEBUG(this->get_logger(), "Published RadarInfo message");
    }
    
    void handle_radar_mark_data_message(std::shared_ptr<rosbag2_storage::SerializedBagMessage> bag_message, rclcpp::Time ros_time) {
        auto msg = std::make_shared<radar_interface::msg::RadarMarkData>();
        rclcpp::Serialization<radar_interface::msg::RadarMarkData> serialization;
        rclcpp::SerializedMessage serialized_msg(*bag_message->serialized_data);
        serialization.deserialize_message(&serialized_msg, msg.get());
        judge_radar_mark_data_publisher_->publish(*msg);
        RCLCPP_DEBUG(this->get_logger(), "Published RadarMarkData message");
    }

    void play_bag() {
        RCLCPP_INFO(this->get_logger(), "Starting to play bag file");
        
        // 添加一个短暂的暂停，确保所有订阅者都已连接
        std::this_thread::sleep_for(500ms);
        
        rclcpp::Time start_time = this->now();
        rcutils_time_point_value_t bag_start_time = 0;
        bool first_msg = true;
        
        while (rclcpp::ok()) {
            try {
                if (!reader_.has_next()) {
                    RCLCPP_INFO(this->get_logger(), "Reached end of bag file, reopening...");
                    reader_.open(rosbag_file);
                    first_msg = true;
                    std::this_thread::sleep_for(100ms);
                    continue;
                }
                
                auto bag_message = reader_.read_next();
                auto current_time = this->now();
                
                // 如果是第一条消息，记录起始时间
                if (first_msg) {
                    bag_start_time = bag_message->time_stamp;
                    start_time = current_time;
                    first_msg = false;
                }
                
                // 计算当前消息应该在什么时候发布
                if (use_original_timestamps_ && bag_start_time > 0) {
                    // 计算bag中的时间差（单位：纳秒）
                    int64_t bag_time_diff = bag_message->time_stamp - bag_start_time;
                    
                    // 转换为实际的等待时间，考虑播放速率
                    int64_t wait_time_ns = bag_time_diff / playback_rate_;
                    
                    // 计算目标时间点
                    auto target_time = start_time + rclcpp::Duration(wait_time_ns);
                    
                    // 如果还没到发布时间，则等待
                    if (current_time < target_time) {
                        auto wait_duration = target_time - current_time;
                        
                        // 将wait_duration转换为std::chrono可以使用的格式
                        int64_t wait_ns = wait_duration.nanoseconds();
                        std::this_thread::sleep_for(std::chrono::nanoseconds(wait_ns));
                    }
                }
                
                const std::string& topic_name = bag_message->topic_name;
                
                // 查找话题对应的处理函数并调用
                auto handler_it = message_handlers_.find(topic_name);
                if (handler_it != message_handlers_.end()) {
                    handler_it->second(bag_message, this->now());
                } else {
                    RCLCPP_DEBUG(this->get_logger(), "No handler for topic: %s", topic_name.c_str());
                }
            } catch (const std::exception& e) {
                RCLCPP_ERROR(this->get_logger(), "Exception in play_bag: %s", e.what());
                std::this_thread::sleep_for(1s);
            }
        }
        
        RCLCPP_INFO(this->get_logger(), "Finished playing bag file");
    }

    // 各种发布器
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_publisher_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr judge_color_publisher_;
    rclcpp::Publisher<std_msgs::msg::UInt16>::SharedPtr judge_remain_time_publisher_;
    rclcpp::Publisher<radar_interface::msg::GameRobotHP>::SharedPtr judge_game_robot_hp_publisher_;
    rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr judge_radar_cmd_publisher_;
    rclcpp::Publisher<radar_interface::msg::RadarInfo>::SharedPtr judge_radar_info_publisher_;
    rclcpp::Publisher<radar_interface::msg::RadarMarkData>::SharedPtr judge_radar_mark_data_publisher_;
    
    // 消息处理器映射
    std::unordered_map<std::string, std::function<void(std::shared_ptr<rosbag2_storage::SerializedBagMessage>, rclcpp::Time)>> message_handlers_;
    
    rosbag2_cpp::Reader reader_;
    std::shared_ptr<std::thread> processing_thread_;
    std::string rosbag_file;
    bool use_original_timestamps_;
    double playback_rate_;
};

RCLCPP_COMPONENTS_REGISTER_NODE(RosbagPlayer)
