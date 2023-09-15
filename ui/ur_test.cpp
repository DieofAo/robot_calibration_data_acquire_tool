#include "ur_test.h"
#include "./ui_ur_test.h"

ur_test::ur_test(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ur_test)
{
    ui->setupUi(this);
    rosNode = new rosNodeWithQt(argc, argv);


    connect(ui->retriveURPose,&QPushButton::clicked,this,&ur_test::retriveURPose);

}

ur_test::~ur_test()
{
    delete ui;
}


void ur_test::retriveURPose(){
    rosNode->cameraImage->saveImage();
        tf2::Transform CurrentURPose;
        rosNode->robotTask->moveObjcet->getCurrentRobotEndLinkFrame2RobotBaseLinkFrame(CurrentURPose);
        std::vector<double> jointcurrent;
        rosNode->robotTask->moveObjcet->getCurrentJointConfiguration(jointcurrent);

        std::string outPutFilePath("/home/jqzlca/workspace/catkin_ws/doc/URCurrentPose.txt");
        std::ofstream outputFile;
        outputFile.open(outPutFilePath.c_str(),std::ios::app);  //append new data to the exist file or non-exist file

        if(outputFile.fail()){
        std::cout<<"write (append) result to file error!"<<std::endl;
//        return;
        }

        std::ostringstream ss;
        ss.precision(std::numeric_limits<double>::digits10);
        ss <<CurrentURPose.getOrigin().x()<<"\t";
        ss <<CurrentURPose.getOrigin().y()<<"\t";
        ss <<CurrentURPose.getOrigin().z()<<"\t";
        ss <<CurrentURPose.getRotation().x()<<"\t";
        ss <<CurrentURPose.getRotation().y()<<"\t";
        ss <<CurrentURPose.getRotation().z()<<"\t";
        ss <<CurrentURPose.getRotation().w()<<"\t";
        ss<<jointcurrent.at(0)*180/3.14<<"\t";
        ss<<jointcurrent.at(1)*180/3.14<<"\t";
        ss<<jointcurrent.at(2)*180/3.14<<"\t";
        ss<<jointcurrent.at(3)*180/3.14<<"\t";
        ss<<jointcurrent.at(4)*180/3.14<<"\t";
        ss<<jointcurrent.at(5)*180/3.14<<"\n";
        outputFile << ss.str();
        outputFile.close();



}
