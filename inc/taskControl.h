#ifndef __TASKCONTROL__
#define __TASKCONTROL__

#include <ros/ros.h>
#include "moveObjectAction.h"
#include "object_detector/objectPose.h"



class taskControl{

public:
    moveObjectAction *moveObjcet;

    taskControl(ros::NodeHandle* _nh);
    ~taskControl();
    void run();

    // update task and object info to gui
    void getRecognizedObjectInfo(int **objectIdDataAddress, int *num);

    void objectMsgCallback(const object_detector::objectPose& msg);
    void updateObjects();
    // command infor from gui
    int idOfTargetObjectToMove;




private:
    int argc;
    char** argv;

    tf2::Transform *TransFromGlobalCameraToRobotBaseLinkFrame;
     tf2::Transform *TransFromHandCameraToRobotEndLinkFrame;
    //object detect
    tf2::Transform *TransFromobjectPosetoGlobalCameraDetectorNode;
    tf2::Transform *TransFromobjectPosetoHandCameraDetectorNode;
    tf2::Transform TransFromHandCameraDetect;
    tf2::Transform TransFromGlobalCameraDetect;
    tf2::Transform TransCannonCameraDetect;
    int cameraId;
    int objectId;
    int flagHandCameraRefresh;
    int flagGraspPoseRefresh;
    tf2::Transform *TransFrom6dFromPreTask;


    //main task resources
    ros::NodeHandle* nh;

    //state machine variables


    //info of recognized objects in the view of camera
    int recognizedObjectId[100];
    int recognizedObjectNum;

    // home joint configuration for the robot.
    std::vector<double> homeJointPosition;

    //hardware configuration, constants read from yaml
    tf2::Transform handFrame2RobotEndLinkFrame;  //RobotEndLinkFrame: wrist_3_link
    tf2::Transform leftHandCameraFrame2RobotEndLinkFrame;
    tf2::Transform leftGlobalCameraFrame2RobotBaseLinkFrame; //RobotBaseLinkFrame: base_link_inertia

    //target configuration (point) of the arucoTag in left global camera for improved object pose measurement
    tf2::Vector3 positionInLeftGlobalCameraFrameForMeasurement;
    tf2::Vector3 axisInHandFrameToOrthogonalize;

    //grasp parameters, constant read from yaml
    tf2::Vector3 localAxisInHandFrameToAlignForGrasp; //power grasp cylinder along an axis of the object.
    tf2::Vector3 localPositionInHandFrameToAlignForGrasp;

    tf2::Transform localFrameInHandFrameToAlignForGrasp; // deterministic grasp frame aligned with the object frame.

    //pose measurements
    tf2::Transform recognizedObjectFrame2LeftHandCameraFrame;
    tf2::Transform recognizedObjectFrame2LeftGlobalCameraFrame;
};

#endif
