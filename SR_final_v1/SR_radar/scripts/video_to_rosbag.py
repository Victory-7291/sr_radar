#!/usr/bin/env python3

import cv2
import numpy as np
import os
import rclpy
from rclpy.node import Node
from rclpy.serialization import serialize_message
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import rosbag2_py
from rcl_interfaces.msg import ParameterDescriptor
from rclpy.time import Time
import argparse
import sys
import yaml
from time import sleep

def get_rosbag_options(path, db_only=True):
    storage_options = rosbag2_py.StorageOptions(
        uri=path,
        storage_id='sqlite3')
    
    converter_options = rosbag2_py.ConverterOptions(
        input_serialization_format='cdr',
        output_serialization_format='cdr')
    
    return storage_options, converter_options

class VideoToBag(Node):
    def __init__(self):
        super().__init__('video_to_bag_node')
        
        self.declare_parameter('video_path', '', 
                               ParameterDescriptor(description='Path to the input video file'))
        self.declare_parameter('bag_path', '',
                               ParameterDescriptor(description='Path to the output bag file'))
        self.declare_parameter('topic_name', '/video_image',
                               ParameterDescriptor(description='Topic name for the image messages'))
        self.declare_parameter('fps', 0.0,
                               ParameterDescriptor(description='FPS override (0 for auto)'))
        
        self.video_path = self.get_parameter('video_path').value
        self.bag_path = self.get_parameter('bag_path').value
        self.topic_name = self.get_parameter('topic_name').value
        self.fps_override = self.get_parameter('fps').value
        
        if not self.video_path or not self.bag_path:
            self.get_logger().error('Video path and bag path must be provided')
            rclpy.shutdown()
            sys.exit(1)
            
        self.get_logger().info(f'Converting video: {self.video_path}')
        self.get_logger().info(f'Output bag: {self.bag_path}')
        self.get_logger().info(f'Topic name: {self.topic_name}')
        
        self.bridge = CvBridge()
        
    def convert(self):
        # Open video file
        cap = cv2.VideoCapture(self.video_path)
        if not cap.isOpened():
            self.get_logger().error(f'Could not open video file: {self.video_path}')
            return False
            
        # Get video properties
        width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
        height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
        fps = cap.get(cv2.CAP_PROP_FPS) if self.fps_override <= 0 else self.fps_override
        frame_count = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
        
        if fps <= 0:
            self.get_logger().warning('Invalid FPS value, using 30 FPS as default')
            fps = 30.0
            
        self.get_logger().info(f'Video properties: {width}x{height}, {fps} FPS, {frame_count} frames')
        
        # Create bag directory if it doesn't exist
        os.makedirs(os.path.dirname(os.path.abspath(self.bag_path)), exist_ok=True)
        
        # Create writer
        storage_options, converter_options = get_rosbag_options(self.bag_path)
        writer = rosbag2_py.SequentialWriter()
        
        try:
            writer.open(storage_options, converter_options)
        except Exception as e:
            self.get_logger().error(f'Error opening bag file: {e}')
            return False
            
        # Add topic
        topic_info = rosbag2_py.TopicMetadata(
            name=self.topic_name,
            type='sensor_msgs/msg/Image',
            serialization_format='cdr')
        writer.create_topic(topic_info)
        
        # Process video
        frame_time_ns = int(1e9 / fps)  # Time between frames in nanoseconds
        current_time_ns = 0
        frame_index = 0
        
        while True:
            ret, frame = cap.read()
            if not ret:
                break
                
            # Convert to ROS image
            msg = self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')
            msg.header.stamp = Time(nanoseconds=current_time_ns).to_msg()
            msg.header.frame_id = 'camera_frame'
            
            # Write to bag
            writer.write(
                self.topic_name,
                serialize_message(msg),
                current_time_ns)
                
            current_time_ns += frame_time_ns
            frame_index += 1
            
            # Progress update
            if frame_index % 100 == 0 or frame_index == frame_count:
                self.get_logger().info(f'Progress: {frame_index}/{frame_count} frames ({frame_index/frame_count*100:.1f}%)')
                
        cap.release()
        self.get_logger().info('Video conversion complete')
        return True

def main():
    # Parse arguments
    parser = argparse.ArgumentParser(description='Convert video file to ROS2 bag')
    parser.add_argument('--video', type=str, help='Path to the input video file')
    parser.add_argument('--bag', type=str, help='Path to the output bag file')
    parser.add_argument('--topic', type=str, default='/video_image', help='Topic name for the image messages')
    parser.add_argument('--fps', type=float, default=0.0, help='FPS override (0 for auto)')
    
    args, unknown = parser.parse_known_args()
    
    # Initialize ROS
    rclpy.init()
    
    # Get the parameters from command line or use defaults
    node = VideoToBag()
    
    # If command line arguments were provided, override node parameters
    if args.video:
        node.video_path = args.video
    if args.bag:
        node.bag_path = args.bag
    if args.topic:
        node.topic_name = args.topic
    if args.fps > 0:
        node.fps_override = args.fps
    
    # Run conversion
    success = node.convert()
    
    # Cleanup
    rclpy.shutdown()
    return 0 if success else 1

if __name__ == '__main__':
    sys.exit(main()) 