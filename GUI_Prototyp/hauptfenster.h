#ifndef HAUPTFENSTER_H
#define HAUPTFENSTER_H

#include <QMainWindow>
#include <overlay.h>
#include <QDebug>
#include <QThread>
#include <threadstayhelpontop.h>
#include <QPoint>
#include <QString>
#include <QFileDialog>
#include <QtXml>
#include <QListWidgetItem>
#include <QGraphicsScene>
#include <QFileSystemModel>
#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class HauptFenster;
}

class HauptFenster : public QMainWindow
{
    Q_OBJECT

public:
    explicit HauptFenster(QWidget *parent = 0);
    ~HauptFenster();

private:
    ThreadStayHelpOnTop *t;
    bool isHelpOn = false;
    void closeEvent(QCloseEvent *event);
    Ui::HauptFenster *ui;
    Overlay *helpWindow;
    QGraphicsView *graphicsView;
    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;
    QFileSystemModel *fileModel;


public slots:
    void slotActionExit();
    void slotActionAbout();
    void slotActionClosePerspective();
    void slotActionCloseProject();
    void slotActionContextHelp();
    void slotActionDynamicHelp();
    void slotActionOpenFile();
    void slotActionOpenHelpPerspective();
    void slotActionOpenPerspective();
    void slotActionPreferences();
    void slotActionRedo();
    void slotActionResetPerspective();
    void slotActionSave();
    void slotActionSaveProject();
    void slotActionShowView();
    void slotActionUndo();
    void slotActionWelcome();
    void slotContextMenu(const QPoint&);
    void addFile();
    void addFile(QString imagePath);
    void pictureLoad(QListWidgetItem* item);
    void readXML();
    void writeXML();
    void listElements(QDomElement root, QString tagname, QString attribute);
    void readXML(QString imagePath);
    void saveFile();
    void removeFile();



};

#endif // HAUPTFENSTER_H
