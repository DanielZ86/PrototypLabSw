#ifndef THREADSTAYHELPONTOP_H
#define THREADSTAYHELPONTOP_H
#include <QThread>
#include <QtGui>
#include <QMainWindow>

class ThreadStayHelpOnTop : public QThread
{
     Q_OBJECT

public:

    ThreadStayHelpOnTop(QMainWindow *main);
    void stop();

private:
    void run();
    QMainWindow *mainWindow;

   bool isThreadstopped = false;

};

#endif // THREADSTAYHELPONTOP_H
