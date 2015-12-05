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

public slots:


private:
    void run();
    QMainWindow *mainWindow;

};

#endif // THREADSTAYHELPONTOP_H
