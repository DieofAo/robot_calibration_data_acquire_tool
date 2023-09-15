#include "rosNodeWithQt.h"
#include "taskControl.h"


rosNodeWithQt::rosNodeWithQt(int _argc, char **_argv){
    argc = _argc;
    argv = _argv;


    start();  //call the run() in a seperate thread.
}


rosNodeWithQt::~rosNodeWithQt(){
    delete robotTask;
}

void rosNodeWithQt::run(){
    ros::init(argc,argv,"ur_manipulation_node");
    ros::NodeHandle nh("~");
    ros::Rate loopRate(10);
    cameraImage=new camera();

    robotTask = new taskControl(&nh);

   ros::AsyncSpinner spinner(4);

   spinner.start();


    while (ros::ok()){
        cameraImage->getImage();


        robotTask->run(); //this call will bocked until return.
        loopRate.sleep();

    }
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    emit rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}
