#ifndef VIDEO_STREAMER_CPP__VIDEO_STREAMER_NODE_HPP_
#define VIDEO_STREAMER_CPP__VIDEO_STREAMER_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>

namespace video_streamer_cpp
{

class VideoStreamerNode : public rclcpp::Node
{
public:
  explicit VideoStreamerNode(const rclcpp::NodeOptions & options);
  ~VideoStreamerNode();

private:
  void declare_parameters();
  void initialize_video_source();
  void timer_callback();

  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  cv::VideoCapture cap_;
  cv_bridge::CvImage cv_image_;

  // Parameters
  std::string video_file_path_;
  std::string output_topic_;
  bool loop_;
  double target_fps_;
  bool force_fps_;

  double current_fps_; // Actual FPS to use, determined after checking video file or forced
  std::chrono::steady_clock::time_point prev_frame_time_;
  std::chrono::duration<double> expected_frame_duration_;
};

}  // namespace video_streamer_cpp

#endif  // VIDEO_STREAMER_CPP__VIDEO_STREAMER_NODE_HPP_ 