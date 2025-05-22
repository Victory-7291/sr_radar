#ifndef VIDEO_PLAYER__VIDEO_PLAYER_NODE_HPP_
#define VIDEO_PLAYER__VIDEO_PLAYER_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>
#include <rosbag2_cpp/reader.hpp>
#include <memory>
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
  bool open_video_source();
  bool open_video_file();
  bool open_rosbag();
  
  // 共用属性
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::string source_type_; // "video", "rosbag" 或 "camera"
  std::string source_path_; // 视频或rosbag文件路径
  std::string topic_name_; // 要发布的话题名称
  bool loop_; // 是否循环播放
  double frame_rate_; // 帧率
  
  // 视频文件播放相关
  cv::VideoCapture cap_;
  
  // Rosbag播放相关
  std::unique_ptr<rosbag2_cpp::Reader> bag_reader_;
  std::string bag_topic_; // 要从bag中读取的话题
  std::vector<std::shared_ptr<sensor_msgs::msg::Image>> cached_images_; // 缓存从bag读取的图像
  size_t current_frame_index_; // 当前帧索引
  rclcpp::Time start_time_; // 开始时间
};

}  // namespace video_player

#endif  // VIDEO_PLAYER__VIDEO_PLAYER_NODE_HPP_