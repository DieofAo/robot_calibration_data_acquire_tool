#include <iostream>
#include <string>
#include <sstream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#define Image_Width 1280
#define Image_height 960

class camera{
public:
    camera();
    ~camera();
    bool getImage();
    void saveImage();

    uchar HNY_CV_002 = 0;



    cv::VideoCapture cap;
    cv::Mat frame_L,frame;
    char file_name[100];
    uchar num = 1;
    int key = 0;

};
