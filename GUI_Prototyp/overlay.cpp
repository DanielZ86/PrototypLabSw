#include "overlay.h"
/**
 *  Author Daniel Zygar
 *
 *  Die Klasse Overlay
 *  erstellt ein transparentes Overlayout.
 */
Overlay::Overlay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Overlay)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->setWindowFlags(Qt::X11BypassWindowManagerHint|Qt::WindowStaysOnBottomHint|Qt::WindowStaysOnTopHint);
    this->setWindowFlags(Qt::WindowTransparentForInput);
}

Overlay::~Overlay()
{
    delete ui;
}
