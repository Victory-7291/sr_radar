import cv2
import os
from pathlib import Path

def extract_frames_from_video():
    """
    从MP4视频中提取每一帧并保存为JPG图像
    """
    # 硬编码的视频路径和输出目录
    video_path = "/home/wan/radar_video/video_recording_20250528_094527.mp4"  # 请修改为您的视频文件路径
    output_dir = "/home/wan/radar_video/"  # 输出目录
    
    # 创建输出目录（如果不存在）
    Path(output_dir).mkdir(parents=True, exist_ok=True)
    
    # 检查视频文件是否存在
    if not os.path.exists(video_path):
        print(f"错误：视频文件 '{video_path}' 不存在！")
        print("请修改脚本中的 video_path 变量为正确的视频文件路径。")
        return
    
    # 打开视频文件
    cap = cv2.VideoCapture(video_path)
    
    # 检查视频是否成功打开
    if not cap.isOpened():
        print(f"错误：无法打开视频文件 '{video_path}'")
        return
    
    # 获取视频信息
    total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    fps = cap.get(cv2.CAP_PROP_FPS)
    duration = total_frames / fps if fps > 0 else 0
    
    print(f"视频信息:")
    print(f"  文件路径: {video_path}")
    print(f"  总帧数: {total_frames}")
    print(f"  帧率: {fps:.2f} FPS")
    print(f"  时长: {duration:.2f} 秒")
    print(f"  输出目录: {output_dir}")
    print()
    
    frame_count = 0
    successful_saves = 0
    
    print("开始提取帧...")
    
    while True:
        # 读取下一帧
        ret, frame = cap.read()
        
        # 如果没有更多帧，退出循环
        if not ret:
            break
        
        # 生成输出文件名（6位数字，前面补零）
        frame_filename = f"frame_{frame_count:06d}.jpg"
        frame_path = os.path.join(output_dir, frame_filename)
        
        # 保存帧为JPG图像
        success = cv2.imwrite(frame_path, frame)
        
        if success:
            successful_saves += 1
        else:
            print(f"警告：保存帧 {frame_count} 失败")
        
        frame_count += 1
        
        # 每处理100帧显示一次进度
        if frame_count % 100 == 0:
            progress = (frame_count / total_frames) * 100
            print(f"进度: {frame_count}/{total_frames} 帧 ({progress:.1f}%)")
    
    # 释放视频捕获对象
    cap.release()
    
    print()
    print("提取完成！")
    print(f"总共处理了 {frame_count} 帧")
    print(f"成功保存了 {successful_saves} 张图像")
    print(f"图像保存在目录: {os.path.abspath(output_dir)}")

if __name__ == "__main__":
    print("=== 视频帧提取工具 ===")
    print()
    extract_frames_from_video() 
