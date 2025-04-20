wan@wan-Predator-PHN16-71:~/SR_v2/SR_radar$ colcon build
Starting >>> vision_interface
Starting >>> radar_interface
Starting >>> livox_interfaces
Starting >>> livox_sdk_vendor
Starting >>> cluster
Starting >>> hik_camera
Starting >>> localization
Finished <<< livox_sdk_vendor [1.00s]                                                                                                
Finished <<< livox_interfaces [5.65s]                                                                                                             
Starting >>> livox_ros2_driver
Finished <<< vision_interface [6.33s]                                                                                                    
Starting >>> dynamic_cloud
Starting >>> kalman_filter                                                                                                        
Starting >>> rosbag_player
Starting >>> tdt_vision
Finished <<< hik_camera [7.93s]                                                                                                    
Finished <<< radar_interface [8.84s]                                                                                                 
Starting >>> debug_map
Starting >>> dv_trigger                                                                                                           
Starting >>> judge_bridge
Starting >>> radar_decision
Finished <<< radar_decision [1.54s]                                                                                                       
--- stderr: livox_ros2_driver                                                                                                               
/usr/include/apr-1.0
apr-1
---
Finished <<< livox_ros2_driver [14.0s]
Finished <<< rosbag_player [13.3s]
Finished <<< cluster [20.4s]                                                                                                           
Finished <<< debug_map [14.4s]                                                                                                              
Finished <<< kalman_filter [17.6s]                                                                                                            
Finished <<< dynamic_cloud [19.2s]                                                                                                         
Finished <<< judge_bridge [17.7s]                                                                                                      
Finished <<< localization [28.5s]                                                                                                   
Finished <<< dv_trigger [21.0s]                                                                    
--- stderr: tdt_vision                                  
Using Cuda Version: 12.4 and TensorRT Version: 
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
  889 |     virtual IPluginV2* createPlugin(AsciiChar const* name, PluginFieldCollection const* fc) noexcept = 0;
      |                                                                                                        ^
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
 1038 |     virtual IPluginV2Layer* addPluginV2(ITensor* const* inputs, int32_t nbInputs, IPluginV2& plugin) noexcept = 0;
      |                                                                                                                 ^
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
 6947 |     IPluginV2Layer* addPluginV2(ITensor* const* inputs, int32_t nbInputs, IPluginV2& plugin) noexcept
      |                                                                                              ^~~~~~~~
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
Finished <<< tdt_vision [51.1s]

Summary: 16 packages finished [57.7s]
  2 packages had stderr output: livox_ros2_driver tdt_vision
wan@wan-Predator-PHN16-71:~/SR_v2/SR_radar$ 


