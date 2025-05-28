#ifndef VIDEO_PLAYER__VIDEO_PLAYER_NODE_HPP_
#define VIDEO_PLAYER__VIDEO_PLAYER_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>
#include <string>

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
  
  // 默认视频路径（请修改为您的实际视频路径）
  std::string video_path_ = "/Users/wan/Documents/SR_final_v1/videos/sample.mp4";
  
  // 其他播放相关参数
  bool use_camera_ = false;  // 是否使用摄像头代替视频文件
  int camera_id_ = 0;        // 摄像头ID（仅当use_camera_为true时有效）
  bool loop_ = true;         // 是否循环播放视频
  double frame_rate_ = 30.0; // 默认帧率（如果无法从视频获取）
};

}  // namespace video_player

#endif  // VIDEO_PLAYER__VIDEO_PLAYER_NODE_HPP_