#include "threadstayhelpontop.h"

ThreadStayHelpOnTop::ThreadStayHelpOnTop(QMainWindow *main)
{
    mainWindow = main;
}

void ThreadStayHelpOnTop::run(){
    while (! isThreadstopped)
        {
        if(!mainWindow->isActiveWindow()){
            mainWindow->activateWindow();
            msleep(500);
        }
    }
}

void ThreadStayHelpOnTop::stop(){
    isThreadstopped = true;
}
