# 反解器对应优化库依赖安装
1. 源码编译 https://github.com/stevengj/nlopt ，同时要将库所在的路径添加到环境变量LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib
2. https://bitbucket.org/traclabs/trac_ik/src/master/ 反解器比KDL成功率高多了
3. track_ik 用catkin相关工具编译时，可以将track_ik_python 删掉，避免装swig依赖。

# ur ros 新版驱动 Universal_Robots_ROS_Driver(都使用最新版)
1. 可以用moveit_setup_assistant来修改ur5_moveit_config
2. ur5的模型文件在universal_robot/ur_description中
3. https://roboticscasual.com/ros-tutorial-how-to-create-a-moveit-config-for-the-ur5-and-a-gripper/ 给臂加一个手,看能否直接参与运动规划。
4. https://github.com/UniversalRobots/Universal_Robots_ROS_Driver
5. https://github.com/ros-industrial/universal_robot
6. https://github.com/UniversalRobots/Universal_Robots_Client_Library

# ur simulation test (https://github.com/ros-industrial/universal_robot)
- roslaunch ur_gazebo ur5_bringup.launch  (use ur bringup launch for controling the real robot)
- roslaunch ur5_moveit_config moveit_planning_execution.launch sim:=true
- roslaunch ur5_moveit_config moveit_rviz.launch


# ros qt plugin安装
1. ROS Qt Creator Plug-in (https://ros-qtc-plugin.readthedocs.io/en/latest/_source/Improve-ROS-Qt-Creator-Plugin-Developers-ONLY.html)
2. git clone git@github.com:ros-industrial/ros_qtc_plugin.git
3. git checkout devel
4. ./setup.py
5. cmake -B build -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="/tmp/qtc_sdk/Tools/QtCreator;/tmp/qtc_sdk/6.4.0/gcc_64"
6. cmake --build build --target package
7. 将/tmp里头的qtc_sdk复制到自定义的software目录中
8. 运行/home/zkkj/software/qtc_sdk/Tools/QtCreator/bin/qtcreator.sh
9. Qtcreator主界面右下角的link with qt（有可能不好使），选择qtc_sdk中对应的qt库。也可以手动点菜单Edit→Preference→Kits→Qt Version→ Add 直接添加qmake所在路径，然后再Kits选择好Qt version。然后从新建立项目。
10. 安装编译好的ros_qt_plugin: 在qtcreator界面上点Help→about plugin→install plugin→Browse, 然后选择编译好的插件zip压缩包（/home/zkkj/software/ros_qtc_plugin/build/ROSProjectManager-11.0-Linux-x86_64.zip），安装完成后重启qtcreator即可。
11. ros_qt_plugin对应的ros工作空间（项目管理文件）是 *.workspace，这个文件只能通过有ros_qt_plugin的qtcreator直接创建ros项目。后期打开ros项目也是打开 *.workspace文件。
12. ros_qt_plugin只会保留ros本身和当前工作空间的环境变量，是因为qtcreator Build 里头的Build environment里强制设置了一些环境变量，无法取消这些强制设置的变量(选中相应的强制设置变量后，点击右侧的Reset，重新编译后又会自动生成)，建议将moveit的代码复制到工作空间中。。
13. 建立ros项目的时候，qtcreator里头的build system要选择为catkinMake,最好不要选为catkinTools（和moveit联合编译可以用）
 
# 老版本的ur ros 驱动  ur_modern_driver
1. https://github.com/ros-industrial/ur_modern_driver （ur_modern_driver has been deprecated completely. 老版本，不需要升级UR臂固件，但是要checkout到kinetic版本，不然会编译错误。）
2. universal_robot 也要checkout到kinetic版本。(这个版本中包含了第8步提到的ur_msgs，所以可以删除独立的ur_msgs包。 独立的ur_msgs包配合kinetic版本的ur_modern_driver，要checkout到1.3.0版本，不然会编译错误)
3. 通过moveit生成轨迹，然后通过action server控制机器人。 To control the robot using ROS, use the action server on /scaled_pos_joint_traj_controller/follow_joint_trajectory，https://github.com/UniversalRobots/Universal_Robots_ROS_Driver
4. http://wiki.ros.org/universal_robot/Tutorials/Getting%20Started%20with%20a%20Universal%20Robot%20and%20ROS-Industrial
- roslaunch ur_modern_driver ur5_bringup.launch robot_ip:=IP_OF_THE_ROBOT
- roslaunch ur5_moveit_config demo.launch
- roslaunch ur5_moveit_config moveit_rviz.launch config:=true(这个依赖于上面的demo.launch)

# ur ros wiki
- http://wiki.ros.org/universal_robot/Tutorials/Getting%20Started%20with%20a%20Universal%20Robot%20and%20ROS-Industrial

