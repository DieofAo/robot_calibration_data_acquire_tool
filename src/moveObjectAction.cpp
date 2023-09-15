#include "moveObjectAction.h"
#include "ur_kinematics/ur_kin.h"  //ikfast provided by universal_robot ros package
// https://hub.docker.com/r/personalrobotics/ros-openrave
// https://ros-planning.github.io/moveit_tutorials/doc/ikfast/ikfast_tutorial.html?highlight=ikfast
// http://openrave.org/docs/latest_stable/openravepy/ikfast/#ik-types
// openrave does not work for the current ur5 urdf. The generated IKFast sovler generate wrong IK solution given end-effector pose from forward kinematic.

moveObjectAction::moveObjectAction(ros::NodeHandle* _nh){
    nh=_nh;

    // motion plan param in accordance with the planning group name of "roslaunch ur5_moveit_config demo.launch"
    planGroupName= "manipulator";          // tool0(last frame) is same as wrist_3_link. base(first frame) is same as base_link_inertia.

    planGroup = new moveit::planning_interface::MoveGroupInterface(planGroupName);   // out loading robot model 'ur5_robot'. plan group is a collection of joints, which are stored as a JointModelGroup
    planGroup->setPlanningTime(1);

    // ik param
    urdf_param_name = "/robot_description";
    ik_chain_start = "base_link";
    ik_chain_end = "flange";
    endLinkFrameOfIKfastSolver2Flange.setIdentity();
    endLinkFrameOfIKfastSolver2Flange.setRotation(tf2::Quaternion(1,0,0,0));


}


moveObjectAction::~moveObjectAction(){
    delete robotModelLoader;
    delete kinematicModel;
    delete kinematicState;
    delete jointModelGroup;
    delete planGroup;

    delete nominal;
}




void moveObjectAction::getCurrentJointConfiguration(std::vector<double>& _jointsPosition){
    _jointsPosition = planGroup->getCurrentJointValues();
    if(debugInfo){
        std::cout<< std::endl;
        std::cout<<"current joint positions: ";
        for(int i=0;i<_jointsPosition.size();i++)
            std::cout<< _jointsPosition.at(i)<<", ";
        std::cout<<std::endl;
    }
}

void moveObjectAction::getCurrentRobotEndLinkFrame2RobotBaseLinkFrame(tf2::Transform& _robotEndLinkFrame2RobotBaseLinkFrame){
    geometry_msgs::PoseStamped pose0 = planGroup->getCurrentPose(ik_chain_start);  //related to the base_link (frame_id in the PoseStamped)
    tf2::Transform robotBaseLinkFrame2WorldReferreceFrame;
    geometry_msgs::Quaternion quat0 =  pose0.pose.orientation;
    geometry_msgs::Point origin0 = pose0.pose.position;
    robotBaseLinkFrame2WorldReferreceFrame.setRotation(tf2::Quaternion(quat0.x, quat0.y, quat0.z, quat0.w));
    robotBaseLinkFrame2WorldReferreceFrame.setOrigin(tf2::Vector3(origin0.x, origin0.y, origin0.z));



    geometry_msgs::PoseStamped pose1 = planGroup->getCurrentPose(ik_chain_end);  //related to the base_link (frame_id in the PoseStamped)
    tf2::Transform robotEndLinkFrame2WorldReferreceFrame;
    geometry_msgs::Quaternion quat1 =  pose1.pose.orientation;
    geometry_msgs::Point origin1 = pose1.pose.position;
    robotEndLinkFrame2WorldReferreceFrame.setRotation(tf2::Quaternion(quat1.x, quat1.y, quat1.z, quat1.w));
    robotEndLinkFrame2WorldReferreceFrame.setOrigin(tf2::Vector3(origin1.x, origin1.y, origin1.z));

    //tranformation between any two frame can be compute by this way
    _robotEndLinkFrame2RobotBaseLinkFrame = robotBaseLinkFrame2WorldReferreceFrame.inverse() *  robotEndLinkFrame2WorldReferreceFrame ;

}


