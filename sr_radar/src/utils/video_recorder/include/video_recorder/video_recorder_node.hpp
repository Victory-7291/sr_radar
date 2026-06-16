#ifndef VIDEO_RECORDER__VIDEO_RECORDER_NODE_HPP_
#define VIDEO_RECORDER__VIDEO_RECORDER_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace video_recorder
{

class VideoRecorderNode : public rclcpp::Node
{
public:
  explicit VideoRecorderNode(const rclcpp::NodeOptions & options);
  virtual ~VideoRecorderNode();

private:
  void image_callback(const sensor_msgs::msg::Image::SharedPtr msg);
  std::string generate_filename();
  
  // 图像订阅器
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
  
  // OpenCV视频写入器
  cv::VideoWriter video_writer_;
  
  // 参数
  std::string output_dir_;
  std::string filename_prefix_;
  int frame_width_;
  int frame_height_;
  double fps_;
  int fourcc_;
  bool recording_;
  std::string current_filename_;
  
  // 记录视频帧数
  int frame_count_;
  
  // 记录视频开始时间
  std::chrono::time_point<std::chrono::system_clock> start_time_;
};

}  // namespace video_recorder

#endif  // VIDEO_RECORDER__VIDEO_RECORDER_NODE_HPP_ 