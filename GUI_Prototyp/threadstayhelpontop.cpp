#include "threadstayhelpontop.h"


ThreadStayHelpOnTop::ThreadStayHelpOnTop(QMainWindow *main)
{
    mainWindow = main;
}

void ThreadStayHelpOnTop::run(){
    while (! isThreadstopped)
        {
            mainWindow->activateWindow();
            qDebug() << "Hallo";
            msleep(100);
        }

}
void ThreadStayHelpOnTop::stop(){
    isThreadstopped = true;
}
