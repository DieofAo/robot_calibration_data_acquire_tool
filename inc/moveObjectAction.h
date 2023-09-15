#ifndef __MOVEOBJECTACTION__
#define __MOVEOBJECTACTION__

#include <ros/ros.h>
#include <trac_ik/trac_ik.hpp>
#include <kdl/chainiksolverpos_nr_jl.hpp>

#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/convert.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>  //this headerfile includes geometry_msgs with time stamps.

#include <moveit/planning_scene/planning_scene.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/kinematic_constraints/utils.h>


#define debugInfo 1

class moveObjectAction{

public:
    moveObjectAction(ros::NodeHandle* _nh);
    ~moveObjectAction();

    void getCurrentJointConfiguration(std::vector<double>& _currentJointsPosition);
    void getCurrentRobotEndLinkFrame2RobotBaseLinkFrame(tf2::Transform& _currentRobotEndLinkFrame2RobotBaseLinkFrame);

    int jointNum;

private:
    ros::NodeHandle* nh;

    //motion plan
    robot_model_loader::RobotModelLoader* robotModelLoader;
    robot_model::RobotModelPtr* kinematicModel;
    robot_state::RobotStatePtr* kinematicState;
    robot_state::JointModelGroup* jointModelGroup;
    moveit::planning_interface::MoveGroupInterface* planGroup;
    moveit::planning_interface::MoveGroupInterface::Plan* motionPlan;
    moveit::core::MoveItErrorCode* planStatus;
    std::string planGroupName;
    std::string jointModelGroupName;

    //ik
    std::string urdf_param_name;
    std::string ik_chain_start, ik_chain_end;
    TRAC_IK::TRAC_IK* trac_ik_solver;
    KDL::JntArray *nominal;
    std::vector<double> ikSolutionCriterionWeight;

    // the ikfast solver has a different frame definition from the ur5_moveit config
    tf2::Transform endLinkFrameOfIKfastSolver2Flange;

    //robot state
    std::vector<double> currentJointsPosition;
};

void tf2Transform2IKfastArray(tf2::Transform& _transform, double *_poseMatrix);
void printfTranfrom(std::string&& _name, tf2::Transform& _transform);
void printfGeometryMsgsPose(std::string&& _name, geometry_msgs::PoseStamped& _pose);
void printEigenIsometry3d(std::string&& _name, Eigen::Isometry3d& _state);

#endif
