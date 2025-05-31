#include "detect.h"

#include <opencv2/imgproc.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/utilities.hpp>
#include <filesystem>
#define TDT_INFO(msg) std::cout << msg << std::endl
#define MAX_CARS 12
#define MAX_ARMORS 20
namespace tdt_radar {
  unsigned int count_img=0;

int getColor(cv::Mat &img) {
    std::vector<cv::Mat> channels;
    cv::split(img, channels);
    cv::Mat blueMinusRed = channels[0] - channels[2];
    cv::Mat redMinusBlue = channels[2] - channels[0];
    cv::Scalar avgBlueMinusRed = cv::mean(blueMinusRed);
    cv::Scalar avgRedMinusBlue = cv::mean(redMinusBlue);
    cv::Scalar avgGreen = cv::mean(channels[1]);
    if(avgBlueMinusRed[0]>avgRedMinusBlue[0]){
      return 0; // Blue
    }else{
      return 2; // Red
    }
}

bool isRectInside(const cv::Rect& small, const cv::Rect& big) {
    bool topLeftInside = big.contains(small.tl());
    bool topRightInside = big.contains(cv::Point(small.x + small.width, small.y));
    bool bottomLeftInside = big.contains(cv::Point(small.x, small.y + small.height));
    bool bottomRightInside = big.contains(cv::Point(small.x + small.width, small.y + small.height));
    return (topLeftInside && topRightInside && bottomLeftInside && bottomRightInside);
}

bool isBoxInside(const yolo::Box& small, const yolo::Box& big) {
    cv::Rect small_rect(small.left,small.top,small.right-small.left,small.bottom-small.top);
    cv::Rect big_rect(big.left,big.top,big.right-big.left,big.bottom-big.top);
    return isRectInside(small_rect,big_rect);
}

cv::Rect getSafeRect(cv::Mat &image, cv::Rect &rect) {
    cv::Rect save_rect;
    save_rect.x = std::max(0, rect.x);
    save_rect.y = std::max(0, rect.y);
    save_rect.width = std::min(image.cols - save_rect.x, rect.width);
    save_rect.height = std::min(image.rows - save_rect.y, rect.height);
    return save_rect;
}

Detect::Detect(const rclcpp::NodeOptions& node_options)
    : Node("radar_detect_node", node_options) {
    //cv::namedWindow("detect", cv::WINDOW_NORMAL);

    // 使用system函数调用nvidia-smi命令
    std::cout << "Checking CUDA with nvidia-smi...\n";
    if (system("nvidia-smi") == 0) {
        RCLCPP_INFO(this->get_logger(), "CUDA is available.");
    } else {
        RCLCPP_ERROR(this->get_logger(), "CUDA is not available. Exiting.");
        rclcpp::shutdown();
    }
    cv::FileStorage fs;
    fs.open("./config/detect_params.yaml", cv::FileStorage::READ);
    fs["yolo_path"] >> yolo_path;
    fs["armor_path"] >> armor_path;
    fs.release();

    std::ifstream file1(yolo_path.c_str());
    if(!file1.good()) {
        system("python3 src/utils/onnx2trt.py "
        "--onnx=model/ONNX/RM2024.onnx "
        "--saveEngine=model/TensorRT/yolo.engine "
        "--minBatch 1 "
        "--optBatch 1 "
        "--maxBatch 2 "
        "--Shape=1280x1280 "
        "--input_name=images"
        );
    }else{
      TDT_INFO("Load yolo engine!");
    }
    std::ifstream file2(armor_path.c_str());
    if(!file2.good()) {
        system("python3 src/utils/onnx2trt.py "
        "--onnx=model/ONNX/armor.onnx "
        "--saveEngine=model/TensorRT/armor.engine "
        "--minBatch 1 "
        "--optBatch 5 "
        "--maxBatch 12 "
        "--Shape=640x640 "
        "--input_name=images"
        );
    }else{
      TDT_INFO("Load armor_yolo engine!");
    }
    std::cout<<"yolo_path:"<<yolo_path<<"\n";
    std::cout<<"armor_path:"<<armor_path<<"\n";

    this->armor_yolo = yolo::load(armor_path, yolo::Type::V5,0.4f,0.45f);
    TDT_INFO("Load armor_yolo engine success!");
    this->yolo = yolo::load(yolo_path, yolo::Type::V5,0.65f,0.45f);
    TDT_INFO("Load yolo engine success!");

  image_sub = this->create_subscription<sensor_msgs::msg::Image>(
      "camera_image", rclcpp::SensorDataQoS(),
      std::bind(&Detect::callback, this, std::placeholders::_1));
  image_pub = this->create_publisher<sensor_msgs::msg::Image>("detect_image", rclcpp::SensorDataQoS());
  pub = this->create_publisher<vision_interface::msg::DetectResult>("detect_result", rclcpp::SensorDataQoS());
  RCLCPP_INFO(this->get_logger(), "Detect node has been started.");
}

void Detect::callback(const std::shared_ptr<sensor_msgs::msg::Image> msg) {
  std::cout<<"time: "<<msg->header.stamp.sec<<"."<<msg->header.stamp.nanosec<<std::endl;
  auto img = cv_bridge::toCvShare(msg, "bgr8")->image;
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  // 创建一个空的检测结果消息，所有坐标默认为0
  vision_interface::msg::DetectResult detect_result;
  detect_result.header.stamp = msg->header.stamp;

  // 标记是否需要处理检测到的车辆和装甲板
  bool should_process = true;

  yolo::Image image(img.data, img.cols, img.rows);

  auto result = yolo->forward(image);
  if(result.size()==0){
    //RCLCPP_INFO(this->get_logger(), "No Car!");
    // 发布空的检测结果（所有坐标默认为0）
    pub->publish(detect_result);
    should_process = false;  // 不需要处理后续步骤
  }else if(result.size()>MAX_CARS){
    //RCLCPP_INFO(this->get_logger(), "Too Many Car!");
    // 发布空的检测结果（所有坐标默认为0）
    pub->publish(detect_result);
    should_process = false;  // 不需要处理后续步骤
  }

  std::vector<yolo::Image> images;
  std::vector<cv::Mat> car_imgs;
  std::vector<Car> cars;

  if(should_process) {
    for(auto &box:result){
      if (box.class_label==0 || box.class_label==1)
      {
        Car car;
        car.car=box;
        cars.push_back(car);
      }
    }
    
    for(auto &car : cars){
      auto temp_rect = cv::Rect(
        car.car.left,
        car.car.top,
        car.car.right-car.car.left,
        car.car.bottom-car.car.top);
      cv::Rect temp_car_rect = getSafeRect(img,temp_rect);
      auto car_img = img(temp_car_rect);
      car_imgs.push_back(car_img.clone());
      car.car_rect = temp_car_rect;
    }

    for(auto &car_img:car_imgs){
      auto image_yolo = yolo::Image(car_img.data, car_img.cols, car_img.rows);
      images.push_back(image_yolo);
    }

    auto armor_boxes = armor_yolo->forwards(images);
    bool has_armor=false;
    for(int i=0;i<armor_boxes.size();i++){
      if(armor_boxes[i].size()==0){
        continue;
      }else{
        cars[i].armors=armor_boxes[i];
        has_armor=true;}
    }
    if(!has_armor){
      //RCLCPP_INFO(this->get_logger(), "No Armor!");
      // 发布空的检测结果（所有坐标默认为0）
      pub->publish(detect_result);
      should_process = false;  // 不需要处理后续步骤
    }
  }

  if(should_process) {
    for(auto &car:cars){
      if(car.armors.size()==0){continue;}
      for(auto &armor:car.armors){
        if(debug){
          //cv::putText(img,std::to_string(armor.class_label),cv::Point(armor.left+car.car.left,armor.top+car.car.top),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(0,255,0),2);
          cv::rectangle(img,car.car_rect,cv::Scalar(255,255,255),2);
        }
      }
    }
    
    for(auto &car:cars){
      if(car.armors.size()==0){continue;}
      
      cv::Rect max_rect;
      float max_confidence=0;
      int best_armor_class_label = -1;

      for(auto &armor:car.armors){
        if(armor.confidence > max_confidence){
          max_rect=cv::Rect(
            armor.left+car.car.left,
            armor.top+car.car.top,
            armor.right-armor.left,
            armor.bottom-armor.top);
          max_confidence=armor.confidence;
          best_armor_class_label = armor.class_label;
        }
      }

      if(best_armor_class_label == -1){
          if(debug)
            cv::putText(img,"No Valid Armor",cv::Point(car.car.left,car.car.bottom-10),cv::FONT_HERSHEY_SIMPLEX,2,cv::Scalar(255,255,0),3);
          continue;
      }

      if (best_armor_class_label >= 0 && best_armor_class_label <= 5) {
          car.color = 0;
          car.number = best_armor_class_label + 1;
      } else if (best_armor_class_label >= 6 && best_armor_class_label <= 11) {
          car.color = 2;
          car.number = best_armor_class_label - 5;
      } else {
          if(debug) cv::putText(img,"Unknown Class",cv::Point(car.car.left,car.car.bottom-20),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(0,0,0),2);
          continue;
      }
      
      auto safe_rect = getSafeRect(img,max_rect);
      //cv::rectangle(img,safe_rect,cv::Scalar(255,255,255),2);

      //car.center=cv::Point2f(max_rect.x+max_rect.width/2,car.car.bottom);
      //car.center=cv::Point2f((car.car.left+car.car.right)/2,car.car.bottom+3);
      car.center=cv::Point2f((car.car.left+car.car.right)/2,max_rect.y+max_rect.height);
      
      if(car.color==0){
          detect_result.blue_x[car.number-1]=car.center.x;
          detect_result.blue_y[car.number-1]=car.center.y;
          //if(car.center.x*car.center.y==0&&car.number!=0){
          //  RCLCPP_ERROR(this->get_logger(), "Error: blue car center is 0 for number %d", car.number);
          //}
          if(debug){
          cv::rectangle(img,car.car_rect,cv::Scalar(255,0,0),2);
          cv::putText(img,std::to_string(car.number),cv::Point(safe_rect.x, safe_rect.y -10),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(255,0,0),2);
          cv::putText(img,"C:"+std::to_string(car.car.confidence),cv::Point(car.car.left,car.car.top),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(255,255,255),2);
          cv::circle(img,car.center,5,cv::Scalar(255,0,0),-1);
          }
      }
      if(car.color==2){
          detect_result.red_x[car.number-1]=car.center.x;
          detect_result.red_y[car.number-1]=car.center.y;
          //if(car.center.x*car.center.y==0&&car.number!=0){
          //  RCLCPP_ERROR(this->get_logger(), "Error: red car center is 0 for number %d", car.number);
          //}
          if(debug){
          cv::rectangle(img,car.car_rect,cv::Scalar(0,0,255),2);
          cv::putText(img,std::to_string(car.number),cv::Point(safe_rect.x, safe_rect.y - 10),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(0,0,255),2);
          cv::putText(img,"C:"+std::to_string(car.car.confidence),cv::Point(car.car.left,car.car.top),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(255,255,255),2);
          cv::circle(img,car.center,5,cv::Scalar(0,0,255),-1);
          }
      }
    }
    
    pub->publish(detect_result);
  }

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
  std::cout<<"Detect Time: "<<time_used.count()*1000<<"ms"<<std::endl;
  
  // 确保在所有情况下都显示图像
  cv::Mat final_img;
  cv::resize(img, final_img, cv::Size(1536, 1125));
  cv::imshow("detect", final_img);
  auto key = cv::waitKey(1);
  if(key=='r'){
      debug = !debug;
  }
}
}// namespace tdt_radar
RCLCPP_COMPONENTS_REGISTER_NODE(tdt_radar::Detect)