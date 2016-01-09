#include "threadstayhelpontop.h"

/**
 *  Author Daniel Zygar
 *
 *  Die Klasse ThreadStayHelpOnTop
 *  hält ein übergebenes QMainWindow im Vordergrund.
 */
ThreadStayHelpOnTop::ThreadStayHelpOnTop(QMainWindow *main)
{
    mainWindow = main;
}
/**
 * @brief ThreadStayHelpOnTop::run
 * hält das QMainWindow-Objekt im Vordergrund.
 */

void ThreadStayHelpOnTop::run(){
    while (! isThreadstopped)
        {
        if(!mainWindow->isActiveWindow()){
            mainWindow->activateWindow();
            msleep(500);
        }
    }
}
/**
 * @brief ThreadStayHelpOnTop::stop
 * stoppt den Thread.
 */
void ThreadStayHelpOnTop::stop(){
    isThreadstopped = true;
}
