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
  
  // 默认视频路径设置为空，需要通过参数传入
  std::string video_path_ = "";
  
  // 其他播放相关参数
  bool use_camera_ = false;    // 是否使用摄像头代替视频文件
  int camera_id_ = 0;          // 摄像头ID（仅当use_camera_为true时有效）
  bool loop_ = true;           // 是否循环播放视频
  double frame_rate_ = 60.0;   // 默认帧率（如果无法从视频获取或force_frame_rate为true）
  bool force_frame_rate_ = false; // 是否强制使用指定的帧率，忽略视频文件中的帧率
};

}  // namespace video_player

#endif  // VIDEO_PLAYER__VIDEO_PLAYER_NODE_HPP_