#include "video_player/video_player_node.hpp"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <rosbag2_cpp/readers/sequential_reader.hpp>
#include <memory>
#include <filesystem>
#include <algorithm>

namespace video_player
{

VideoPlayerNode::VideoPlayerNode(const rclcpp::NodeOptions & options)
: Node("video_player_node", options),
  current_frame_index_(0)
{
  RCLCPP_INFO(this->get_logger(), "VideoPlayerNode created");

  // 声明参数
  this->declare_parameter<std::string>("source_type", "video");
  this->declare_parameter<std::string>("video_file_path", "");
  this->declare_parameter<std::string>("rosbag_file_path", "");
  this->declare_parameter<std::string>("rosbag_topic", "/video_image");
  this->declare_parameter<std::string>("topic_name", "video_image");
  this->declare_parameter<bool>("loop", true);
  this->declare_parameter<double>("frame_rate", 0.0);

  // 获取参数
  this->get_parameter("source_type", source_type_);
  this->get_parameter("video_file_path", source_path_);
  this->get_parameter("topic_name", topic_name_);
  this->get_parameter("loop", loop_);
  this->get_parameter("frame_rate", frame_rate_);

  // 如果source_type是rosbag，则使用rosbag路径
  if (source_type_ == "rosbag") {
    this->get_parameter("rosbag_file_path", source_path_);
    this->get_parameter("rosbag_topic", bag_topic_);
  }

  // 创建图像发布者
  publisher_ = this->create_publisher<sensor_msgs::msg::Image>(topic_name_, 10);
  
  // 打开视频源
  if (!open_video_source()) {
    RCLCPP_ERROR(this->get_logger(), "Failed to open video source");
    throw std::runtime_error("Failed to open video source");
  }
  
  // 创建定时器
  double timer_period = (frame_rate_ > 0) ? (1.0 / frame_rate_) : (1.0 / 30.0);
  timer_ = this->create_wall_timer(
    std::chrono::duration<double>(timer_period),
    std::bind(&VideoPlayerNode::timer_callback, this));
  
  RCLCPP_INFO(this->get_logger(), "VideoPlayerNode initialized, publishing to '%s' at %f FPS",
              topic_name_.c_str(), 1.0/timer_period);
}

bool VideoPlayerNode::open_video_source() {
  if (source_type_ == "video") {
    return open_video_file();
  } else if (source_type_ == "rosbag") {
    return open_rosbag();
  } else {
    RCLCPP_ERROR(this->get_logger(), "Unsupported source type: %s", source_type_.c_str());
    return false;
  }
}

bool VideoPlayerNode::open_video_file() {
  if (source_path_.empty()) {
    RCLCPP_ERROR(this->get_logger(), "Video file path is not set.");
    return false;
  }

  RCLCPP_INFO(this->get_logger(), "Opening video file: %s", source_path_.c_str());
  try {
    cap_.open(source_path_);
    if (!cap_.isOpened()) {
      RCLCPP_ERROR(this->get_logger(), "Error opening video file: %s", source_path_.c_str());
      return false;
    }
    
    // 获取视频属性
    double fps = cap_.get(cv::CAP_PROP_FPS);
    if (fps <= 0) {
      RCLCPP_WARN(this->get_logger(), "Could not get FPS from video, defaulting to 30 FPS.");
      fps = 30.0;
    }
    
    // 如果未指定帧率，则使用视频自身的帧率
    if (frame_rate_ <= 0) {
      frame_rate_ = fps;
    }
    
    RCLCPP_INFO(this->get_logger(), "Video successfully opened. Width: %d, Height: %d, FPS: %f", 
                (int)cap_.get(cv::CAP_PROP_FRAME_WIDTH), 
                (int)cap_.get(cv::CAP_PROP_FRAME_HEIGHT),
                fps);
    return true;
  } catch (const std::exception& e) {
    RCLCPP_ERROR(this->get_logger(), "Exception while opening video: %s", e.what());
    return false;
  }
}

bool VideoPlayerNode::open_rosbag() {
  if (source_path_.empty()) {
    RCLCPP_ERROR(this->get_logger(), "Rosbag file path is not set.");
    return false;
  }

  RCLCPP_INFO(this->get_logger(), "Opening rosbag: %s", source_path_.c_str());
  try {
    // 检查bag文件是否存在
    if (!std::filesystem::exists(source_path_)) {
      RCLCPP_ERROR(this->get_logger(), "Rosbag file does not exist: %s", source_path_.c_str());
      return false;
    }
    
    // 创建bag reader
    bag_reader_ = std::make_unique<rosbag2_cpp::readers::SequentialReader>();
    
    // 打开bag文件
    rosbag2_storage::StorageOptions storage_options;
    storage_options.uri = source_path_;
    storage_options.storage_id = "sqlite3";
    
    rosbag2_cpp::ConverterOptions converter_options;
    converter_options.input_serialization_format = "cdr";
    converter_options.output_serialization_format = "cdr";
    
    bag_reader_->open(storage_options, converter_options);
    
    // 检查topic是否存在
    auto topics_and_types = bag_reader_->get_all_topics_and_types();
    bool topic_found = false;
    for (const auto& topic : topics_and_types) {
      if (topic.name == bag_topic_ && topic.type == "sensor_msgs/msg/Image") {
        topic_found = true;
        break;
      }
    }
    
    if (!topic_found) {
      RCLCPP_ERROR(this->get_logger(), "Topic '%s' of type 'sensor_msgs/msg/Image' not found in bag",
                   bag_topic_.c_str());
      return false;
    }
    
    // 预加载所有图像
    RCLCPP_INFO(this->get_logger(), "Loading images from bag...");
    while (bag_reader_->has_next()) {
      auto serialized_message = bag_reader_->read_next();
      
      if (serialized_message->topic_name == bag_topic_) {
        auto image_msg = std::make_shared<sensor_msgs::msg::Image>();
        rclcpp::Serialization<sensor_msgs::msg::Image> serialization;
        serialization.deserialize_message(serialized_message->serialized_data, image_msg.get());
        cached_images_.push_back(image_msg);
      }
    }
    
    if (cached_images_.empty()) {
      RCLCPP_ERROR(this->get_logger(), "No images found in bag under topic '%s'", bag_topic_.c_str());
      return false;
    }
    
    RCLCPP_INFO(this->get_logger(), "Loaded %zu images from bag", cached_images_.size());
    
    // 计算帧率（如果未指定）
    if (frame_rate_ <= 0 && cached_images_.size() >= 2) {
      auto first_ts = rclcpp::Time(cached_images_.front()->header.stamp);
      auto last_ts = rclcpp::Time(cached_images_.back()->header.stamp);
      double duration = (last_ts - first_ts).seconds();
      
      if (duration > 0) {
        frame_rate_ = static_cast<double>(cached_images_.size() - 1) / duration;
        RCLCPP_INFO(this->get_logger(), "Calculated frame rate from bag: %f FPS", frame_rate_);
      } else {
        frame_rate_ = 30.0;
        RCLCPP_WARN(this->get_logger(), "Could not calculate frame rate from bag, using default: %f FPS", frame_rate_);
      }
    } else if (frame_rate_ <= 0) {
      frame_rate_ = 30.0;
      RCLCPP_WARN(this->get_logger(), "Using default frame rate: %f FPS", frame_rate_);
    }
    
    current_frame_index_ = 0;
    start_time_ = this->now();
    
    return true;
  } catch (const std::exception& e) {
    RCLCPP_ERROR(this->get_logger(), "Exception while opening rosbag: %s", e.what());
    return false;
  }
}

void VideoPlayerNode::timer_callback()
{
  try {
    if (source_type_ == "video") {
      // 从视频文件播放
      cv::Mat frame;
      cap_ >> frame;

      if (frame.empty()) {
        if (loop_) {
          RCLCPP_INFO(this->get_logger(), "End of video file reached. Looping.");
          cap_.set(cv::CAP_PROP_POS_FRAMES, 0); // 重置到视频开头
          cap_ >> frame; // 再次读取第一帧
          if (frame.empty()) {
            RCLCPP_ERROR(this->get_logger(), "Failed to loop video or video is empty.");
            timer_->cancel(); // 如果循环失败则停止定时器
            return;
          }
        } else {
          RCLCPP_INFO(this->get_logger(), "End of video file reached.");
          timer_->cancel();
          return;
        }
      }

      // 发布图像消息
      std_msgs::msg::Header header;
      header.stamp = this->now();
      header.frame_id = "camera_frame";

      sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
      publisher_->publish(*msg);
      
      RCLCPP_DEBUG(this->get_logger(), "Published video frame at time: %f", rclcpp::Time(header.stamp).seconds());
    } else if (source_type_ == "rosbag") {
      // 从rosbag播放
      if (cached_images_.empty()) {
        RCLCPP_ERROR(this->get_logger(), "No images available in the bag");
        timer_->cancel();
        return;
      }
      
      if (current_frame_index_ >= cached_images_.size()) {
        if (loop_) {
          RCLCPP_INFO(this->get_logger(), "End of bag reached. Looping.");
          current_frame_index_ = 0;
          start_time_ = this->now();
        } else {
          RCLCPP_INFO(this->get_logger(), "End of bag reached.");
          timer_->cancel();
          return;
        }
      }
      
      // 获取当前帧并发布
      auto image_msg = cached_images_[current_frame_index_];
      
      // 更新时间戳
      auto new_msg = std::make_shared<sensor_msgs::msg::Image>(*image_msg);
      new_msg->header.stamp = this->now();
      
      publisher_->publish(*new_msg);
      
      RCLCPP_DEBUG(this->get_logger(), "Published bag frame %zu/%zu", 
                  current_frame_index_ + 1, cached_images_.size());
                  
      current_frame_index_++;
    }
  } catch (const std::exception& e) {
    RCLCPP_ERROR(this->get_logger(), "Exception in timer_callback: %s", e.what());
  }
}

}  // namespace video_player

RCLCPP_COMPONENTS_REGISTER_NODE(video_player::VideoPlayerNode)