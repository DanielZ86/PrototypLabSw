#include "threadstayhelpontop.h"


ThreadStayHelpOnTop::ThreadStayHelpOnTop(QMainWindow *main)
{
    mainWindow = main;
}

void ThreadStayHelpOnTop::run(){
    while (1) {
        {
        mainWindow->activateWindow();
     // mainWindow->raise();
     // qDebug()<<"From worker thread: " << mainWindow->set;
        msleep(100);
        }
    }
}
