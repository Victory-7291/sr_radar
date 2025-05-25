#include "video_record/video_record_node.hpp"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace video_record
{

VideoRecordNode::VideoRecordNode(const rclcpp::NodeOptions & options)
: Node("video_record_node", options),
  is_recording_(false),
  frame_count_(0)
{
  RCLCPP_INFO(this->get_logger(), "VideoRecordNode创建");

  // 生成完整的输出文件路径
  output_path_ = generate_filename();
  RCLCPP_INFO(this->get_logger(), "视频将保存到: %s", output_path_.c_str());

  // 从参数获取视频编码格式，默认为MJPG
  this->declare_parameter<std::string>("fourcc", "mp4v");
  this->get_parameter("fourcc", fourcc_);

  // 从参数获取视频帧率，默认为30
  this->declare_parameter<double>("fps", 30.0);
  this->get_parameter("fps", fps_);

  // 从参数获取视频宽高，默认为0（将根据接收到的图像确定）
  this->declare_parameter<int>("width", 0);
  this->declare_parameter<int>("height", 0);
  this->get_parameter("width", width_);
  this->get_parameter("height", height_);

  // 创建相机图像订阅者
  subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
    "camera_image", 10, std::bind(&VideoRecordNode::image_callback, this, std::placeholders::_1));

  RCLCPP_INFO(this->get_logger(), "已订阅相机图像话题 'camera_image'");
  RCLCPP_INFO(this->get_logger(), "视频编码: %s, 帧率: %.1f", fourcc_.c_str(), fps_);
}

VideoRecordNode::~VideoRecordNode()
{
  // 关闭视频写入器
  if (video_writer_.isOpened()) {
    video_writer_.release();
    RCLCPP_INFO(this->get_logger(), "视频录制完成，已保存 %lu 帧到 %s", frame_count_, output_path_.c_str());
  }
}

std::string VideoRecordNode::generate_filename() const
{
  // 生成带时间戳的文件名
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << output_dir_;
  if (output_dir_.back() != '/' && output_dir_.back() != '\\') {
    ss << '/';
  }
  ss << "camera_record_" << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S") << ".mp4";
  return ss.str();
}

void VideoRecordNode::image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  try {
    // 将ROS图像消息转换为OpenCV格式
    cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8);

    // 当前时间
    auto now = this->now();
    
    // 如果还没有开始录制，初始化视频写入器
    if (!is_recording_) {
      // 如果未设置宽高，使用图像的宽高
      if (width_ == 0 || height_ == 0) {
        width_ = cv_ptr->image.cols;
        height_ = cv_ptr->image.rows;
      }

      if (verbose_) {
        RCLCPP_INFO(this->get_logger(), "初始化视频写入器，尺寸: %dx%d，帧率: %.1f", width_, height_, fps_);
      }

      // 初始化视频编码器和写入器
      int fourcc = cv::VideoWriter::fourcc(
        fourcc_[0], 
        fourcc_.length() > 1 ? fourcc_[1] : ' ', 
        fourcc_.length() > 2 ? fourcc_[2] : ' ', 
        fourcc_.length() > 3 ? fourcc_[3] : ' '
      );
      
      video_writer_.open(output_path_, fourcc, fps_, cv::Size(width_, height_));
      
      if (!video_writer_.isOpened()) {
        RCLCPP_ERROR(this->get_logger(), "无法创建视频写入器，路径: %s", output_path_.c_str());
        return;
      }
      
      is_recording_ = true;
      record_start_time_ = now;
      RCLCPP_INFO(this->get_logger(), "开始录制视频到: %s", output_path_.c_str());
    }

    // 将图像写入视频文件
    video_writer_.write(cv_ptr->image);
    frame_count_++;
    
    // 定期显示录制状态
    if (verbose_ && frame_count_ % 100 == 0) {
      auto elapsed = now - record_start_time_;
      double elapsed_seconds = elapsed.seconds();
      double actual_fps = frame_count_ / elapsed_seconds;
      
      RCLCPP_INFO(this->get_logger(), "已录制 %lu 帧，运行时间: %.1f 秒，实际帧率: %.1f FPS", 
                 frame_count_, elapsed_seconds, actual_fps);
    }
  } catch (const cv_bridge::Exception& e) {
    RCLCPP_ERROR(this->get_logger(), "cv_bridge异常: %s", e.what());
  } catch (const std::exception& e) {
    RCLCPP_ERROR(this->get_logger(), "图像处理异常: %s", e.what());
  }
}

}  // namespace video_record

RCLCPP_COMPONENTS_REGISTER_NODE(video_record::VideoRecordNode) 