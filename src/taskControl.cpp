#include "taskControl.h"

taskControl::taskControl(ros::NodeHandle* _nh){
    nh = _nh;

    recognizedObjectNum=0;
    idOfTargetObjectToMove=-1;

    //collisionObjects->objectsInit();

    moveObjcet = new moveObjectAction(nh);

    //test motion plan
    homeJointPosition.resize(moveObjcet->jointNum);
    for(int i=0;i<moveObjcet->jointNum;i++)
        homeJointPosition.at(i)=0.8;

    //topic service registration
    //subscribe object pose topic
    TransFromGlobalCameraToRobotBaseLinkFrame=new tf2::Transform;//initialize
    TransFromGlobalCameraToRobotBaseLinkFrame=new tf2::Transform;//initialize
    TransFromobjectPosetoGlobalCameraDetectorNode=new tf2::Transform;
    TransFromobjectPosetoHandCameraDetectorNode=new tf2::Transform;
    TransFrom6dFromPreTask=new tf2::Transform;
    flagHandCameraRefresh=0;
    flagGraspPoseRefresh=0;
}

taskControl::~taskControl(){
    delete moveObjcet;
}


//state machine
void taskControl::run(){


}


