#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@FileName：   test_integration.py
@Description：测试PFA_radar-2025与ultra_radar功能集成
@Author：     Assistant
@Version:     1.0
@Time：       2025/01/XX
"""

import yaml
import sys
import os

def test_config_loading():
    """测试配置文件加载"""
    print("=" * 50)
    print("🔧 测试配置文件加载...")
    
    try:
        with open("config.yaml", "r", encoding="utf-8") as f:
            config = yaml.safe_load(f)
        
        # 检查智能预测配置
        blind_zone = config.get('blind_zone', {})
        intelligent_prediction = blind_zone.get('intelligent_prediction', {})
        
        print(f"✅ 配置文件加载成功")
        print(f"📊 智能预测启用状态: {intelligent_prediction.get('enabled', False)}")
        print(f"📊 d_factor: {intelligent_prediction.get('d_factor', 0.01)}")
        print(f"📊 cos_factor: {intelligent_prediction.get('cos_factor', 0.003)}")
        print(f"📊 轨迹点限制: {intelligent_prediction.get('trajectory_limit', 105)}")
        
        # 检查预测点数据
        points = blind_zone.get('points', {})
        print(f"📍 配置的机器人数量: {len(points)}")
        for robot_id, robot_points in points.items():
            print(f"   {robot_id}: {len(robot_points)}个预测点")
        
        return True
        
    except Exception as e:
        print(f"❌ 配置文件加载失败: {e}")
        return False

def test_intelligent_prediction():
    """测试智能预测模块"""
    print("=" * 50)
    print("🤖 测试智能预测模块...")
    
    try:
        from guess_plt import Predict
        
        # 创建预测器实例
        predictor = Predict(d_factor=0.01, cos_factor=0.003, trajectory_limit=10, clear_threshold=5)
        
        # 测试添加轨迹点
        test_trajectory = [(100, 200), (120, 220), (140, 240), (160, 260)]
        for point in test_trajectory:
            predictor.add_point(point)
        
        print(f"✅ 智能预测模块加载成功")
        print(f"📊 轨迹点数量: {len(predictor.trajectory)}")
        print(f"📊 配置参数: d_factor={predictor.d_factor}, cos_factor={predictor.cos_factor}")
        
        # 测试预测功能
        test_guess_points = [(200, 300), (180, 280), (220, 320)]
        predicted = predictor.predict_point(test_guess_points)
        print(f"🎯 预测结果: {predicted}")
        
        return True
        
    except ImportError as e:
        print(f"❌ 智能预测模块导入失败: {e}")
        return False
    except Exception as e:
        print(f"❌ 智能预测测试失败: {e}")
        return False

def test_visualization_tools():
    """测试可视化工具"""
    print("=" * 50)
    print("🎨 测试可视化工具...")
    
    tools_status = {}
    
    # 测试RMUC_axis.py
    try:
        print("📊 测试RMUC坐标系可视化...")
        # 不实际运行，只检查语法
        with open("RMUC_axis.py", "r", encoding="utf-8") as f:
            content = f.read()
        compile(content, "RMUC_axis.py", "exec")
        tools_status["RMUC_axis.py"] = "✅ 语法正确"
    except Exception as e:
        tools_status["RMUC_axis.py"] = f"❌ 错误: {e}"
    
    # 测试PNG_draw.py
    try:
        print("🖼️  测试PNG地图编辑器...")
        with open("PNG_draw.py", "r", encoding="utf-8") as f:
            content = f.read()
        compile(content, "PNG_draw.py", "exec")
        tools_status["PNG_draw.py"] = "✅ 语法正确"
    except Exception as e:
        tools_status["PNG_draw.py"] = f"❌ 错误: {e}"
    
    # 测试QT_串口助手.py
    try:
        print("📡 测试QT串口助手...")
        with open("QT_串口助手.py", "r", encoding="utf-8") as f:
            content = f.read()
        compile(content, "QT_串口助手.py", "exec")
        tools_status["QT_串口助手.py"] = "✅ 语法正确"
    except Exception as e:
        tools_status["QT_串口助手.py"] = f"❌ 错误: {e}"
    
    # 显示结果
    for tool, status in tools_status.items():
        print(f"   {tool}: {status}")
    
    return all("✅" in status for status in tools_status.values())

def test_main_integration():
    """测试主程序集成"""
    print("=" * 50)
    print("🔄 测试主程序集成...")
    
    try:
        # 检查main.py的语法
        with open("main.py", "r", encoding="utf-8") as f:
            content = f.read()
        
        # 检查关键导入和初始化
        if "from guess_plt import Predict" in content:
            print("✅ 智能预测模块已导入")
        else:
            print("❌ 智能预测模块未正确导入")
            return False
        
        if "INTELLIGENT_PREDICTION_ENABLED" in content:
            print("✅ 智能预测标志已定义")
        else:
            print("❌ 智能预测标志未定义")
            return False
        
        if "guess_predict[robot_id] = Predict(" in content:
            print("✅ 智能预测器初始化已集成")
        else:
            print("❌ 智能预测器初始化未集成")
            return False
        
        if "guess_predict[name].add_point" in content:
            print("✅ 轨迹更新已集成到滤波器")
        else:
            print("❌ 轨迹更新未集成到滤波器")
            return False
        
        print("✅ 主程序集成检查通过")
        return True
        
    except Exception as e:
        print(f"❌ 主程序集成检查失败: {e}")
        return False

def print_usage_guide():
    """打印使用指南"""
    print("=" * 50)
    print("📖 集成后的使用指南")
    print("=" * 50)
    
    print("🔧 配置文件管理:")
    print("   - 编辑 config.yaml 中的 blind_zone.intelligent_prediction 部分")
    print("   - 调整预测算法参数: d_factor, cos_factor, trajectory_limit")
    print("   - 修改预测点位: blind_zone.points")
    
    print("\n🤖 智能预测功能:")
    print("   - 设置 intelligent_prediction.enabled: True 启用")
    print("   - 算法会根据机器人轨迹智能排序预测点")
    print("   - 自动回退到简单预测算法（如果智能预测失败）")
    
    print("\n🛠️ 可视化工具:")
    print("   - python RMUC_axis.py    # 查看战场坐标系和预测点")
    print("   - python PNG_draw.py     # 图形化编辑地图掩码")
    print("   - python QT_串口助手.py  # 串口通信调试")
    
    print("\n🎯 运行主程序:")
    print("   - python main.py         # 启动雷达系统")
    print("   - 查看控制台输出的智能预测状态信息")
    
    print("\n📊 监控和调试:")
    print("   - 观察控制台的预测更新日志")
    print("   - 使用可视化工具验证预测点合理性")
    print("   - 根据实际效果调整配置参数")

def main():
    """主测试函数"""
    print("🚀 PFA_radar-2025 x ultra_radar 集成测试")
    print("=" * 50)
    
    # 检查当前目录
    if not os.path.exists("config.yaml"):
        print("❌ 请在PFA_radar-2025目录下运行此脚本")
        return
    
    # 运行所有测试
    tests = [
        ("配置文件加载", test_config_loading),
        ("智能预测模块", test_intelligent_prediction),
        ("可视化工具", test_visualization_tools),
        ("主程序集成", test_main_integration),
    ]
    
    results = {}
    for test_name, test_func in tests:
        try:
            results[test_name] = test_func()
        except Exception as e:
            print(f"❌ 测试 {test_name} 出现异常: {e}")
            results[test_name] = False
    
    # 总结结果
    print("=" * 50)
    print("📋 测试结果总结:")
    success_count = 0
    for test_name, success in results.items():
        status = "✅ 通过" if success else "❌ 失败"
        print(f"   {test_name}: {status}")
        if success:
            success_count += 1
    
    print(f"\n🎯 总体结果: {success_count}/{len(tests)} 测试通过")
    
    if success_count == len(tests):
        print("🎉 集成测试全部通过！系统已成功集成ultra_radar的优秀功能。")
        print_usage_guide()
    else:
        print("⚠️  部分测试失败，请检查错误信息并修复问题。")

if __name__ == "__main__":
    main() 