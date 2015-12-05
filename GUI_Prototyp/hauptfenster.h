#ifndef HAUPTFENSTER_H
#define HAUPTFENSTER_H

#include <QMainWindow>
#include <overlay.h>
#include <QDebug>
#include <QThread>
#include <threadstayhelpontop.h>

namespace Ui {
class HauptFenster;
}

class HauptFenster : public QMainWindow
{
    Q_OBJECT

public:
    explicit HauptFenster(QWidget *parent = 0);
    ~HauptFenster();
    Overlay *helpWindow;
    QThread *t;
    void run();

void setOverlay();



private:
    Ui::HauptFenster *ui;
};

#endif // HAUPTFENSTER_H
