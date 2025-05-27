#include "video_recorder/video_recorder_node.hpp"
#include <rclcpp_components/register_node_macro.hpp>
#include <filesystem>
#include <iostream>

namespace video_recorder
{

VideoRecorderNode::VideoRecorderNode(const rclcpp::NodeOptions & options)
: Node("video_recorder_node", options),
  recording_(false),
  frame_count_(0)
{
  RCLCPP_INFO(this->get_logger(), "VideoRecorderNode正在初始化");

  // 声明并获取参数
  this->declare_parameter<std::string>("output_dir", "/tmp");
  this->declare_parameter<std::string>("filename_prefix", "video_recording");
  this->declare_parameter<double>("fps", 30.0);
  this->declare_parameter<std::string>("fourcc", "mp4v");
  this->declare_parameter<std::string>("topic", "/camera_image");
  
  this->get_parameter("output_dir", output_dir_);
  this->get_parameter("filename_prefix", filename_prefix_);
  this->get_parameter("fps", fps_);
  this->get_parameter("topic", std::string topic_name);

  // 创建输出目录（如果不存在）
  std::filesystem::path dir_path(output_dir_);
  if (!std::filesystem::exists(dir_path)) {
    try {
      std::filesystem::create_directories(dir_path);
      RCLCPP_INFO(this->get_logger(), "创建输出目录: %s", output_dir_.c_str());
    } catch (const std::exception& e) {
      RCLCPP_ERROR(this->get_logger(), "创建输出目录失败: %s, 错误: %s", output_dir_.c_str(), e.what());
      throw;
    }
  }

  // 设置FourCC编码
  std::string fourcc_str;
  this->get_parameter("fourcc", fourcc_str);
  if (fourcc_str.length() != 4) {
    RCLCPP_WARN(this->get_logger(), "无效的FourCC编码: %s, 使用默认值'mp4v'", fourcc_str.c_str());
    fourcc_str = "mp4v";
  }
  fourcc_ = cv::VideoWriter::fourcc(
    fourcc_str[0], fourcc_str[1], fourcc_str[2], fourcc_str[3]);
  
  RCLCPP_INFO(this->get_logger(), "订阅话题: %s", topic_name.c_str());
  
  // 创建订阅器
  subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
    topic_name, 10, 
    std::bind(&VideoRecorderNode::image_callback, this, std::placeholders::_1));

  RCLCPP_INFO(this->get_logger(), "VideoRecorderNode初始化完成");
}

VideoRecorderNode::~VideoRecorderNode()
{
  if (recording_ && video_writer_.isOpened()) {
    RCLCPP_INFO(this->get_logger(), "关闭视频文件: %s, 总共录制了 %d 帧", 
                current_filename_.c_str(), frame_count_);
    video_writer_.release();
  }
}

void VideoRecorderNode::image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  try {
    // 使用cv_bridge将ROS图像消息转换为OpenCV格式
    cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    
    // 如果没有正在录制，初始化视频写入器
    if (!recording_) {
      frame_width_ = cv_ptr->image.cols;
      frame_height_ = cv_ptr->image.rows;
      current_filename_ = generate_filename();
      
      RCLCPP_INFO(this->get_logger(), "开始录制视频: %s, 分辨率: %dx%d, FPS: %.1f", 
                 current_filename_.c_str(), frame_width_, frame_height_, fps_);
      
      video_writer_.open(current_filename_, fourcc_, fps_, 
                        cv::Size(frame_width_, frame_height_));
      
      if (!video_writer_.isOpened()) {
        RCLCPP_ERROR(this->get_logger(), "无法创建视频文件: %s", current_filename_.c_str());
        return;
      }
      
      recording_ = true;
      frame_count_ = 0;
      start_time_ = std::chrono::system_clock::now();
    }
    
    // 写入帧
    video_writer_.write(cv_ptr->image);
    frame_count_++;
    
    // 每100帧打印一次状态
    if (frame_count_ % 100 == 0) {
      auto now = std::chrono::system_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start_time_).count();
      RCLCPP_INFO(this->get_logger(), "已录制 %d 帧, 时长: %ld 秒", frame_count_, duration);
    }
  } catch (const cv_bridge::Exception& e) {
    RCLCPP_ERROR(this->get_logger(), "cv_bridge异常: %s", e.what());
  } catch (const std::exception& e) {
    RCLCPP_ERROR(this->get_logger(), "处理图像时发生异常: %s", e.what());
  }
}

std::string VideoRecorderNode::generate_filename()
{
  auto now = std::chrono::system_clock::now();
  auto now_time = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << output_dir_ << "/" << filename_prefix_ << "_";
  ss << std::put_time(std::localtime(&now_time), "%Y%m%d_%H%M%S") << ".mp4";
  return ss.str();
}

}  // namespace video_recorder

RCLCPP_COMPONENTS_REGISTER_NODE(video_recorder::VideoRecorderNode) 