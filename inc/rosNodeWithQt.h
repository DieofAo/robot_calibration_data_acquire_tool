#ifndef __ROSNODEWITHQT__
#define __ROSNODEWITHQT__

#include <QThread>
#include "taskControl.h"
#include "retriveCal.h"


class rosNodeWithQt: public QThread{
    Q_OBJECT

public:
    rosNodeWithQt(int argc, char **argv);
    camera *cameraImage;

    ~rosNodeWithQt();
    void run(); //virtual inherited function for Qthread
    void retriveURPose();
    taskControl *robotTask;




signals:
    void rosShutdown();

private:
    int argc;
    char** argv;
};

#endif
