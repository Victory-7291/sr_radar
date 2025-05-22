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

  this->declare_parameter<std::string>("video_file_path", "");
  this->get_parameter("video_file_path", video_path_);

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

  publisher_ = this->create_publisher<sensor_msgs::msg::Image>("video_image", 10);
  double fps = cap_.get(cv::CAP_PROP_FPS);
  if (fps <= 0) {
    RCLCPP_WARN(this->get_logger(), "Could not get FPS from video, defaulting to 30 FPS.");
    fps = 30.0;
  }
  RCLCPP_INFO(this->get_logger(), "Video FPS: %f", fps);
  
  timer_ = this->create_wall_timer(
    std::chrono::milliseconds(static_cast<int>(1000.0 / fps)),
    std::bind(&VideoPlayerNode::timer_callback, this));
  RCLCPP_INFO(this->get_logger(), "VideoPlayerNode initialized, publishing to 'video_image' at %f FPS.", fps);
}

void VideoPlayerNode::timer_callback()
{
  try {
    cv::Mat frame;
    cap_ >> frame;

    if (frame.empty()) {
      RCLCPP_INFO(this->get_logger(), "End of video file reached. Looping.");
      cap_.set(cv::CAP_PROP_POS_FRAMES, 0); // Reset to the beginning of the video
      cap_ >> frame; // Read the first frame again
      if (frame.empty()) {
          RCLCPP_ERROR(this->get_logger(), "Failed to loop video or video is empty.");
          timer_->cancel(); // Stop the timer if looping fails
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