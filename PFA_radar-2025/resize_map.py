import cv2
import os

# 硬编码参数 - 可以在这里直接修改
input_path = "./images-2025/map_blue.jpg"  # 输入图像路径
output_path = "./images/map_blue.jpg"      # 输出图像路径
target_width = 2800                        # 目标宽度
target_height = 1500                       # 目标高度

def stretch_resize_image(input_path, output_path, target_width, target_height):
    """
    将输入图像直接拉伸调整到目标尺寸，不保持宽高比
    """
    # 读取原始图像
    original_image = cv2.imread(input_path)
    if original_image is None:
        print(f"无法读取图像: {input_path}")
        return False
    
    # 直接拉伸调整尺寸
    resized_image = cv2.resize(original_image, (target_width, target_height), 
                              interpolation=cv2.INTER_LINEAR)
    
    # 创建输出目录（如果不存在）
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    
    # 保存结果
    cv2.imwrite(output_path, resized_image)
    print(f"已将图像从 {original_image.shape[1]}x{original_image.shape[0]} 拉伸调整为 {target_width}x{target_height}")
    print(f"已保存到: {output_path}")
    return True

if __name__ == "__main__":
    # 执行图像拉伸调整
    stretch_resize_image(input_path, output_path, target_width, target_height)