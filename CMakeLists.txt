cmake_minimum_required(VERSION 2.8.3)

project(ur_test)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#ikfast cpp lib no main setting
ADD_DEFINITIONS(-DIKFAST_NO_MAIN)
#ADD_DEFINITIONS(-DIKFAST_HAS_LIBRARY)
ADD_DEFINITIONS(-DUR5_PARAMS)

set(Qt5_DIR "/home/jqzlca/software/Qt5.14.2/5.14.2/gcc_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Widgets REQUIRED)


find_package(catkin REQUIRED COMPONENTS
  interactive_markers    #referred to moveit_ws/moveit_tutorials/CMakeLists.txt
  moveit_core
  moveit_ros_planning
  moveit_ros_planning_interface
  moveit_ros_perception
  rviz_visual_tools
  moveit_visual_tools
  pluginlib
  geometric_shapes
  rosbag
  tf2_ros
  tf2_eigen
  tf2_geometry_msgs

  roscpp       # basic depens
  std_msgs

  trac_ik_lib  # referred to CMakeLists.txt in trac_ik_examples
)

set(OpenCV_DIR "/home/jqzlca/software/opencv_install/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)

find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED system filesystem date_time thread)

find_package(PkgConfig REQUIRED)  # referred to CMakeLists.txt in trac_ik_examples
pkg_check_modules(pkg_nlopt REQUIRED nlopt)

find_package(orocos_kdl REQUIRED)  # referred to CMakeLists.txt in trac_ik_examples

catkin_package(
  #LIBRARIES
  #INCLUDE_DIRS
  CATKIN_DEPENDS
    moveit_core    #referred to moveit_ws/moveit_tutorials/CMakeLists.txt
    moveit_visual_tools
    moveit_ros_planning_interface
    interactive_markers
    tf2_geometry_msgs
    trac_ik_lib   # referred to CMakeLists.txt in trac_ik_examples

  DEPENDS
    EIGEN3     #referred to moveit_ws/moveit_tutorials/CMakeLists.txt
    Boost
    orocos_kdl   # referred to CMakeLists.txt in trac_ik_examples
    pkg_nlopt
)

include_directories(
  ./inc
  ./ui
  ./ikfast_ur5
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
  ${orocos_kdl_INCLUDE_DIRS}   # referred to CMakeLists.txt in trac_ik_examples
  ${pkg_nlopt_INCLUDE_DIRS}    # referred to CMakeLists.txt in trac_ik_examples
)

add_executable(${PROJECT_NAME}_node
    ur_manipulation_node.cpp
    ./src/moveObjectAction.cpp
    ./src/rosNodeWithQt.cpp
    ./src/taskControl.cpp
    ./src/retriveCal.cpp
    ./ui/ur_test.cpp
    ./ui/ur_test.h  # header file having Q_OBJECT should be MOC here
    ./ui/ur_test.ui # ui file should be MOC here
    ./inc/rosNodeWithQt.h # header file having Q_OBJECT should be MOC here
    ./ikfast_ur5/ur_kin.cpp
)

target_link_libraries(${PROJECT_NAME}_node
    ${catkin_LIBRARIES}
    ${Boost_LIBRARIES}
    ${OpenCV_LIBS}
    ${orocos_kdl_LIBRARIES}   # referred to CMakeLists.txt in trac_ik_examples
    ${pkg_nlopt_LIBRARIES}     # referred to CMakeLists.txt in trac_ik_examples
    Qt5::Widgets
)
