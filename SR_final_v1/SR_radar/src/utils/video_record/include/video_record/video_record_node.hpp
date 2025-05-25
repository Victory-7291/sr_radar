#ifndef VIDEO_RECORD__VIDEO_RECORD_NODE_HPP_
#define VIDEO_RECORD__VIDEO_RECORD_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>
#include <string>
#include <memory>

namespace video_record
{

class VideoRecordNode : public rclcpp::Node
{
public:
  explicit VideoRecordNode(const rclcpp::NodeOptions & options);
  ~VideoRecordNode();

private:
  void image_callback(const sensor_msgs::msg::Image::SharedPtr msg);
  
  // 生成带时间戳的文件路径
  std::string generate_filename() const;
  
  // 订阅相机图像
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
  
  // 视频保存路径
  std::string output_dir_ = "/Users/wan/Videos/"; // 默认保存目录
  std::string output_path_; // 完整的文件路径（包含文件名）
  
  // 视频编码器
  std::string fourcc_ = "mp4v"; // 默认使用mp4v编码器
  
  // 视频宽高
  int width_ = 0; // 0表示自动根据图像设置
  int height_ = 0; // 0表示自动根据图像设置
  
  // 视频帧率
  double fps_ = 60.0; // 默认30帧每秒
  
  // OpenCV视频写入器
  cv::VideoWriter video_writer_;
  
  // 是否正在记录
  bool is_recording_;
  
  // 记录开始时间
  rclcpp::Time record_start_time_;
  
  // 记录的帧数
  uint64_t frame_count_;
  
  // 是否在控制台显示录制状态
  bool verbose_ = true; // 默认显示录制信息
};

}  // namespace video_record

#endif  // VIDEO_RECORD__VIDEO_RECORD_NODE_HPP_ 