#!/bin/bash

# 定义工作空间路径
WORKSPACE_PATH="$(cd "$(dirname "$0")/.." && pwd)"
VIDEO_PATH="$WORKSPACE_PATH/test.mp4"
ROSBAG_PATH="$WORKSPACE_PATH/test_video_bag"

echo "工作空间路径: $WORKSPACE_PATH"
echo "视频文件路径: $VIDEO_PATH"
echo "Rosbag输出路径: $ROSBAG_PATH"

# 检查视频文件是否存在
if [ ! -f "$VIDEO_PATH" ]; then
  echo "错误: 视频文件 $VIDEO_PATH 不存在!"
  exit 1
fi

# 步骤1: 将视频转换为rosbag
echo "步骤1: 将视频转换为rosbag..."
# 确保输出目录存在
mkdir -p "$(dirname "$ROSBAG_PATH")"

# 调用Python脚本进行转换
python3 $WORKSPACE_PATH/scripts/video_to_rosbag.py --video "$VIDEO_PATH" --bag "$ROSBAG_PATH"

# 检查转换是否成功
if [ $? -ne 0 ]; then
  echo "错误: 视频转换失败!"
  exit 1
fi

echo "转换完成! Rosbag保存在 $ROSBAG_PATH"

# 步骤2: 编译代码
echo "步骤2: 编译代码..."
cd $WORKSPACE_PATH && colcon build --packages-select video_player tdt_vision

# 检查编译是否成功
if [ $? -ne 0 ]; then
  echo "错误: 编译失败!"
  exit 1
fi

echo "编译完成!"

# 步骤3: 启动calibration程序
echo "步骤3: 启动校准程序..."
source $WORKSPACE_PATH/install/setup.bash
ros2 launch tdt_vision calib_rosbag.launch.py

echo "完成!" 