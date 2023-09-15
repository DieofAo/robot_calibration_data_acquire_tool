# Ros node for target object manipulation using an robotic arm-hand

## 1. depens
- ros noetic
- moveit 
- qt
- eigen
- trac_IK
- nlopt

## 2. Features
1. It has a graphic user interface based on Qt to work with ros node which is run in a sub QThread.
2. It uses trac_IK package to compute ik solution where task redundancy is considered via resolution criterion.
3. It has a 2-level task planning framework. The 1st level defines a state machine to excute the action segments of a specific task. The 2nd level compute the IK solution, check collision, plan motion, and drive the real robot.
4. It subcribes object pose information in the surroundings from a sensing node.



## 3. Todo
1. How to deal with reducing code redundancy for multiple task planning?


## 4. Bug report

To be continued...ss

## 5.run the program in terminal
- 先连接机器人或者仿真机器人
- 连接真实机器人用： roslaunch ur_robot_driver ur5_bringup.launch robot_ip:=机器人ip；  连仿真机器人用： roslaunch ur_gazebo ur5_bringup.launch 
- roslaunch ur5_moveit_config moveit_planning_execution.launch (用gaze_bo仿真时带上参数 sim:=true)
- roslaunch ur5_moveit_config moveit_rviz.launch
- roslaunch ur_manipulation ur_manipulation.launch
