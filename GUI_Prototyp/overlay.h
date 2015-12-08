#ifndef OVERLAY_H
#define OVERLAY_H

#include <QMainWindow>
#include <QToolBar>
#include <QString>
#include "ui_overlay.h"

namespace Ui {
class Overlay;
}

class Overlay : public QMainWindow
{
    Q_OBJECT

public:
    explicit Overlay(QWidget *parent = 0);
    ~Overlay();

private:
    Ui::Overlay *ui;
};

#endif // OVERLAY_H
