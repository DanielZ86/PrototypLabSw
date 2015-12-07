#include "hauptfenster.h"
#include "ui_hauptfenster.h"
#include <overlay.h>
#include <QRect>
#include <QPushButton>
#include <QList>
#include <QObject>
#include <QToolButton>

HauptFenster::HauptFenster(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HauptFenster)
{

    ui->setupUi(this);

    QObject::connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(slotActionOpenFile()), Qt::QueuedConnection);
    QObject::connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(slotActionOpen_File_Triggered()), Qt::QueuedConnection );


   //  QObject::connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(slotActionOpenFile()),  Qt::QueuedConnection );
  //   QObject::connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(slotActionOpen_File_Triggered()),  Qt::QueuedConnection );


}

HauptFenster::~HauptFenster()
{
    delete ui;
}

void HauptFenster::slotActionExit(){
    this->close();
    if(isHelpOn)
    helpWindow->close();
}

void HauptFenster::closeEvent(QCloseEvent *event){
    // // qDebug() << event;
    if(isHelpOn){
        helpWindow->close();
    }
    this->close();
}

void HauptFenster::slotActionAbout(){
    // // qDebug() << "slotActionAbout";
}

void HauptFenster::slotActionClosePerspective(){
    // // qDebug() << "slotActionClosePerspective";
}

void HauptFenster::slotActionCloseProject(){
    // // qDebug() << "slotActionCloseProject";
    ui->listWidget->clear();
    ui->graphicsView->setScene(NULL);
}

void HauptFenster::slotActionContextHelp(){
    // // qDebug() << "slotActionContextHelp";
}

void HauptFenster::slotActionDynamicHelp(){
    // // qDebug() << "slotActionDynamicHelp";
    if(isHelpOn){
        helpWindow->close();
        t->stop();
        isHelpOn = false;
    }else{
        helpWindow = new Overlay();
        helpWindow->showFullScreen();
        isHelpOn=true;
        t = new ThreadStayHelpOnTop(helpWindow);
        t->start();
    }
}


void HauptFenster::slotActionOpenHelpPerspective(){
    // // qDebug() << "slotActionOpenHelpPerspective";
}

void HauptFenster::slotActionOpenPerspective(){
    // // qDebug() << "slotActionOpenPerspective";
}

void HauptFenster::slotActionPreferences(){
    // // qDebug() << "slotActionPreferences";
}

void HauptFenster::slotActionRedo(){
    // // qDebug() << "slotActionRedo";
}

void HauptFenster::slotActionResetPerspective(){
    // // qDebug() << "slotActionResetPerspective";
}

void HauptFenster::slotActionSave(){
    // // qDebug() << "slotActionSave";
    int i = ui->listWidget->currentRow();
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Save File"),"C://","PNG (*.png)");
    QFile file(imagePath);
    QFile::copy(ui->listWidget->item(i)->text(), imagePath);
}

void HauptFenster::slotActionSaveProject(){
    // // qDebug() << "slotActionSaveProject";
    writeXML();
}

void HauptFenster::slotActionShowView(){
    // // qDebug() << "slotActionShowView";
}

void HauptFenster::slotActionUndo(){
    // // qDebug() << "slotActionUndo";
}

void HauptFenster::slotActionWelcome(){
    // // qDebug() << "slotActionWelcome";
}
void HauptFenster::slotContextMenu(const QPoint& point){
    QMenu myMenu;
    myMenu.addAction  ( "Add Item" , this , SLOT (addFile()) );
    myMenu.addAction  ( "Remove Item" , this , SLOT (removeFile()) );
    myMenu.addAction ( "Save Item", this, SLOT (saveFile()));
    myMenu.exec(mapToGlobal(point));
}

// Speichert das ausgewählte Bild aus der Liste auf dem Rechner ab
void HauptFenster::saveFile(){
    int i = ui->listWidget->currentRow();
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Save File"),"C://","PNG (*.png)");
    QFile file(imagePath);   
    QFile::copy(ui->listWidget->item(i)->text(), imagePath);  
}

// Löscht ein ausgewähltes Bild in der Liste aus der Liste
void HauptFenster::removeFile(){
    int i = ui->listWidget->currentRow();
    delete ui->listWidget->item(i);
    ui->graphicsView->setScene(NULL);
}

// Fügt ein neues Bild in die Liste ein.
void HauptFenster::addFile(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),"C://","Picture (*.png)");
    ui->listWidget->addItem(filename);
}

// Fügt ein neues Bild in die Liste ein.
void HauptFenster::addFile( QString imagePath ){
    ui->listWidget->addItem(imagePath);
}

void HauptFenster::pictureLoad(QListWidgetItem *item){
    imageObject = new QImage();
    imageObject->load(item->text());
    image = QPixmap::fromImage(*imageObject);
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->graphicsView->setScene(scene);
}

void HauptFenster::readXML(){
    QDomDocument document;
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"),"C://","XML (*.xml)");
    QFile file(imagePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        // // qDebug() << "Failed to open file";
    }
    else{
        if(!document.setContent(&file)){
          // // qDebug() << "Failed to load file";
        }
        file.close();
    }
    QDomElement root = document.firstChildElement();
    listElements(root, "Pictures", "Name");
    // // qDebug() << "Finished";
}

void HauptFenster::listElements(QDomElement root, QString tagname, QString attribute){
    QDomNodeList items = root.elementsByTagName(tagname);
    // // qDebug() << "Total items = " << items.count();
    for(int i = 0; i < items.count(); i++){
        QDomNode itemnode = items.at(i);
        if(itemnode.isElement()){
            QDomElement itelement = itemnode.toElement();
            addFile(itelement.attribute(attribute));
        }
    }
}

void HauptFenster::writeXML(){
   QDomDocument document;
   QDomElement root = document.createElement("Pictures");
   document.appendChild(root);
   ui->listWidget->repaint();
   int temp = ui->listWidget->count();
   for(int i = 0; i < temp; i++){
       QDomElement pictures = document.createElement("Pictures");
       pictures.setAttribute("Name",  ui->listWidget->item(i)->text());
       pictures.setAttribute("ID", QString::number(i));
       root.appendChild(pictures);
   }
   QString imagePath = QFileDialog::getSaveFileName(this, tr("Choose File"),"C://","XML (*.xml)");
   QFile file(imagePath);
   if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
      // // qDebug() << "Failed to open file for writting";
   }
   else{
       QTextStream stream(&file);
       stream << document.toString();
       file.close();
        // // qDebug() << "Finished";
   }
}

void HauptFenster::readXML(QString imagePath){
    QDomDocument document;
    QFile file(imagePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        // // qDebug() << "Failed to open file";
    }
    else{
        if(!document.setContent(&file)){
          // // qDebug() << "Failed to load file";
        }
        file.close();
    }
    QDomElement root = document.firstChildElement();
    listElements(root, "Pictures", "Name");
    // // qDebug() << "Finished";
}

void HauptFenster::setHelpOnQToolBarAndOnPos(QString nameOfPos, QToolBar *qToolBar,  Overlay *helpWindow){
    QRect temp = HauptFenster::geometry();
    QRect temp2 = qToolBar->geometry();
    QList<QObject*> listChildrenToolbar = qToolBar->children();
    foreach (QObject* firstObject, listChildrenToolbar) {
        if(firstObject->inherits("QToolButton")){
            QToolButton *inhertObject = qobject_cast<QToolButton *>(firstObject);
            QRect geo = inhertObject->geometry();
            int x = geo.x() + temp.x()  + geo.width() + temp2.x() - 10;
            int y = geo.y() +temp.y() + geo.height() + temp2.y()- temp2.height();
            if(inhertObject->text()== nameOfPos){
              QPushButton *helpButton = new QPushButton(helpWindow);
              helpButton->setText("<--- Click here.");
              helpButton->setGeometry(x,y,100,30);
              helpButton->setStyleSheet("{ color: white; background-color: black; }");
              helpButton->setWindowOpacity(1.0);
              helpButton->setAttribute(Qt::WA_TranslucentBackground, false);
              helpButton->setFlat(true);
              helpButton->show();
              helpButtons.push_front(helpButton);
            }
        }
    }
}

/*
void hauptFenster::setHelpOnQMenue(QString nameOfPos, QMenuBar *qMenuBar){
    QRect temp = hauptFenster::geometry();
    QList<QObject*> listOfChildrenMenueBar =  qMenuBar->children();
    int sizeX=0;
    foreach (QObject* firstObject, listOfChildrenMenueBar) {
        if(firstObject->inherits("QMenu")){
        QMenu *inhertObject = qobject_cast<QMenu *>(firstObject);
        QString name = inhertObject->title() + " ";
        QFont *test = new QFont(name);
        QFontMetrics fm(*test);
        int pixelsWide = fm.width(name);
        sizeX =  sizeX + (pixelsWide);
        if(inhertObject->title() == nameOfPos){
           int x = temp.x()  + sizeX;
            QPushButton *helpButton = new QPushButton();
            helpButton->setText(inhertObject->title());
            helpButton->setGeometry(x  ,temp.y()  ,120,30);
            helpButton->show();
            helpButtons.push_front(helpButton);
            }
         }
    }
}
*/

void HauptFenster::slotActionWorkflowFileOpenFile(){
    if(isHelpOn){
        helpWindow->close();
        isHelpOn = false;
    }
    slotActionDynamicHelp();
    QToolBar *toolBar = ui->toolBarFileAndEdit;
    setHelpOnQToolBarAndOnPos("Open File", toolBar,  helpWindow);
}

void HauptFenster::slotActionWorkflowFileSave(){

}

void HauptFenster::slotActionWorkflowFileSaveProject(){
    if(isHelpOn){
        helpWindow->close();
        isHelpOn = false;
    }
    slotActionDynamicHelp();
    QToolBar *toolBar = ui->toolBarFileAndEdit;
    setHelpOnQToolBarAndOnPos("Save Project", toolBar,  helpWindow);
}

void HauptFenster::slotActionWorkflowFileCloseProject(){
if(isHelpOn){
    helpWindow->close();
    isHelpOn = false;
}
    slotActionDynamicHelp();
        QToolBar *toolBar = ui->toolBarFileAndEdit;
        setHelpOnQToolBarAndOnPos("Close Project", toolBar,  helpWindow);



}

void HauptFenster::slotActionWorkflowFileExit(){

}

void HauptFenster::slotActionWorkflowContextAddItem(){

}

void HauptFenster::slotActionWorkflowContextRemoveItem(){

}

void HauptFenster::slotActionWorkflowContextSaveItem(){

}

void HauptFenster::slotActionWorkflowShowPicture(){

}

void HauptFenster::slotActionOpenFile(){
    // // qDebug() << "slotActionOpenFile";
    dialog = new QFileDialog(this, tr("Open File"),"C://","Picture (*.png);; Project (*.xml)");
   // QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"),"C://","Picture (*.png);; Project (*.xml)");
    dialog->show();
    connect(dialog, SIGNAL(finished(int)), this, SLOT(What()));
}

void HauptFenster::What(){
     helpWindow->close();
     isHelpOn = false;
     foreach (QPushButton* btn, helpButtons) {
         btn->close();
     }
         /*if(imagePath.endsWith(".png")){
             addFile(imagePath);
         }else if (imagePath.endsWith(".xml")){
             ui->listWidget->clear();
             readXML(imagePath);
         }*/
     QPushButton *helpButton = new QPushButton(this);
     helpButton->setText("Workflow finished.\nPlease click to close this workflow.");
     QRect temp = HauptFenster::geometry();
     helpButton->setGeometry(0,0, temp.width(),temp.height());
     helpButton->setWindowOpacity(1.0);
     helpButton->setStyleSheet("background-color: white");
     helpButton->setStyleSheet("color: black");
     helpButton->setFlat(true);
     helpButton->show();
     helpButtons.push_front(helpButton);
     connect(helpButton, SIGNAL(clicked(bool)), this, SLOT(What2()));
}

void HauptFenster::What2(){
    helpWindow->close();
    t->stop();
    isHelpOn = false;
    //helpButton->close();
    foreach (QPushButton* btn, helpButtons) {
        btn->close();
    }
    helpButtons.clear();
}

void HauptFenster::slotActionDynamicHelpOpenFile(){
    // // qDebug() << "slotActionDynamicHelp";
    if(isHelpOn){
        helpWindow->close();
        t->stop();
        isHelpOn = false;
    }else{
        helpWindow = new Overlay();
        helpWindow->showFullScreen();
        isHelpOn=true;
        t = new ThreadStayHelpOnTop(helpWindow);
        t->start();
    }
}

void HauptFenster::slotActionOpen_File_Triggered(){
    Sleep(100);
    if(isHelpOn){
        helpWindow->close();
        isHelpOn = false;
        slotActionDynamicHelpOpenFile();
        QList<QFileDialog *> listOfChildrenMain =  HauptFenster::findChildren<QFileDialog *>();
        foreach (QObject* firstObject, listOfChildrenMain) {
            if(firstObject->inherits("QFileDialog")){
                QFileDialog *inhertObject = qobject_cast<QFileDialog *>(firstObject);
                QRect posQFileDialog = inhertObject->geometry();
                QPushButton *helpButton = new QPushButton(helpWindow);
                helpButton->setText("<--- Choose your File.\nPicture: PNG\nProject: XML");
                helpButton->setGeometry(posQFileDialog.x(),posQFileDialog.y(), 150,130);
                helpButton->setStyleSheet("{ color: white; background-color: black; }");
                helpButton->setWindowOpacity(1.0);
                helpButton->setFlat(true);
                helpButton->show();
                helpButtons.push_front(helpButton);
                break;
            }
        }
    }
}
