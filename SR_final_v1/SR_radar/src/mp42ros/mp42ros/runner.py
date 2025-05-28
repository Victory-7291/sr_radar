import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2

class VideoPublisher(Node):
    def __init__(self):
        super().__init__('video_publisher')

        """
        ros2 run mp42ros runner \
        --ros-args \
        -p mp4_file_path:=test.mp4 \
        -p send_topic_name:=/zed2i/zed_node/rgb_raw/image_raw_color \
        -p loop:=True \
        -p fps:=15.0
        """

        self.declare_parameter("mp4_file_path", "test.mp4")
        self.declare_parameter("send_topic_name", "/zed2i/zed_node/rgb_raw/image_raw_color")
        self.declare_parameter("loop", True)  # 無限ループ
        self.declare_parameter("fps", 15.0)  # 15 Hz
        self.mp4_file_path: str = self.get_parameter("mp4_file_path").get_parameter_value().string_value
        self.send_topic_name: str = self.get_parameter("send_topic_name").get_parameter_value().string_value
        self.loop: bool = self.get_parameter("loop").get_parameter_value().bool_value
        self.fps: float = self.get_parameter("fps").get_parameter_value().double_value

        self.publisher_ = self.create_publisher(Image, self.send_topic_name, 10)
        self.timer = self.create_timer(1.0 / self.fps, self.timer_callback)
        self.bridge = CvBridge()
        self.cap = cv2.VideoCapture(self.mp4_file_path)

    def timer_callback(self):
        ret, frame = self.cap.read()
        if not ret and self.loop:
            self.cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
            ret, frame = self.cap.read()

        if ret:
            msg = self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')
            self.publisher_.publish(msg)
        else:
            exit(0)

def main():
    rclpy.init()
    video_publisher = VideoPublisher()
    rclpy.spin(video_publisher)
    video_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()