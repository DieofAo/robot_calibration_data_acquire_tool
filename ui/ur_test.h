#ifndef ROBOT_CONTROL_UI_H
#define ROBOT_CONTROL_UI_H

#include <QMainWindow>

#include "rosNodeWithQt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ur_test; }
QT_END_NAMESPACE

class ur_test : public QMainWindow
{
    Q_OBJECT

public:
    ur_test(int argc, char** argv, QWidget *parent = nullptr);
    ~ur_test();

public slots:

    void retriveURPose();

signals: 
    void taskParamUpdated(int commandIndex, int commandValue);

private:
    Ui::ur_test *ui;
    rosNodeWithQt *rosNode;
};
#endif // ROBOT_CONTROL_UI_H
