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
#include <QToolBar>
#include <QList>
#include <QPushButton>

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
    void closeEvent(QCloseEvent *event);
    void setHelpOnQToolBarAndOnPos(QString nameOfPos, QToolBar *qToolBar,  Overlay *helpWindow);

    Ui::HauptFenster *ui;
    ThreadStayHelpOnTop *t;
    bool isHelpOn = false;

    QGraphicsView *graphicsView;
    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;
    QFileSystemModel *fileModel;

    Overlay *helpWindow;
    QList<QPushButton*> helpButtons;
    QFileDialog *dialog;


public slots:
    void readXML();
    void writeXML();
    void listElements(QDomElement root, QString tagname, QString attribute);
    void readXML(QString imagePath);
    void addFile();
    void addFile(QString imagePath);
    void saveFile();
    void removeFile();
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
    void slotActionWorkflowFileOpenFile();
    void slotActionWorkflowFileSave();
    void slotActionWorkflowFileSaveProject();
    void slotActionWorkflowFileCloseProject();
    void slotActionWorkflowFileExit();
    void slotActionWorkflowContextAddItem();
    void slotActionWorkflowContextRemoveItem();
    void slotActionWorkflowContextSaveItem();
    void slotActionWorkflowShowPicture();

    void slotActionOpen_File_Triggered();
    void slotActionDynamicHelpOpenFile();
    void What();
    void What2();

    void slotLoadPicture(QListWidgetItem*);


};

#endif // HAUPTFENSTER_H
