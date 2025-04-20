wan@wan-Predator-PHN16-71:~/SR_v2/SR_radar$ colcon build
Starting >>> vision_interface
Starting >>> radar_interface
Starting >>> livox_interfaces
Starting >>> livox_sdk_vendor
Starting >>> cluster
Starting >>> hik_camera
Starting >>> localization
Starting >>> radar_decision
[1.307s] WARNING:colcon.colcon_cmake.task.cmake.build:Could not run installation step for package 'radar_decision' because it has no 'install' target
--- stderr: radar_decision
CMake Warning (dev) in CMakeLists.txt:
  No project() command is present.  The top-level CMakeLists.txt file must
  contain a literal, direct call to the project() command.  Add a line of
  code such as

    project(ProjectName)

  near the top of the file, but after cmake_minimum_required().

  CMake is pretending there is a "project(Project)" command on the first
  line.
This warning is for project developers.  Use -Wno-dev to suppress it.

---
Finished <<< radar_decision [0.63s]
Finished <<< livox_sdk_vendor [0.94s]                                 
Finished <<< livox_interfaces [5.22s]                                     
Starting >>> livox_ros2_driver                                            
Finished <<< vision_interface [6.88s]                                      
Starting >>> dynamic_cloud
Starting >>> kalman_filter
Starting >>> rosbag_player
Starting >>> tdt_vision
Finished <<< hik_camera [7.60s]                                          
Finished <<< radar_interface [8.87s]                                      
Starting >>> debug_map
Starting >>> dv_trigger
Starting >>> judge_bridge
Finished <<< cluster [19.1s]                                         
--- stderr: livox_ros2_driver
CMake Warning (dev) at CMakeLists.txt:31 (find_package):
  Policy CMP0074 is not set: find_package uses <PackageName>_ROOT variables.
  Run "cmake --help-policy CMP0074" for policy details.  Use the cmake_policy
  command to set the policy and suppress this warning.

  CMake variable PCL_ROOT is set to:

    /usr

  For compatibility, CMake is ignoring the variable.
This warning is for project developers.  Use -Wno-dev to suppress it.

/usr/include/apr-1.0
apr-1
---
Finished <<< livox_ros2_driver [13.9s]
Finished <<< rosbag_player [12.5s]                                      
Finished <<< debug_map [14.7s]                                          
Finished <<< kalman_filter [17.2s]                                       
--- stderr: judge_bridge                                                 
/home/wan/SR_v2/SR_radar/src/judge_bridge/src/judge_bridge.cpp: In member function ‘void JudgeBridgeNode::send_map_robot_data(const MatchResult&)’:
/home/wan/SR_v2/SR_radar/src/judge_bridge/src/judge_bridge.cpp:238:24: warning: unused variable ‘default_red_x’ [-Wunused-variable]
  238 |     constexpr uint16_t default_red_x = 210, default_red_y = 110;
      |                        ^~~~~~~~~~~~~
/home/wan/SR_v2/SR_radar/src/judge_bridge/src/judge_bridge.cpp:238:45: warning: unused variable ‘default_red_y’ [-Wunused-variable]
  238 |     constexpr uint16_t default_red_x = 210, default_red_y = 110;
      |                                             ^~~~~~~~~~~~~
---
Finished <<< judge_bridge [16.8s]
Finished <<< dynamic_cloud [19.0s]                                       
Finished <<< localization [28.0s]                                         
Finished <<< dv_trigger [21.2s]                                        
--- stderr: tdt_vision                                  
Using Cuda Version: 12.4 and TensorRT Version: 
CMake Warning (dev) in yolo/CMakeLists.txt:
  Policy CMP0104 is not set: CMAKE_CUDA_ARCHITECTURES now detected for NVCC,
  empty CUDA_ARCHITECTURES not allowed.  Run "cmake --help-policy CMP0104"
  for policy details.  Use the cmake_policy command to set the policy and
  suppress this warning.

  CUDA_ARCHITECTURES is empty for target "yolo".
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Warning (dev) in yolo/CMakeLists.txt:
  Policy CMP0104 is not set: CMAKE_CUDA_ARCHITECTURES now detected for NVCC,
  empty CUDA_ARCHITECTURES not allowed.  Run "cmake --help-policy CMP0104"
  for policy details.  Use the cmake_policy command to set the policy and
  suppress this warning.

  CUDA_ARCHITECTURES is empty for target "yolo".
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Warning (dev) in yolo/CMakeLists.txt:
  Policy CMP0104 is not set: CMAKE_CUDA_ARCHITECTURES now detected for NVCC,
  empty CUDA_ARCHITECTURES not allowed.  Run "cmake --help-policy CMP0104"
  for policy details.  Use the cmake_policy command to set the policy and
  suppress this warning.

  CUDA_ARCHITECTURES is empty for target "yolo".
This warning is for project developers.  Use -Wno-dev to suppress it.

nvcc warning : incompatible redefinition for option 'std', the last value of this option was used
nvcc warning : incompatible redefinition for option 'std', the last value of this option was used
nvcc warning : incompatible redefinition for option 'std', the last value of this option was used
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:889:102: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  889 |     virtual IPluginV2* createPlugin(AsciiChar const* name, PluginFieldCollection const* fc) noexcept = 0;
      |                                                                                                      ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:906:119: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  906 |     virtual IPluginV2* deserializePlugin(AsciiChar const* name, void const* serialData, size_t serialLength) noexcept
      |                                                                                                                       ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:970:31: warning: ‘IPluginCreator’ is deprecated [-Wdeprecated-declarations]
  970 | using IPluginCreator = v_1_0::IPluginCreator;
      |                               ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:833:22: note: declared here
  833 | class TRT_DEPRECATED IPluginCreator : public IPluginCreatorInterface
      |                      ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:970:45: warning: ‘IPluginCreator’ is deprecated [-Wdeprecated-declarations]
  970 | using IPluginCreator = v_1_0::IPluginCreator;
      |                                             ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:833:22: note: declared here
  833 | class TRT_DEPRECATED IPluginCreator : public IPluginCreatorInterface
      |                      ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:663:51: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  663 |     virtual IPluginV2& getPlugin() noexcept = 0;
      |                                                   ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:1038:111: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 1038 |     virtual IPluginV2Layer* addPluginV2(ITensor* const* inputs, int32_t nbInputs, IPluginV2& plugin) noexcept = 0;
      |                                                                                                               ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual void* nvinfer1::v_1_0::IGpuAllocator::allocateAsync(uint64_t, uint64_t, nvinfer1::AllocatorFlags, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1733:22: warning: ‘virtual void* nvinfer1::v_1_0::IGpuAllocator::allocate(uint64_t, uint64_t, nvinfer1::AllocatorFlags)’ is deprecated [-Wdeprecated-declarations]
 1733 |         return allocate(size, alignment, flags);
      |         ~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1634:38: note: declared here
 1634 |     TRT_DEPRECATED virtual void* allocate(
      |                                      ^~~~~   
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual bool nvinfer1::v_1_0::IGpuAllocator::deallocateAsync(void*, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1765:24: warning: ‘virtual bool nvinfer1::v_1_0::IGpuAllocator::deallocate(void*)’ is deprecated [-Wdeprecated-declarations]
 1765 |         return deallocate(memory);
      |         ~~~~~~~~~~~~~~~^~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1700:29: note: declared here
 1700 |     TRT_DEPRECATED virtual bool deallocate(void* const memory) noexcept = 0;
      |                             ^~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual void* nvinfer1::v_1_0::IOutputAllocator::reallocateOutputAsync(const char*, void*, uint64_t, uint64_t, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:3945:30: warning: ‘virtual void* nvinfer1::v_1_0::IOutputAllocator::reallocateOutput(const char*, void*, uint64_t, uint64_t)’ is deprecated [-Wdeprecated-declarations]
 3945 |         return reallocateOutput(tensorName, currentMemory, size, alignment);
      |         ~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:3914:30: note: declared here
 3914 |     TRT_DEPRECATED virtual void* reallocateOutput(
      |                              ^~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h: At global scope:
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:2704:32: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 2704 |     IPluginV2& getPlugin() noexcept
      |                                ^~~~    
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:6947:90: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 6947 |     IPluginV2Layer* addPluginV2(ITensor* const* inputs, int32_t nbInputs, IPluginV2& plugin) noexcept
      |                                                                                          ^~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7888:39: warning: ‘IInt8EntropyCalibrator’ is deprecated [-Wdeprecated-declarations]
 7888 | using IInt8EntropyCalibrator = v_1_0::IInt8EntropyCalibrator;
      |                                       ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7852:22: note: declared here
 7852 | class TRT_DEPRECATED IInt8EntropyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7888:61: warning: ‘IInt8EntropyCalibrator’ is deprecated [-Wdeprecated-declarations]
 7888 | using IInt8EntropyCalibrator = v_1_0::IInt8EntropyCalibrator;
      |                                                             ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7852:22: note: declared here
 7852 | class TRT_DEPRECATED IInt8EntropyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7928:40: warning: ‘IInt8EntropyCalibrator2’ is deprecated [-Wdeprecated-declarations]
 7928 | using IInt8EntropyCalibrator2 = v_1_0::IInt8EntropyCalibrator2;
      |                                        ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7892:22: note: declared here
 7892 | class TRT_DEPRECATED IInt8EntropyCalibrator2 : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7928:63: warning: ‘IInt8EntropyCalibrator2’ is deprecated [-Wdeprecated-declarations]
 7928 | using IInt8EntropyCalibrator2 = v_1_0::IInt8EntropyCalibrator2;
      |                                                               ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7892:22: note: declared here
 7892 | class TRT_DEPRECATED IInt8EntropyCalibrator2 : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7967:38: warning: ‘IInt8MinMaxCalibrator’ is deprecated [-Wdeprecated-declarations]
 7967 | using IInt8MinMaxCalibrator = v_1_0::IInt8MinMaxCalibrator;
      |                                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7932:22: note: declared here
 7932 | class TRT_DEPRECATED IInt8MinMaxCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7967:59: warning: ‘IInt8MinMaxCalibrator’ is deprecated [-Wdeprecated-declarations]
 7967 | using IInt8MinMaxCalibrator = v_1_0::IInt8MinMaxCalibrator;
      |                                                           ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7932:22: note: declared here
 7932 | class TRT_DEPRECATED IInt8MinMaxCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:8047:38: warning: ‘IInt8LegacyCalibrator’ is deprecated [-Wdeprecated-declarations]
 8047 | using IInt8LegacyCalibrator = v_1_0::IInt8LegacyCalibrator;
      |                                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7971:22: note: declared here
 7971 | class TRT_DEPRECATED IInt8LegacyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:8047:59: warning: ‘IInt8LegacyCalibrator’ is deprecated [-Wdeprecated-declarations]
 8047 | using IInt8LegacyCalibrator = v_1_0::IInt8LegacyCalibrator;
      |                                                           ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7971:22: note: declared here
 7971 | class TRT_DEPRECATED IInt8LegacyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:889:102: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  889 |     virtual IPluginV2* createPlugin(AsciiChar const* name, PluginFieldCollection const* fc) noexcept = 0;
      |                                                                                                      ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:906:119: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  906 |     virtual IPluginV2* deserializePlugin(AsciiChar const* name, void const* serialData, size_t serialLength) noexcept
      |                                                                                                                       ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:970:31: warning: ‘IPluginCreator’ is deprecated [-Wdeprecated-declarations]
  970 | using IPluginCreator = v_1_0::IPluginCreator;
      |                               ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:833:22: note: declared here
  833 | class TRT_DEPRECATED IPluginCreator : public IPluginCreatorInterface
      |                      ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:970:45: warning: ‘IPluginCreator’ is deprecated [-Wdeprecated-declarations]
  970 | using IPluginCreator = v_1_0::IPluginCreator;
      |                                             ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:833:22: note: declared here
  833 | class TRT_DEPRECATED IPluginCreator : public IPluginCreatorInterface
      |                      ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:663:51: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  663 |     virtual IPluginV2& getPlugin() noexcept = 0;
      |                                                   ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:1038:111: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 1038 |     virtual IPluginV2Layer* addPluginV2(ITensor* const* inputs, int32_t nbInputs, IPluginV2& plugin) noexcept = 0;
      |                                                                                                               ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual void* nvinfer1::v_1_0::IGpuAllocator::allocateAsync(uint64_t, uint64_t, nvinfer1::AllocatorFlags, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1733:22: warning: ‘virtual void* nvinfer1::v_1_0::IGpuAllocator::allocate(uint64_t, uint64_t, nvinfer1::AllocatorFlags)’ is deprecated [-Wdeprecated-declarations]
 1733 |         return allocate(size, alignment, flags);
      |         ~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1634:38: note: declared here
 1634 |     TRT_DEPRECATED virtual void* allocate(
      |                                      ^~~~~   
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual bool nvinfer1::v_1_0::IGpuAllocator::deallocateAsync(void*, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1765:24: warning: ‘virtual bool nvinfer1::v_1_0::IGpuAllocator::deallocate(void*)’ is deprecated [-Wdeprecated-declarations]
 1765 |         return deallocate(memory);
      |         ~~~~~~~~~~~~~~~^~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1700:29: note: declared here
 1700 |     TRT_DEPRECATED virtual bool deallocate(void* const memory) noexcept = 0;
      |                             ^~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual void* nvinfer1::v_1_0::IOutputAllocator::reallocateOutputAsync(const char*, void*, uint64_t, uint64_t, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:3945:30: warning: ‘virtual void* nvinfer1::v_1_0::IOutputAllocator::reallocateOutput(const char*, void*, uint64_t, uint64_t)’ is deprecated [-Wdeprecated-declarations]
 3945 |         return reallocateOutput(tensorName, currentMemory, size, alignment);
      |         ~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:3914:30: note: declared here
 3914 |     TRT_DEPRECATED virtual void* reallocateOutput(
      |                              ^~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h: At global scope:
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:2704:32: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 2704 |     IPluginV2& getPlugin() noexcept
      |                                ^~~~    
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:6947:90: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 6947 |     IPluginV2Layer* addPluginV2(ITensor* const* inputs, int32_t nbInputs, IPluginV2& plugin) noexcept
      |                                                                                          ^~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7888:39: warning: ‘IInt8EntropyCalibrator’ is deprecated [-Wdeprecated-declarations]
 7888 | using IInt8EntropyCalibrator = v_1_0::IInt8EntropyCalibrator;
      |                                       ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7852:22: note: declared here
 7852 | class TRT_DEPRECATED IInt8EntropyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7888:61: warning: ‘IInt8EntropyCalibrator’ is deprecated [-Wdeprecated-declarations]
 7888 | using IInt8EntropyCalibrator = v_1_0::IInt8EntropyCalibrator;
      |                                                             ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7852:22: note: declared here
 7852 | class TRT_DEPRECATED IInt8EntropyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7928:40: warning: ‘IInt8EntropyCalibrator2’ is deprecated [-Wdeprecated-declarations]
 7928 | using IInt8EntropyCalibrator2 = v_1_0::IInt8EntropyCalibrator2;
      |                                        ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7892:22: note: declared here
 7892 | class TRT_DEPRECATED IInt8EntropyCalibrator2 : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7928:63: warning: ‘IInt8EntropyCalibrator2’ is deprecated [-Wdeprecated-declarations]
 7928 | using IInt8EntropyCalibrator2 = v_1_0::IInt8EntropyCalibrator2;
      |                                                               ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7892:22: note: declared here
 7892 | class TRT_DEPRECATED IInt8EntropyCalibrator2 : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7967:38: warning: ‘IInt8MinMaxCalibrator’ is deprecated [-Wdeprecated-declarations]
 7967 | using IInt8MinMaxCalibrator = v_1_0::IInt8MinMaxCalibrator;
      |                                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7932:22: note: declared here
 7932 | class TRT_DEPRECATED IInt8MinMaxCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7967:59: warning: ‘IInt8MinMaxCalibrator’ is deprecated [-Wdeprecated-declarations]
 7967 | using IInt8MinMaxCalibrator = v_1_0::IInt8MinMaxCalibrator;
      |                                                           ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7932:22: note: declared here
 7932 | class TRT_DEPRECATED IInt8MinMaxCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:8047:38: warning: ‘IInt8LegacyCalibrator’ is deprecated [-Wdeprecated-declarations]
 8047 | using IInt8LegacyCalibrator = v_1_0::IInt8LegacyCalibrator;
      |                                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7971:22: note: declared here
 7971 | class TRT_DEPRECATED IInt8LegacyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:8047:59: warning: ‘IInt8LegacyCalibrator’ is deprecated [-Wdeprecated-declarations]
 8047 | using IInt8LegacyCalibrator = v_1_0::IInt8LegacyCalibrator;
      |                                                           ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7971:22: note: declared here
 7971 | class TRT_DEPRECATED IInt8LegacyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:889:102: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  889 |     virtual IPluginV2* createPlugin(AsciiChar const* name, PluginFieldCollection const* fc) noexcept = 0;
      |                                                                                                      ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:906:119: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  906 |     virtual IPluginV2* deserializePlugin(AsciiChar const* name, void const* serialData, size_t serialLength) noexcept
      |                                                                                                                       ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:970:31: warning: ‘IPluginCreator’ is deprecated [-Wdeprecated-declarations]
  970 | using IPluginCreator = v_1_0::IPluginCreator;
      |                               ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:833:22: note: declared here
  833 | class TRT_DEPRECATED IPluginCreator : public IPluginCreatorInterface
      |                      ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:970:45: warning: ‘IPluginCreator’ is deprecated [-Wdeprecated-declarations]
  970 | using IPluginCreator = v_1_0::IPluginCreator;
      |                                             ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:833:22: note: declared here
  833 | class TRT_DEPRECATED IPluginCreator : public IPluginCreatorInterface
      |                      ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:663:51: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  663 |     virtual IPluginV2& getPlugin() noexcept = 0;
      |                                                   ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:1038:111: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 1038 |     virtual IPluginV2Layer* addPluginV2(ITensor* const* inputs, int32_t nbInputs, IPluginV2& plugin) noexcept = 0;
      |                                                                                                               ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual void* nvinfer1::v_1_0::IGpuAllocator::allocateAsync(uint64_t, uint64_t, nvinfer1::AllocatorFlags, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1733:22: warning: ‘virtual void* nvinfer1::v_1_0::IGpuAllocator::allocate(uint64_t, uint64_t, nvinfer1::AllocatorFlags)’ is deprecated [-Wdeprecated-declarations]
 1733 |         return allocate(size, alignment, flags);
      |         ~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1634:38: note: declared here
 1634 |     TRT_DEPRECATED virtual void* allocate(
      |                                      ^~~~~   
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual bool nvinfer1::v_1_0::IGpuAllocator::deallocateAsync(void*, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1765:24: warning: ‘virtual bool nvinfer1::v_1_0::IGpuAllocator::deallocate(void*)’ is deprecated [-Wdeprecated-declarations]
 1765 |         return deallocate(memory);
      |         ~~~~~~~~~~~~~~~^~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1700:29: note: declared here
 1700 |     TRT_DEPRECATED virtual bool deallocate(void* const memory) noexcept = 0;
      |                             ^~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual void* nvinfer1::v_1_0::IOutputAllocator::reallocateOutputAsync(const char*, void*, uint64_t, uint64_t, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:3945:30: warning: ‘virtual void* nvinfer1::v_1_0::IOutputAllocator::reallocateOutput(const char*, void*, uint64_t, uint64_t)’ is deprecated [-Wdeprecated-declarations]
 3945 |         return reallocateOutput(tensorName, currentMemory, size, alignment);
      |         ~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:3914:30: note: declared here
 3914 |     TRT_DEPRECATED virtual void* reallocateOutput(
      |                              ^~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h: At global scope:
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:2704:32: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 2704 |     IPluginV2& getPlugin() noexcept
      |                                ^~~~    
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:6947:90: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 6947 |     IPluginV2Layer* addPluginV2(ITensor* const* inputs, int32_t nbInputs, IPluginV2& plugin) noexcept
      |                                                                                          ^~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7888:39: warning: ‘IInt8EntropyCalibrator’ is deprecated [-Wdeprecated-declarations]
 7888 | using IInt8EntropyCalibrator = v_1_0::IInt8EntropyCalibrator;
      |                                       ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7852:22: note: declared here
 7852 | class TRT_DEPRECATED IInt8EntropyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7888:61: warning: ‘IInt8EntropyCalibrator’ is deprecated [-Wdeprecated-declarations]
 7888 | using IInt8EntropyCalibrator = v_1_0::IInt8EntropyCalibrator;
      |                                                             ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7852:22: note: declared here
 7852 | class TRT_DEPRECATED IInt8EntropyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7928:40: warning: ‘IInt8EntropyCalibrator2’ is deprecated [-Wdeprecated-declarations]
 7928 | using IInt8EntropyCalibrator2 = v_1_0::IInt8EntropyCalibrator2;
      |                                        ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7892:22: note: declared here
 7892 | class TRT_DEPRECATED IInt8EntropyCalibrator2 : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7928:63: warning: ‘IInt8EntropyCalibrator2’ is deprecated [-Wdeprecated-declarations]
 7928 | using IInt8EntropyCalibrator2 = v_1_0::IInt8EntropyCalibrator2;
      |                                                               ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7892:22: note: declared here
 7892 | class TRT_DEPRECATED IInt8EntropyCalibrator2 : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7967:38: warning: ‘IInt8MinMaxCalibrator’ is deprecated [-Wdeprecated-declarations]
 7967 | using IInt8MinMaxCalibrator = v_1_0::IInt8MinMaxCalibrator;
      |                                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7932:22: note: declared here
 7932 | class TRT_DEPRECATED IInt8MinMaxCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7967:59: warning: ‘IInt8MinMaxCalibrator’ is deprecated [-Wdeprecated-declarations]
 7967 | using IInt8MinMaxCalibrator = v_1_0::IInt8MinMaxCalibrator;
      |                                                           ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7932:22: note: declared here
 7932 | class TRT_DEPRECATED IInt8MinMaxCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:8047:38: warning: ‘IInt8LegacyCalibrator’ is deprecated [-Wdeprecated-declarations]
 8047 | using IInt8LegacyCalibrator = v_1_0::IInt8LegacyCalibrator;
      |                                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7971:22: note: declared here
 7971 | class TRT_DEPRECATED IInt8LegacyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:8047:59: warning: ‘IInt8LegacyCalibrator’ is deprecated [-Wdeprecated-declarations]
 8047 | using IInt8LegacyCalibrator = v_1_0::IInt8LegacyCalibrator;
      |                                                           ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7971:22: note: declared here
 7971 | class TRT_DEPRECATED IInt8LegacyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
In file included from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntimeCommon.h:34,
                 from /home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:22,
                 from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:27,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:889:104: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  889 | in(AsciiChar const* name, PluginFieldCollection const* fc) noexcept = 0;
      |                                                                       ^

/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:907:11: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  907 |         = 0;
      |           ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:970:31: warning: ‘IPluginCreator’ is deprecated [-Wdeprecated-declarations]
  970 | using IPluginCreator = v_1_0::IPluginCreator;
      |                               ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:833:22: note: declared here
  833 | class TRT_DEPRECATED IPluginCreator : public IPluginCreatorInterface
      |                      ^~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:970:45: warning: ‘IPluginCreator’ is deprecated [-Wdeprecated-declarations]
  970 | using IPluginCreator = v_1_0::IPluginCreator;
      |                                             ^
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:833:22: note: declared here
  833 | class TRT_DEPRECATED IPluginCreator : public IPluginCreatorInterface
      |                      ^~~~~~~~~~~~~~
In file included from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:27,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:663:47: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
  663 |     virtual IPluginV2& getPlugin() noexcept = 0;
      |                                               ^
In file included from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntimeCommon.h:34,
                 from /home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:22,
                 from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:27,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
In file included from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:27,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:1038:113: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 1038 | ensor* const* inputs, int32_t nbInputs, IPluginV2& plugin) noexcept = 0;
      |                                                                       ^

In file included from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntimeCommon.h:34,
                 from /home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:22,
                 from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:27,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
In file included from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual void* nvinfer1::v_1_0::IGpuAllocator::allocateAsync(uint64_t, uint64_t, nvinfer1::AllocatorFlags, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1733:24: warning: ‘virtual void* nvinfer1::v_1_0::IGpuAllocator::allocate(uint64_t, uint64_t, nvinfer1::AllocatorFlags)’ is deprecated [-Wdeprecated-declarations]
 1733 |         return allocate(size, alignment, flags);
      |                ~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1634:34: note: declared here
 1634 |     TRT_DEPRECATED virtual void* allocate(
      |                                  ^~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual bool nvinfer1::v_1_0::IGpuAllocator::deallocateAsync(void*, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1765:26: warning: ‘virtual bool nvinfer1::v_1_0::IGpuAllocator::deallocate(void*)’ is deprecated [-Wdeprecated-declarations]
 1765 |         return deallocate(memory);
      |                ~~~~~~~~~~^~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:1700:33: note: declared here
 1700 |     TRT_DEPRECATED virtual bool deallocate(void* const memory) noexcept = 0;
      |                                 ^~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h: In member function ‘virtual void* nvinfer1::v_1_0::IOutputAllocator::reallocateOutputAsync(const char*, void*, uint64_t, uint64_t, cudaStream_t)’:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:3945:32: warning: ‘virtual void* nvinfer1::v_1_0::IOutputAllocator::reallocateOutput(const char*, void*, uint64_t, uint64_t)’ is deprecated [-Wdeprecated-declarations]
 3945 |         return reallocateOutput(tensorName, currentMemory, size, alignment);
      |                ~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:3914:34: note: declared here
 3914 |     TRT_DEPRECATED virtual void* reallocateOutput(
      |                                  ^~~~~~~~~~~~~~~~
In file included from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:9,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h: At global scope:
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:2704:28: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 2704 |     IPluginV2& getPlugin() noexcept
      |                            ^~~~~~~~
In file included from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntimeCommon.h:34,
                 from /home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:22,
                 from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:27,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
In file included from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:9,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:6947:94: warning: ‘IPluginV2’ is deprecated [-Wdeprecated-declarations]
 6947 | V2(ITensor* const* inputs, int32_t nbInputs, IPluginV2& plugin) noexcept
      |                                                                 ^~~~~~~~

In file included from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntimeCommon.h:34,
                 from /home/wan/TensorRT-10.7.0.23/include/NvInferImpl.h:22,
                 from /home/wan/TensorRT-10.7.0.23/include/NvInferRuntime.h:27,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInferRuntimePlugin.h:132:22: note: declared here
  132 | class TRT_DEPRECATED IPluginV2
      |                      ^~~~~~~~~
In file included from /home/wan/SR_v2/SR_radar/src/tdt_vision/yolo/yolos.hpp:9,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/include/detect.h:8,
                 from /home/wan/SR_v2/SR_radar/src/tdt_vision/detect/src/detect.cpp:1:
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7888:39: warning: ‘IInt8EntropyCalibrator’ is deprecated [-Wdeprecated-declarations]
 7888 | using IInt8EntropyCalibrator = v_1_0::IInt8EntropyCalibrator;
      |                                       ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7852:22: note: declared here
 7852 | class TRT_DEPRECATED IInt8EntropyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7888:61: warning: ‘IInt8EntropyCalibrator’ is deprecated [-Wdeprecated-declarations]
 7888 | using IInt8EntropyCalibrator = v_1_0::IInt8EntropyCalibrator;
      |                                                             ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7852:22: note: declared here
 7852 | class TRT_DEPRECATED IInt8EntropyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7928:40: warning: ‘IInt8EntropyCalibrator2’ is deprecated [-Wdeprecated-declarations]
 7928 | using IInt8EntropyCalibrator2 = v_1_0::IInt8EntropyCalibrator2;
      |                                        ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7892:22: note: declared here
 7892 | class TRT_DEPRECATED IInt8EntropyCalibrator2 : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7928:63: warning: ‘IInt8EntropyCalibrator2’ is deprecated [-Wdeprecated-declarations]
 7928 | using IInt8EntropyCalibrator2 = v_1_0::IInt8EntropyCalibrator2;
      |                                                               ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7892:22: note: declared here
 7892 | class TRT_DEPRECATED IInt8EntropyCalibrator2 : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7967:38: warning: ‘IInt8MinMaxCalibrator’ is deprecated [-Wdeprecated-declarations]
 7967 | using IInt8MinMaxCalibrator = v_1_0::IInt8MinMaxCalibrator;
      |                                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7932:22: note: declared here
 7932 | class TRT_DEPRECATED IInt8MinMaxCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7967:59: warning: ‘IInt8MinMaxCalibrator’ is deprecated [-Wdeprecated-declarations]
 7967 | using IInt8MinMaxCalibrator = v_1_0::IInt8MinMaxCalibrator;
      |                                                           ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7932:22: note: declared here
 7932 | class TRT_DEPRECATED IInt8MinMaxCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:8047:38: warning: ‘IInt8LegacyCalibrator’ is deprecated [-Wdeprecated-declarations]
 8047 | using IInt8LegacyCalibrator = v_1_0::IInt8LegacyCalibrator;
      |                                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7971:22: note: declared here
 7971 | class TRT_DEPRECATED IInt8LegacyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:8047:59: warning: ‘IInt8LegacyCalibrator’ is deprecated [-Wdeprecated-declarations]
 8047 | using IInt8LegacyCalibrator = v_1_0::IInt8LegacyCalibrator;
      |                                                           ^
/home/wan/TensorRT-10.7.0.23/include/NvInfer.h:7971:22: note: declared here
 7971 | class TRT_DEPRECATED IInt8LegacyCalibrator : public IInt8Calibrator
      |                      ^~~~~~~~~~~~~~~~~~~~~
---
Finished <<< tdt_vision [51.4s]

Summary: 16 packages finished [58.7s]
  4 packages had stderr output: judge_bridge livox_ros2_driver radar_decision tdt_vision

