#include "hauptfenster.h"
#include "ui_hauptfenster.h"
#include <overlay.h>


HauptFenster::HauptFenster(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HauptFenster)
{
    ui->setupUi(this);
    setOverlay();
}

HauptFenster::~HauptFenster()
{
    delete ui;
}

void HauptFenster::setOverlay(){
    helpWindow = new Overlay();
    helpWindow->showFullScreen();
    ThreadStayHelpOnTop *t = new ThreadStayHelpOnTop(helpWindow);
    t->start();
}
