#include"retriveCal.h"
camera::camera(){
    cap.open(0,cv::CAP_ANY);
    cap.set(cv::CAP_PROP_FRAME_WIDTH,  Image_Width*2);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, Image_height);
    cap.set(cv::CAP_PROP_FPS, 30);
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
}
camera::~camera(){
    cap.release();

}

bool camera::getImage(){


    if (!cap.isOpened())
        return -1;


    int i=0;


        key = cv::waitKey(1);
        cap >> frame;

        if (HNY_CV_002 == 0)
        {
            frame_L = frame(cv::Rect(0, 0, Image_Width, Image_height));
        }
        else
        {
            frame_L = frame(cv::Rect(Image_Width, 0, Image_Width, Image_height));
        }



//        if (key == 's')    //s save
//        {
//            sprintf(file_name, "/home/jqzlca/workspace/demo1/image//left/Left%u.jpg", num);
//            imwrite(file_name, frame_L);

//            num++;
//            key = 0;
//        }



       cv::namedWindow("Video_L", 1);
       imshow("Video_L", frame_L);


    return 0;
}

void camera::saveImage(){
    sprintf(file_name, "/home/jqzlca/workspace/catkin_ws/doc/collaborativeImage/Left%u.jpg", num);
    imwrite(file_name, frame_L);

    num++;

}
