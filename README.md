wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ colcon build
Starting >>> radar_interface
Starting >>> vision_interface
Starting >>> hik_camera
Starting >>> libocsort
Starting >>> video_player
Starting >>> video_recorder
Finished <<< hik_camera [0.14s]                                          
Finished <<< video_player [0.16s]
Finished <<< libocsort [0.17s]
Finished <<< vision_interface [0.46s]                                     
Starting >>> rosbag_player
Finished <<< radar_interface [0.48s]
Starting >>> tdt_vision
Starting >>> debug_map
Starting >>> dv_trigger
Starting >>> judge_bridge
Starting >>> kalman_filter
Starting >>> radar_decision
Finished <<< rosbag_player [0.18s]                                  
Finished <<< radar_decision [0.17s]
Finished <<< dv_trigger [0.19s]
Finished <<< debug_map [0.21s]
--- stderr: video_recorder                                              
/home/wan/SR_final_v1/SR_radar/src/utils/video_recorder/src/video_recorder_node.cpp: In constructor ‘video_recorder::VideoRecorderNode::VideoRecorderNode(const rclcpp::NodeOptions&)’:
/home/wan/SR_final_v1/SR_radar/src/utils/video_recorder/src/video_recorder_node.cpp:26:44: error: expected primary-expression before ‘topic_name’
   26 |   this->get_parameter("topic", std::string topic_name);
      |                                            ^~~~~~~~~~
In file included from /opt/ros/humble/include/rclcpp/rclcpp/logging.hpp:24,
                 from /opt/ros/humble/include/rclcpp/rclcpp/client.hpp:40,
                 from /opt/ros/humble/include/rclcpp/rclcpp/callback_group.hpp:24,
                 from /opt/ros/humble/include/rclcpp/rclcpp/any_executable.hpp:20,
                 from /opt/ros/humble/include/rclcpp/rclcpp/memory_strategy.hpp:25,
                 from /opt/ros/humble/include/rclcpp/rclcpp/memory_strategies.hpp:18,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executor_options.hpp:20,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executor.hpp:37,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executors/multi_threaded_executor.hpp:25,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executors.hpp:21,
                 from /opt/ros/humble/include/rclcpp/rclcpp/rclcpp.hpp:155,
                 from /home/wan/SR_final_v1/SR_radar/src/utils/video_recorder/include/video_recorder/video_recorder_node.hpp:4,
                 from /home/wan/SR_final_v1/SR_radar/src/utils/video_recorder/src/video_recorder_node.cpp:1:
/home/wan/SR_final_v1/SR_radar/src/utils/video_recorder/src/video_recorder_node.cpp:50:51: error: ‘topic_name’ was not declared in this scope; did you mean ‘typename’?
   50 |   RCLCPP_INFO(this->get_logger(), "订阅话题: %s", topic_name.c_str());
      |                                                   ^~~~~~~~~~
/home/wan/SR_final_v1/SR_radar/src/utils/video_recorder/src/video_recorder_node.cpp:53:69: error: no matching function for call to ‘video_recorder::VideoRecorderNode::create_subscription<sensor_msgs::msg::Image>(const char [13], const rmw_qos_profile_t&, std::_Bind_helper<false, void (video_recorder::VideoRecorderNode::*)(std::shared_ptr<sensor_msgs::msg::Image_<std::allocator<void> > >), video_recorder::VideoRecorderNode*, const std::_Placeholder<1>&>::type)’
   53 |   subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
      |                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^
   54 |     "camera_image", rmw_qos_profile_sensor_data,
      |     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                     
   55 |     std::bind(&VideoRecorderNode::image_callback, this, std::placeholders::_1));
      |     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from /opt/ros/humble/include/rclcpp/rclcpp/executors/single_threaded_executor.hpp:28,
                 from /opt/ros/humble/include/rclcpp/rclcpp/executors.hpp:22,
                 from /opt/ros/humble/include/rclcpp/rclcpp/rclcpp.hpp:155,
                 from /home/wan/SR_final_v1/SR_radar/src/utils/video_recorder/include/video_recorder/video_recorder_node.hpp:4,
                 from /home/wan/SR_final_v1/SR_radar/src/utils/video_recorder/src/video_recorder_node.cpp:1:
/opt/ros/humble/include/rclcpp/rclcpp/node.hpp:219:3: note: candidate: ‘template<class MessageT, class CallbackT, class AllocatorT, class SubscriptionT, class MessageMemoryStrategyT> std::shared_ptr<ROSMessageT> rclcpp::Node::create_subscription(const string&, const rclcpp::QoS&, CallbackT&&, const rclcpp::SubscriptionOptionsWithAllocator<AllocatorT>&, typename MessageMemoryStrategyT::SharedPtr)’
  219 |   create_subscription(
      |   ^~~~~~~~~~~~~~~~~~~
/opt/ros/humble/include/rclcpp/rclcpp/node.hpp:219:3: note:   template argument deduction/substitution failed:
/home/wan/SR_final_v1/SR_radar/src/utils/video_recorder/src/video_recorder_node.cpp:54:21: note:   cannot convert ‘rmw_qos_profile_sensor_data’ (type ‘const rmw_qos_profile_t’ {aka ‘const rmw_qos_profile_s’}) to type ‘const rclcpp::QoS&’
   54 |     "camera_image", rmw_qos_profile_sensor_data,
      |                     ^~~~~~~~~~~~~~~~~~~~~~~~~~~
gmake[2]: *** [CMakeFiles/video_recorder_node.dir/build.make:76: CMakeFiles/video_recorder_node.dir/src/video_recorder_node.cpp.o] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:139: CMakeFiles/video_recorder_node.dir/all] Error 2
gmake: *** [Makefile:146: all] Error 2
---
Failed   <<< video_recorder [5.70s, exited with code 2]
Aborted  <<< kalman_filter [13.6s]                 
Aborted  <<< tdt_vision [15.2s]                    
Aborted  <<< judge_bridge [15.8s]                                   

Summary: 9 packages finished [16.5s]
  1 package failed: video_recorder
  3 packages aborted: judge_bridge kalman_filter tdt_vision
  2 packages had stderr output: tdt_vision video_recorder
  1 package not processed
wan@wan-Predator-PHN16-71:~/SR_final_v1/SR_radar$ 


