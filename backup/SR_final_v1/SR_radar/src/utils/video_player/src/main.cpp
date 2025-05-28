#include <rclcpp/rclcpp.hpp>
#include "video_player/video_player_node.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions options;
  auto node = std::make_shared<video_player::VideoPlayerNode>(options);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
} 