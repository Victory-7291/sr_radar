#!/usr/bin/env python3
"""
ROS2话题记录工具 - 将ROS2话题保存为.db3格式文件

使用方法:
1. 直接运行模式（推荐）:
   - 编辑脚本顶部的DEFAULT_OUTPUT_DIR, DEFAULT_TOPICS和DEFAULT_DURATION设置
   - 确保DIRECT_RUN = True
   - 直接执行脚本: python3 record_topics.py

2. 命令行参数模式:
   - 设置DIRECT_RUN = False
   - 使用命令行参数执行: python3 record_topics.py -d ~/output -t 60 --topics /topic1 /topic2

常见用法示例:
- 记录预设话题到默认目录: python3 record_topics.py
- 记录30秒: python3 record_topics.py -t 30
- 记录到特定目录: python3 record_topics.py -d ~/my_bags
- 记录特定话题: python3 record_topics.py --topics /topic1 /topic2
"""

import os
import time
import argparse
import subprocess
from datetime import datetime
import sys

#=====================================================================
# 用户配置区 - 修改这些值来自定义默认行为
#=====================================================================

# 默认保存目录 - 修改为你想要的路径
DEFAULT_OUTPUT_DIR = "/home/wan/SR_final_v1/SR_radar/"

# 默认要记录的话题列表 - 添加或删除你要记录的话题
DEFAULT_TOPICS = [
    "/judge/remain_time",
    "/judge/radar_mark_data",
    "/judge/radar_info",
    "/judge/color",
    "/judge/game_robot_hp",
    "/judge/radar_cmd",
    "/camera_image", 
    # 可以在此添加更多话题，例如:
    # "/topic1",
    # "/topic2",
]

# 默认记录时长（秒），None表示一直记录直到用户中断
# 设置为数字（如：60）则会自动在指定秒数后停止记录
DEFAULT_DURATION = None

# 是否直接运行（不解析命令行参数）
# True: 直接使用上面设置的默认值，忽略所有命令行参数
# False: 允许通过命令行参数覆盖默认设置
DIRECT_RUN = True

#=====================================================================
# 脚本功能区 - 一般情况下不需要修改
#=====================================================================

def create_directory(directory):
    """创建目录，如果目录不存在"""
    if not os.path.exists(directory):
        os.makedirs(directory)
        print(f"创建目录: {directory}")

def record_topics(output_dir, topics, duration=None):
    """记录指定的话题到.db3文件"""
    # 创建带有时间戳的文件名
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_path = os.path.join(output_dir, f"radar_data_{timestamp}")
    
    # 构建ROS2命令
    cmd = ["ros2", "bag", "record", "-o", output_path]
    cmd.extend(topics)
    
    print(f"开始记录话题: {', '.join(topics)}")
    print(f"输出文件: {output_path}")
    
    try:
        # 如果指定了持续时间，则记录指定时长
        if duration:
            print(f"将记录 {duration} 秒...")
            process = subprocess.Popen(cmd)
            time.sleep(duration)
            process.terminate()
            print(f"记录完成！文件保存在: {output_path}")
        else:
            # 否则一直记录直到用户中断
            print("记录中... 按 Ctrl+C 停止记录")
            subprocess.run(cmd)
    except KeyboardInterrupt:
        print("\n用户中断记录")
        print(f"记录完成！文件保存在: {output_path}")

def direct_run():
    """直接使用默认配置运行"""
    output_dir = os.path.expanduser(DEFAULT_OUTPUT_DIR)
    create_directory(output_dir)
    record_topics(output_dir, DEFAULT_TOPICS, DEFAULT_DURATION)

if __name__ == "__main__":
    # 如果设置为直接运行模式，则跳过参数解析
    if DIRECT_RUN:
        direct_run()
        sys.exit(0)
    
    # 解析命令行参数（可选）
    parser = argparse.ArgumentParser(description="记录ROS2话题为.db3文件")
    parser.add_argument("-d", "--directory", default=DEFAULT_OUTPUT_DIR, 
                      help=f"存储.db3文件的目录路径 (默认: {DEFAULT_OUTPUT_DIR})")
    parser.add_argument("-t", "--duration", type=int, default=DEFAULT_DURATION,
                      help="记录的时长（秒），不指定则一直记录直到用户中断")
    parser.add_argument("--topics", nargs="+", default=DEFAULT_TOPICS,
                      help="要记录的话题列表")
    parser.add_argument("--use-defaults", action="store_true",
                      help="使用脚本中预设的默认值，忽略其他命令行参数")
    
    args = parser.parse_args()
    
    # 如果指定了使用默认值，则忽略其他命令行参数
    if args.use_defaults:
        output_dir = os.path.expanduser(DEFAULT_OUTPUT_DIR)
        topics = DEFAULT_TOPICS
        duration = DEFAULT_DURATION
    else:
        output_dir = os.path.expanduser(args.directory)
        topics = args.topics
        duration = args.duration
    
    # 创建输出目录
    create_directory(output_dir)
    
    # 开始记录话题
    record_topics(output_dir, topics, duration) 
