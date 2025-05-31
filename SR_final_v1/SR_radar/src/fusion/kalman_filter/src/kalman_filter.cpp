#include "kalman_filter.h"
#include "filter_plus.h"
#include <pcl_conversions/pcl_conversions.h>

namespace tdt_radar{

KalmanFilter::KalmanFilter(const rclcpp::NodeOptions& node_options):rclcpp::Node("kalman_filter_node",node_options)
{
    //radar_pub_ = this->create_publisher<vision_interface::msg::Radar2Sentry>("/radar2sentry", 10);
    radar_detect_pub_ = this->create_publisher<vision_interface::msg::DetectResult>("/kalman_detect", 10);
    sub_detect_= this->create_subscription<vision_interface::msg::DetectResult>("/resolve_result", rclcpp::SensorDataQoS(), std::bind(&KalmanFilter::detect_callback, this, std::placeholders::_1));
    sub_color_ = this->create_subscription<radar_interface::team_color::msg>("judge/color", 10, std::bind(&KalmanFilter::color_callback, this, std::placeholders::_1));
    
    self_color = radar_interface::team_color::UNKNOWN;
    
    //RCLCPP_INFO(this->get_logger(), "Kalman_filter_Node has been started.");
}

void KalmanFilter::color_callback(const radar_interface::team_color::msg::SharedPtr msg)
{
    self_color = msg->data ? radar_interface::team_color::C_RED : radar_interface::team_color::C_BLUE;
    //RCLCPP_INFO(this->get_logger(), "Team color received: %s", self_color == radar_interface::team_color::C_RED ? "RED" : "BLUE");
}

void KalmanFilter::detect_callback(const vision_interface::msg::DetectResult::SharedPtr msg)
{
    //RCLCPP_INFO(this->get_logger(), "Detect_callback");
    rclcpp::Time time = msg->header.stamp;
    
    // 首先初始化检测结果，拷贝原始消息
    vision_interface::msg::DetectResult detect_msg = *msg;
    
    // 首先更新所有滤波器的预测点
    for(auto &kf : KFs)
    {
        kf.update_predict_point();
        kf.has_updated = false;
    }
    
    // 处理所有机器人的卡尔曼滤波
    
    // 处理红色机器人
    for(int robot_idx = 0; robot_idx < 6; robot_idx++) {
        if(msg->red_x[robot_idx] != 0 && msg->red_y[robot_idx] != 0) {
            pcl::PointXY red_point;
            red_point.x = msg->red_x[robot_idx];
            red_point.y = msg->red_y[robot_idx];
            
            // 匹配过程
            std::vector<int> match_kf_indexs;
            for(int j = 0; j < this->KFs.size(); j++)
            {
                if(KFs[j].match(red_point) && KFs[j].get_color() == 2 && KFs[j].get_number() == robot_idx){
                    match_kf_indexs.push_back(j);
                }
            }
            
            // 处理三种匹配情况
            if(match_kf_indexs.size() == 0)
            {
                // 无匹配：创建新滤波器
                Kalman_filter_plus kf(red_point, time);
                kf.camera_match(time, red_point, 2, robot_idx); // 设置为红色机器人
                KFs.push_back(kf);
            }
            else if(match_kf_indexs.size() == 1)
            {
                // 单一匹配：直接更新
                KFs[match_kf_indexs[0]].update(red_point, time);
                KFs[match_kf_indexs[0]].camera_match(time, red_point, 2, robot_idx);
            }
            else
            {
                // 多重匹配：选择最近点更新
                float min_distance = 1000000;
                int min_index = 0;
                for(auto index : match_kf_indexs)
                {
                    float distance = KFs[index].Distance(KFs[index].predict_point, red_point);
                    if(distance < min_distance)
                    {
                        min_distance = distance;
                        min_index = index;
                    }
                }
                KFs[min_index].update(red_point, time);
                KFs[min_index].camera_match(time, red_point, 2, robot_idx);
            }
        }
    }
    
    // 处理蓝色机器人
    for(int robot_idx = 0; robot_idx < 6; robot_idx++) {
        if(msg->blue_x[robot_idx] != 0 && msg->blue_y[robot_idx] != 0) {
            pcl::PointXY blue_point;
            blue_point.x = msg->blue_x[robot_idx];
            blue_point.y = msg->blue_y[robot_idx];
            
            // 匹配过程
            std::vector<int> match_kf_indexs;
            for(int j = 0; j < this->KFs.size(); j++)
            {
                if(KFs[j].match(blue_point) && KFs[j].get_color() == 0 && KFs[j].get_number() == robot_idx){
                    match_kf_indexs.push_back(j);
                }
            }
            
            // 处理三种匹配情况
            if(match_kf_indexs.size() == 0)
            {
                // 无匹配：创建新滤波器
                Kalman_filter_plus kf(blue_point, time);
                kf.camera_match(time, blue_point, 0, robot_idx); // 设置为蓝色机器人
                KFs.push_back(kf);
            }
            else if(match_kf_indexs.size() == 1)
            {
                // 单一匹配：直接更新
                KFs[match_kf_indexs[0]].update(blue_point, time);
                KFs[match_kf_indexs[0]].camera_match(time, blue_point, 0, robot_idx);
            }
            else
            {
                // 多重匹配：选择最近点更新
                float min_distance = 1000000;
                int min_index = 0;
                for(auto index : match_kf_indexs)
                {
                    float distance = KFs[index].Distance(KFs[index].predict_point, blue_point);
                    if(distance < min_distance)
                    {
                        min_distance = distance;
                        min_index = index;
                    }
                }
                KFs[min_index].update(blue_point, time);
                KFs[min_index].camera_match(time, blue_point, 0, robot_idx);
            }
        }
    }
    
    // 清理过时的卡尔曼滤波器
    for(int i = KFs.size() - 1; i >= 0; i--)
    {
        if((KFs[i].last_time) > 0.35){
            KFs.erase(KFs.begin() + i);
        }
    }
    
    // 清理过时的历史记录
    for(auto &kf : KFs)
    {
        for(int i=kf.history.size() - 1; i >= 0; i--)
        {
            if(Kalman_filter_plus::GetTimeByRosTime(time)-kf.history[i].first > 0.35)
            {
                kf.history.erase(kf.history.begin() + i);
            }
        }
    }
    
    // 更新所有机器人的卡尔曼滤波结果
    for(auto kf : KFs)
    {
        if(kf.detect_history.size()==0) continue;
        
        int robot_idx = kf.get_number();
        
        if(kf.get_color() == 0) // 蓝色机器人
        {
            detect_msg.blue_x[robot_idx] = kf.predict_point.x;
            detect_msg.blue_y[robot_idx] = kf.predict_point.y;
        }
        else if(kf.get_color() == 2) // 红色机器人
        {
            detect_msg.red_x[robot_idx] = kf.predict_point.x;
            detect_msg.red_y[robot_idx] = kf.predict_point.y;
        }
    }
    
    // 坐标系转换和特殊处理
    if(self_color == radar_interface::team_color::C_BLUE){
        for(int i=0; i<6; i++){
            if(detect_msg.blue_x[i]!=0 && detect_msg.blue_y[i]!=0){
                detect_msg.blue_x[i]=28.0-detect_msg.blue_x[i];
                detect_msg.blue_y[i]=15.0-detect_msg.blue_y[i];
            }
            if(detect_msg.red_x[i]!=0 && detect_msg.red_y[i]!=0){
                detect_msg.red_x[i]=28.0-detect_msg.red_x[i];
                detect_msg.red_y[i]=15.0-detect_msg.red_y[i];
            }
        }
    }
    
    radar_detect_pub_->publish(detect_msg);
}

}//namespace tdt_radar
RCLCPP_COMPONENTS_REGISTER_NODE(tdt_radar::KalmanFilter)


