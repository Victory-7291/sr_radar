wan@wan-Predator-PHN16-71:~/SR_v2/SR_radar$ colcon build
Starting >>> vision_interface
Starting >>> radar_interface
Starting >>> livox_interfaces
Starting >>> livox_sdk_vendor
Starting >>> cluster
Starting >>> hik_camera
Starting >>> localization
Starting >>> radar_decision
Finished <<< livox_sdk_vendor [0.84s]                                                                                                
--- stderr: radar_decision
Error parsing '/home/wan/SR_v2/SR_radar/src/radar_decision/package.xml':
Traceback (most recent call last):
  File "/usr/local/lib/python3.10/dist-packages/catkin_pkg/package.py", line 610, in parse_package_string
    root = dom.parseString(data)
  File "/usr/lib/python3.10/xml/dom/minidom.py", line 2000, in parseString
    return expatbuilder.parseString(string)
  File "/usr/lib/python3.10/xml/dom/expatbuilder.py", line 925, in parseString
    return builder.parseString(string)
  File "/usr/lib/python3.10/xml/dom/expatbuilder.py", line 223, in parseString
    parser.Parse(string, True)
xml.parsers.expat.ExpatError: no element found: line 1, column 0

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/opt/ros/humble/share/ament_cmake_core/cmake/core/package_xml_2_cmake.py", line 150, in <module>
    main()
  File "/opt/ros/humble/share/ament_cmake_core/cmake/core/package_xml_2_cmake.py", line 53, in main
    raise e
  File "/opt/ros/humble/share/ament_cmake_core/cmake/core/package_xml_2_cmake.py", line 49, in main
    package = parse_package_string(
  File "/usr/local/lib/python3.10/dist-packages/catkin_pkg/package.py", line 612, in parse_package_string
    raise InvalidPackage('The manifest contains invalid XML:\n%s' % ex, filename)
catkin_pkg.package.InvalidPackage: Error(s) in package '/home/wan/SR_v2/SR_radar/src/radar_decision/package.xml':
The manifest contains invalid XML:
no element found: line 1, column 0
CMake Error at /opt/ros/humble/share/ament_cmake_core/cmake/core/ament_package_xml.cmake:95 (message):
  execute_process(/usr/bin/python3
  /opt/ros/humble/share/ament_cmake_core/cmake/core/package_xml_2_cmake.py
  /home/wan/SR_v2/SR_radar/src/radar_decision/package.xml
  /home/wan/SR_v2/SR_radar/build/radar_decision/ament_cmake_core/package.cmake)
  returned error code 1
Call Stack (most recent call first):
  /opt/ros/humble/share/ament_cmake_core/cmake/core/ament_package_xml.cmake:49 (_ament_package_xml)
  /opt/ros/humble/share/ament_cmake_auto/cmake/ament_auto_find_build_dependencies.cmake:42 (ament_package_xml)
  CMakeLists.txt:16 (ament_auto_find_build_dependencies)


---
Failed   <<< radar_decision [0.85s, exited with code 1]
Aborted  <<< hik_camera [1.33s]                                                                                                                 
Aborted  <<< livox_interfaces [1.96s]                                                                                                           
Aborted  <<< vision_interface [2.43s]                                                                                                  
Aborted  <<< radar_interface [2.46s]
Aborted  <<< cluster [4.24s]                                                                    
Aborted  <<< localization [4.27s]

Summary: 1 package finished [4.94s]
  1 package failed: radar_decision
  6 packages aborted: cluster hik_camera livox_interfaces localization radar_interface vision_interface
  1 package had stderr output: radar_decision
  8 packages not processed
wan@wan-Predator-PHN16-71:~/SR_v2/SR_radar$ 


