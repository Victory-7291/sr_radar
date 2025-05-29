#include <rclcpp/logger.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/qos.hpp>
#include <rclcpp/rclcpp.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <vision_interface/msg/detect_result.hpp>
#include <vision_interface/msg/radar2_sentry.hpp>
#include <vision_interface/msg/radar_warn.hpp>
#include <vision_interface/msg/match_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <fstream>
#include <radar_interface/msg/match_result.hpp>
#include <radar_interface/msg/matched_target.hpp>
#include <radar_interface/team_color.hpp>
#include <radar_interface/msg/radar_mark_data.hpp>
namespace tdt_radar {
    class DebugMap : public rclcpp::Node {
    public:
        explicit DebugMap(const rclcpp::NodeOptions & options) : Node("debug_map", options){
            match_result_sub = this->create_subscription<vision_interface::msg::DetectResult>("/kalman_detect", 10, std::bind(&DebugMap::match_result_callback, this, std::placeholders::_1));
            sub_color_ = this->create_subscription<radar_interface::team_color::msg>("judge/color", rclcpp::SystemDefaultsQoS(), std::bind(&DebugMap::color_callback, this, std::placeholders::_1));
            sub_radar_mark_data_ = this->create_subscription<radar_interface::msg::RadarMarkData>("judge/radar_mark_data", rclcpp::SystemDefaultsQoS(), std::bind(&DebugMap::radar_mark_data_callback, this, std::placeholders::_1));
            
            //radar2sentry_pub = this->create_publisher<vision_interface::msg::Radar2Sentry>("/Radar2Sentry", rclcpp::SensorDataQoS());
            match_result_pub = this->create_publisher<radar_interface::msg::MatchResult>("/matcher/match_result", rclcpp::SystemDefaultsQoS());
            
            map = cv::imread("config/RM2025.png");
            cv::resize(map, map, cv::Size(28*38, 15*38));

            // 初始化relax相关参数
            for(int i = 0; i < 6; i++){
                relax[i] = false;
                relax_time[i] = 0.0;
                blue_time[i] = 0.0;
                red_time[i] = 0.0;
                blue_update[i] = 0.0;
                red_update[i] = 0.0;
                mark_progress[i] = 0;
            }
            
            // 初始化团队颜色
            self_color = radar_interface::team_color::UNKNOWN;
            
            // 创建30Hz的定时器用于更新地图显示
            double timer_period = 1.0 / 30.0; // 30Hz，约33.3ms
            map_timer = this->create_wall_timer(
                std::chrono::duration<double>(timer_period),
                std::bind(&DebugMap::show_map, this));
        }
        
        void radar_mark_data_callback(const radar_interface::msg::RadarMarkData::SharedPtr msg)
        {
            for (int i = 0; i < 6; i++) {
                mark_progress[i] = msg->mark_progress[i];
            }
            RCLCPP_INFO(this->get_logger(), "Radar mark data received");
        }
        
        void color_callback(const radar_interface::team_color::msg::SharedPtr msg)
        {
            self_color = msg->data ? radar_interface::team_color::C_RED : radar_interface::team_color::C_BLUE;
            RCLCPP_INFO(this->get_logger(), "Team color received: %s", self_color == radar_interface::team_color::C_RED ? "RED" : "BLUE");
        }
        
        //void save_match_info(const std::shared_ptr<vision_interface::msg::MatchInfo> msg){
        //    this->match_info = *msg;
        //    if(msg->self_color==1)
        //    match_info.self_color = 2;
        //}

        void show_map(){
            auto now_time = std::chrono::system_clock::now();
            double time = std::chrono::duration_cast<std::chrono::milliseconds>(now_time.time_since_epoch()).count()/1000.0;
            auto clone_map = map.clone();
            for(int i=0;i<6;i++){
                int number = i+1;
                if(number==6)number++;
                if(blue_point[i].x*blue_point[i].y&&time-blue_update[i]<2){
                    cv::Point2f point = cv::Point2f(clone_map.cols*blue_point[i].x/28,clone_map.rows*(15-blue_point[i].y)/15);
                    cv::circle(clone_map,point,10,cv::Scalar(200,0,0),-1);
                    cv::putText(clone_map,std::to_string(number),cv::Point(point.x-6,point.y+5),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255));
                }
                if(red_point[i].x*red_point[i].y&&time-red_update[i]<2){
                    cv::Point2f point = cv::Point2f(clone_map.cols*red_point[i].x/28,clone_map.rows*(15-red_point[i].y)/15);
                    cv::circle(clone_map,point,10,cv::Scalar(0,0,200),-1);
                    cv::putText(clone_map,std::to_string(number),cv::Point(point.x-6,point.y+5),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255));
                }
            }
            cv::imshow("map", clone_map);
            cv::waitKey(1);
        }
        // 将DetectResult转换为MatchResult并发布的回调函数
        void match_result_callback(const std::shared_ptr<vision_interface::msg::DetectResult> msg) {
            auto now = std::chrono::system_clock::now();
            double time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count()/1000.0;
            
            // 更新位置数据
            for (int i = 0; i < 6; i++) {
                if (msg->blue_x[i] * msg->blue_y[i]) {
                    blue_point[i] = cv::Point2f(msg->blue_x[i], msg->blue_y[i]);
                    blue_time[i] = time;
                    blue_update[i] = time;
                }
                if (msg->red_x[i] * msg->red_y[i]) {
                    red_point[i] = cv::Point2f(msg->red_x[i], msg->red_y[i]);
                    red_time[i] = time;
                    red_update[i] = time;
                }
            }
            
            radar_interface::msg::MatchResult match_result;
            
            // 填充红蓝双方的数据
            for (int i = 0; i < 6; i++) {
                // 蓝方数据
                match_result.blue[i].id = -1; // 默认为-1，表示没有匹配到
                if (blue_point[i].x * blue_point[i].y != 0) { // 检查坐标是否有效
                    bool should_publish = false;
                    
                    // 应用与radar2sentry相同的发送机制
                    if (!relax[i]) {
                        if (mark_progress[i] >= 117) {
                            relax[i] = true;
                            relax_time[i] = time;
                        } else {
                            if (time - blue_update[i] < 2) { // 检查时效性（2秒内更新）
                                should_publish = true;
                            }
                        }
                    } else {
                        // 休息状态下处理逻辑
                        if (mark_progress[i] < 105) {
                            relax[i] = false;
                            if (time - blue_update[i] < 2) {
                                should_publish = true;
                            }
                        } else if (time - relax_time[i] > 0.35) { // 发送频率控制（休息状态下0.35秒一次）
                            relax_time[i] = time;
                            if (time - blue_update[i] < 2) {
                                should_publish = true;
                            }
                        }
                    }
                    
                    if (should_publish) {
                        match_result.blue[i].id = i; // 设置ID
                        match_result.blue[i].position[0] = blue_point[i].x;
                        match_result.blue[i].position[1] = blue_point[i].y;
                    }
                }
                
                // 红方数据
                match_result.red[i].id = -1; // 默认为-1，表示没有匹配到
                if (red_point[i].x * red_point[i].y != 0) { // 检查坐标是否有效
                    bool should_publish = false;
                    
                    // 应用与radar2sentry相同的发送机制
                    if (!relax[i]) {
                        if (mark_progress[i] >= 117) {
                            relax[i] = true;
                            relax_time[i] = time;
                        } else {
                            if (time - red_update[i] < 2) { // 检查时效性（2秒内更新）
                                should_publish = true;
                            }
                        }
                    } else {
                        // 休息状态下处理逻辑
                        if (mark_progress[i] < 105) {
                            relax[i] = false;
                            if (time - red_update[i] < 2) {
                                should_publish = true;
                            }
                        } else if (time - relax_time[i] > 0.35) { // 发送频率控制（休息状态下0.35秒一次）
                            relax_time[i] = time;
                            if (time - red_update[i] < 2) {
                                should_publish = true;
                            }
                        }
                    }
                    
                    if (should_publish) {
                        match_result.red[i].id = i; // 设置ID
                        match_result.red[i].position[0] = red_point[i].x;
                        match_result.red[i].position[1] = red_point[i].y;
                    }
                }
            }
            
            // 发布结果
            match_result_pub->publish(match_result);
        }

        rclcpp::Subscription<vision_interface::msg::DetectResult>::SharedPtr match_result_sub;
        //rclcpp::Publisher<vision_interface::msg::Radar2Sentry>::SharedPtr radar2sentry_pub;
        rclcpp::Publisher<radar_interface::msg::MatchResult>::SharedPtr match_result_pub;
        rclcpp::Subscription<radar_interface::team_color::msg>::SharedPtr sub_color_;
        rclcpp::Subscription<radar_interface::msg::RadarMarkData>::SharedPtr sub_radar_mark_data_;
        rclcpp::TimerBase::SharedPtr map_timer; // 用于定时更新地图的定时器

        double blue_time[6];//单位s
        double red_time[6];//单位s

        bool relax[6];
        double relax_time[6];

        double blue_update[6];
        double red_update[6];

        int hero_count1;
        int hero_count2;
        
        cv::Point2f blue_point[6];
        cv::Point2f red_point[6];
        
        uint8_t mark_progress[6];

        //vision_interface::msg::MatchInfo match_info;
        radar_interface::team_color::ENUM self_color;
        cv::Mat map;
        int count = 0;//20帧保存一次
        };
}  // namespace tdt_radar

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    auto node_options = rclcpp::NodeOptions(); // 创建NodeOptions实例
    rclcpp::spin(std::make_shared<tdt_radar::DebugMap>(node_options)); // 传递NodeOptions实例
    rclcpp::shutdown();
    return 0;
}
