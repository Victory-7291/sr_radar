#ifndef VIDEO_PLAYER__VIDEO_PLAYER_NODE_HPP_
#define VIDEO_PLAYER__VIDEO_PLAYER_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>

namespace video_player
{

class VideoPlayerNode : public rclcpp::Node
{
public:
  explicit VideoPlayerNode(const rclcpp::NodeOptions & options);

private:
  void image_callback(const sensor_msgs::msg::Image::SharedPtr msg);
  void timer_callback();

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  cv::VideoCapture cap_;
  std::string video_path_;
  bool use_camera_;
  int camera_id_;
  bool loop_;
  double frame_rate_;
};

}  // namespace video_player

#endif  // VIDEO_PLAYER__VIDEO_PLAYER_NODE_HPP_