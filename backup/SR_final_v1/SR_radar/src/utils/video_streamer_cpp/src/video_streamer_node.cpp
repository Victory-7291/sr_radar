#include "video_streamer_cpp/video_streamer_node.hpp"
#include <sensor_msgs/image_encodings.hpp>

namespace video_streamer_cpp
{

VideoStreamerNode::VideoStreamerNode(const rclcpp::NodeOptions & options)
: Node("video_streamer_node", options)
{
  RCLCPP_INFO(this->get_logger(), "VideoStreamerNode component created.");
  declare_parameters();
  initialize_video_source();

  publisher_ = this->create_publisher<sensor_msgs::msg::Image>(output_topic_, 10);
  
  // Determine actual FPS
  double video_fps = cap_.get(cv::CAP_PROP_FPS);
  if (force_fps_ || video_fps <= 0) {
    current_fps_ = target_fps_;
    if (force_fps_) {
      RCLCPP_INFO(this->get_logger(), "Forcing frame rate to user-specified value: %.2f FPS.", current_fps_);
    } else {
      RCLCPP_WARN(this->get_logger(), "Could not get FPS from video or camera, using target_fps: %.2f FPS.", current_fps_);
    }
  } else {
    current_fps_ = video_fps;
    RCLCPP_INFO(this->get_logger(), "Video FPS: %.2f. Using this as publishing rate.", current_fps_);
  }

  if (current_fps_ <= 0) {
      RCLCPP_ERROR(this->get_logger(), "Resulting FPS is invalid (%.2f). Cannot start timer.", current_fps_);
      throw std::runtime_error("Invalid FPS for timer.");
  }

  expected_frame_duration_ = std::chrono::duration<double>(1.0 / current_fps_);
  RCLCPP_INFO(this->get_logger(), "Publishing at %.2f FPS, with frame interval: %.4f seconds.", 
              current_fps_, expected_frame_duration_.count());

  prev_frame_time_ = std::chrono::steady_clock::now();
  timer_ = this->create_wall_timer(
    expected_frame_duration_,
    std::bind(&VideoStreamerNode::timer_callback, this));

  RCLCPP_INFO(this->get_logger(), "VideoStreamerNode initialized, publishing video to '%s' at %.2f FPS.", 
              output_topic_.c_str(), current_fps_);
}

VideoStreamerNode::~VideoStreamerNode()
{
  if (timer_) {
    timer_->cancel();
  }
  if (cap_.isOpened()) {
    cap_.release();
  }
  RCLCPP_INFO(this->get_logger(), "VideoStreamerNode component destroyed.");
}

void VideoStreamerNode::declare_parameters()
{
  this->declare_parameter<std::string>("video_file_path", "");
  this->declare_parameter<std::string>("output_topic", "/image_raw_cpp");
  this->declare_parameter<bool>("loop", true);
  this->declare_parameter<double>("target_fps", 30.0);
  this->declare_parameter<bool>("force_fps", false);

  this->get_parameter("video_file_path", video_file_path_);
  this->get_parameter("output_topic", output_topic_);
  this->get_parameter("loop", loop_);
  this->get_parameter("target_fps", target_fps_);
  this->get_parameter("force_fps", force_fps_);

  RCLCPP_INFO(this->get_logger(), "Parameters: video_file_path='%s', output_topic='%s', loop=%d, target_fps=%.2f, force_fps=%d", 
              video_file_path_.c_str(), output_topic_.c_str(), loop_, target_fps_, force_fps_);
}

void VideoStreamerNode::initialize_video_source()
{
  if (video_file_path_.empty()) {
    RCLCPP_ERROR(this->get_logger(), "Video file path is not set (param 'video_file_path').");
    throw std::runtime_error("Video file path is not set.");
  }

  RCLCPP_INFO(this->get_logger(), "Opening video file: %s", video_file_path_.c_str());
  if (!cap_.open(video_file_path_)) {
    RCLCPP_ERROR(this->get_logger(), "Error opening video file: %s", video_file_path_.c_str());
    throw std::runtime_error("Error opening video file: " + video_file_path_);
  }
  RCLCPP_INFO(this->get_logger(), "Video file opened successfully. Width: %.0f, Height: %.0f", 
              cap_.get(cv::CAP_PROP_FRAME_WIDTH), cap_.get(cv::CAP_PROP_FRAME_HEIGHT));
}

void VideoStreamerNode::timer_callback()
{
  auto now = std::chrono::steady_clock::now();
  auto elapsed_since_prev_frame = now - prev_frame_time_;

  // Simple busy wait if we are too early, this is not ideal for high precision but helps
  // prevent bursting if processing is very fast.
  // A more robust solution might involve a more complex timer re-scheduling or rate control.
  if (elapsed_since_prev_frame < expected_frame_duration_ * 0.95) { // Add a small tolerance
      return; // Skip this callback, wait for the next one closer to the desired time
  }
  prev_frame_time_ = now; // Update for the next cycle

  cv::Mat frame;
  cap_ >> frame;

  if (frame.empty()) {
    if (loop_) {
      RCLCPP_INFO(this->get_logger(), "End of video. Looping.");
      cap_.set(cv::CAP_PROP_POS_FRAMES, 0);
      cap_ >> frame;
      if (frame.empty()) {
        RCLCPP_ERROR(this->get_logger(), "Failed to loop video or video is empty after attempting to loop.");
        timer_->cancel();
        return;
      }
    } else {
      RCLCPP_INFO(this->get_logger(), "End of video. Stopping.");
      timer_->cancel();
      // Potentially signal shutdown or completion if needed
      // rclcpp::shutdown(nullptr, "Video ended"); 
      return;
    }
  }

  // Prepare header
  std_msgs::msg::Header header;
  header.stamp = this->now(); // Use rclcpp::Node::now() for ROS time
  header.frame_id = "camera_optical_frame"; // Or a configurable frame_id

  // Convert OpenCV image to ROS message
  try {
      cv_image_ = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, frame);
      sensor_msgs::msg::Image::SharedPtr msg = cv_image_.toImageMsg();
      publisher_->publish(*msg);
      RCLCPP_DEBUG(this->get_logger(), "Published frame at ROS time: %f", rclcpp::Time(header.stamp).seconds());
  } catch (const cv_bridge::Exception& e) {
      RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
      return;
  }
}

}  // namespace video_streamer_cpp

// Register the component withrclcpp_components
RCLCPP_COMPONENTS_REGISTER_NODE(video_streamer_cpp::VideoStreamerNode) 