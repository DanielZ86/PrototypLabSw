#include "threadstayhelpontop.h"
#include <QFileDialog>


ThreadStayHelpOnTop::ThreadStayHelpOnTop(QMainWindow *main)
{
    mainWindow = main;
}

void ThreadStayHelpOnTop::run(){
    while (! isThreadstopped)
        {
/*

        qDebug() << "Bevor";
        QList<HauptFenster *> listOfChildrenMain =  guiMain->findChildren<HauptFenster *>("");
        qDebug() << "Liste";
        foreach (HauptFenster* firstObject, listOfChildrenMain) {
           qDebug() << "Objekte";
            if(firstObject->inherits("QFileDialog")){
                //QFileDialog *inhertObject = qobject_cast<QFileDialog *>(firstObject);
                qDebug() << "Innen";
            }
        }
*/
        if(!mainWindow->isActiveWindow()){
            mainWindow->activateWindow();
            msleep(500);
        }

    }

}
void ThreadStayHelpOnTop::stop(){
    isThreadstopped = true;
}
