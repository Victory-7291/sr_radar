#include "video_player/video_player_node.hpp"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.hpp>
#include <rclcpp_components/register_node_macro.hpp>

namespace video_player
{

VideoPlayerNode::VideoPlayerNode(const rclcpp::NodeOptions & options)
: Node("video_player_node", options)
{
  RCLCPP_INFO(this->get_logger(), "VideoPlayerNode created");

  // 不再从参数中获取视频路径，而是使用默认值
  // 但仍然声明参数，允许可选的命令行覆盖
  this->declare_parameter<std::string>("video_file_path", video_path_);
  this->get_parameter("video_file_path", video_path_);
  
  // 声明其他参数
  this->declare_parameter<bool>("use_camera", use_camera_);
  this->declare_parameter<int>("camera_id", camera_id_);
  this->declare_parameter<bool>("loop", loop_);
  this->declare_parameter<double>("frame_rate", frame_rate_);
  
  // 获取参数值（如果命令行有提供）
  this->get_parameter("use_camera", use_camera_);
  this->get_parameter("camera_id", camera_id_);
  this->get_parameter("loop", loop_);
  this->get_parameter("frame_rate", frame_rate_);

  // 根据配置选择视频源
  if (use_camera_) {
    RCLCPP_INFO(this->get_logger(), "Using camera with ID: %d", camera_id_);
    try {
      cap_.open(camera_id_);
      if (!cap_.isOpened()) {
        RCLCPP_ERROR(this->get_logger(), "Error opening camera with ID: %d", camera_id_);
        throw std::runtime_error("Error opening camera");
      }
    } catch (const std::exception& e) {
      RCLCPP_ERROR(this->get_logger(), "Exception while opening camera: %s", e.what());
      throw;
    }
  } else {
    if (video_path_.empty()) {
      RCLCPP_ERROR(this->get_logger(), "Video file path is not set.");
      throw std::runtime_error("Video file path is not set.");
    }

    RCLCPP_INFO(this->get_logger(), "Opening video file: %s", video_path_.c_str());
    try {
      cap_.open(video_path_);
      if (!cap_.isOpened()) {
        RCLCPP_ERROR(this->get_logger(), "Error opening video file: %s", video_path_.c_str());
        throw std::runtime_error("Error opening video file: " + video_path_);
      }
      
      RCLCPP_INFO(this->get_logger(), "Video successfully opened. Width: %d, Height: %d", 
                  (int)cap_.get(cv::CAP_PROP_FRAME_WIDTH), 
                  (int)cap_.get(cv::CAP_PROP_FRAME_HEIGHT));
    } catch (const std::exception& e) {
      RCLCPP_ERROR(this->get_logger(), "Exception while opening video: %s", e.what());
      throw;
    }
  }

  publisher_ = this->create_publisher<sensor_msgs::msg::Image>("video_image", 10);
  
  // 获取视频帧率或使用默认值
  double fps = cap_.get(cv::CAP_PROP_FPS);
  if (fps <= 0) {
    RCLCPP_WARN(this->get_logger(), "Could not get FPS from video, using default: %f FPS.", frame_rate_);
    fps = frame_rate_;
  } else {
    RCLCPP_INFO(this->get_logger(), "Video FPS: %f", fps);
  }
  
  timer_ = this->create_wall_timer(
    std::chrono::milliseconds(static_cast<int>(1000.0 / fps)),
    std::bind(&VideoPlayerNode::timer_callback, this));
  
  if (use_camera_) {
    RCLCPP_INFO(this->get_logger(), "VideoPlayerNode initialized, publishing camera frames to 'video_image' at %f FPS.", fps);
  } else {
    RCLCPP_INFO(this->get_logger(), "VideoPlayerNode initialized, publishing video to 'video_image' at %f FPS.", fps);
  }
}

void VideoPlayerNode::timer_callback()
{
  try {
    cv::Mat frame;
    cap_ >> frame;

    if (frame.empty()) {
      if (use_camera_) {
        RCLCPP_ERROR(this->get_logger(), "Empty frame from camera. Check camera connection.");
        return;
      } else if (loop_) {
        RCLCPP_INFO(this->get_logger(), "End of video file reached. Looping.");
        cap_.set(cv::CAP_PROP_POS_FRAMES, 0); // Reset to the beginning of the video
        cap_ >> frame; // Read the first frame again
        if (frame.empty()) {
            RCLCPP_ERROR(this->get_logger(), "Failed to loop video or video is empty.");
            timer_->cancel(); // Stop the timer if looping fails
            return;
        }
      } else {
        RCLCPP_INFO(this->get_logger(), "End of video file reached. Stopping playback.");
        timer_->cancel(); // Stop the timer if not looping
        return;
      }
    }

    // OpenCV reads images in BGR format by default, so no conversion is needed for BGR8.
    std_msgs::msg::Header header;
    header.stamp = this->now();
    header.frame_id = "camera_frame"; // Or any appropriate frame_id

    sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
    publisher_->publish(*msg);
    
    RCLCPP_DEBUG(this->get_logger(), "Published frame at time: %f", rclcpp::Time(header.stamp).seconds());
  } catch (const std::exception& e) {
    RCLCPP_ERROR(this->get_logger(), "Exception in timer_callback: %s", e.what());
  }
}

}  // namespace video_player

RCLCPP_COMPONENTS_REGISTER_NODE(video_player::VideoPlayerNode)