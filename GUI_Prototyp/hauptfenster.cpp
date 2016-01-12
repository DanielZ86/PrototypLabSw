#include "hauptfenster.h"
#include "ui_hauptfenster.h"
/**
 *  Author Daniel Zygar
 *
 *  Die Klasse HauptFenster
 *  ist das Hauptfenster, es bildet ein Mini-MITK nach.
 */
HauptFenster::HauptFenster(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HauptFenster)
{
    ui->setupUi(this);
    QObject::connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(slotActionOpenFile()), Qt::QueuedConnection);
    QObject::connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(slotActionOpen_File_Triggered()), Qt::QueuedConnection );
}

HauptFenster::~HauptFenster()
{
    delete ui;
}

/**
 * @brief HauptFenster::slotActionExit
 * Beendet das Programm und schließt alle offenen Helpfenster.
 */
void HauptFenster::slotActionExit(){
    if(isHelpOn){
        helpWindow->close();
        foreach (QPushButton* btn, helpButtons) {
            btn->close();
        }
        helpButtons.clear();
        t->stop();
        isHelpOn = false;
    }
    this->close();
}

/**
 * @brief HauptFenster::closeEvent
 * @param event
 * überschreibt das CloseEvent und führt eine andere Close-Methode aus.
 */
void HauptFenster::closeEvent(QCloseEvent *event){
    qDebug() << event;
    slotActionExit();
}

/**
 * @brief HauptFenster::slotActionAbout
 * not implemented yet.
 */
void HauptFenster::slotActionAbout(){
}

/**
 * @brief HauptFenster::slotActionClosePerspective
 * not implemented yet.
 */
void HauptFenster::slotActionClosePerspective(){
}

/**
 * @brief HauptFenster::slotActionCloseProject
 * schließt ein Projekt.
 */
void HauptFenster::slotActionCloseProject(){
    ui->listWidget->clear();
    ui->graphicsView->setScene(NULL);
}

/**
 * @brief HauptFenster::slotActionContextHelp
 * not implemented yet.
 */
void HauptFenster::slotActionContextHelp(){
}

/**
 * @brief HauptFenster::slotActionDynamicHelp
 * erstellt einen Thread und öffnet die dynamische Hilfe.
 */
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

/**
 * @brief HauptFenster::slotActionOpenHelpPerspective
 * not implemented yet.
 */
void HauptFenster::slotActionOpenHelpPerspective(){
}

/**
 * @brief HauptFenster::slotActionOpenPerspective
 * not implemented yet.
*/
void HauptFenster::slotActionOpenPerspective(){
}

/**
 * @brief HauptFenster::slotActionPreferences
 * not implemented yet.
 */
void HauptFenster::slotActionPreferences(){
}

/**
 * @brief HauptFenster::slotActionRedo
 * not implemented yet.
 */
void HauptFenster::slotActionRedo(){
}

/**
 * @brief HauptFenster::slotActionResetPerspective
 * not implemented yet.
 */
void HauptFenster::slotActionResetPerspective(){
}

/**
 * @brief HauptFenster::slotActionSave
 * Speichert das ausgewählte Bild an einem gewünschten Ort auf dem Rechner ab.
 *
 */
void HauptFenster::slotActionSave(){
    int i = ui->listWidget->currentRow();
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Save File"),"C://","PNG (*.png)");
    QFile file(imagePath);
    QFile::copy(ui->listWidget->item(i)->text(), imagePath);
}

/**
 * @brief HauptFenster::slotActionSaveProject
 * Führt die Methode WriteXML aus, diese speichert das Projekt in einer XML Datei ab.
 */
void HauptFenster::slotActionSaveProject(){
    writeXML();
}

/**
 * @brief HauptFenster::slotActionShowView
 * not implemented yet.
 */
void HauptFenster::slotActionShowView(){
}

/**
 * @brief HauptFenster::slotActionUndo
 * not implemented yet.
 */
void HauptFenster::slotActionUndo(){
}

/**
 * @brief HauptFenster::slotActionWelcome
 * not implemented yet.
 */
void HauptFenster::slotActionWelcome(){
}

/**
 * @brief HauptFenster::slotContextMenu
 * @param point
 * führt die gewählte Context-Methode aus.
 */
void HauptFenster::slotContextMenu(const QPoint& point){
    QMenu myMenu;
    myMenu.addAction  ( "Add Item" , this , SLOT (addFile()) );
    myMenu.addAction  ( "Remove Item" , this , SLOT (removeFile()) );
    myMenu.addAction ( "Save Item", this, SLOT (saveFile()));
    myMenu.exec(mapToGlobal(point));
}

/**
 * @brief HauptFenster::saveFile
 * Speichert das ausgewählte Bild an einem gewünschten Ort auf dem Rechner ab.
 */
void HauptFenster::saveFile(){
    int i = ui->listWidget->currentRow();
    QString imagePath = QFileDialog::getSaveFileName(this, tr("Save File"),"C://","PNG (*.png)");
    QFile file(imagePath);   
    QFile::copy(ui->listWidget->item(i)->text(), imagePath);  
}

/**
 * @brief HauptFenster::removeFile
 * Löscht ein ausgewähltes Bild aus der Liste.
 */
void HauptFenster::removeFile(){
    int i = ui->listWidget->currentRow();
    delete ui->listWidget->item(i);
    ui->graphicsView->setScene(NULL);
}

/**
 * @brief HauptFenster::addFile
 * Fügt ein neues Bild in die Liste ein, welches über ein QFileDialog ausgewählt wurde.
 */
void HauptFenster::addFile(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),"C://","Picture (*.png)");
    ui->listWidget->addItem(filename);
}

/**
 * @brief HauptFenster::addFile
 * @param imagePath
 * Fügt ein neues Bild in die Liste ein.
 */
void HauptFenster::addFile( QString imagePath ){
    ui->listWidget->addItem(imagePath);
}

/**
 * @brief HauptFenster::readXML
 * liest ein Projekt über eine XML Datei ein.
 */
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

/**
 * @brief HauptFenster::listElements
 * @param root ein QDomElement
 * @param tagname der Tagname des Attributes
 * @param attribute der Attributname.
 * liest die Elemente aus der XML Datei.
 */
void HauptFenster::listElements(QDomElement root, QString tagname, QString attribute){
    QDomNodeList items = root.elementsByTagName(tagname);
    for(int i = 0; i < items.count(); i++){
        QDomNode itemnode = items.at(i);
        if(itemnode.isElement()){
            QDomElement itelement = itemnode.toElement();
            addFile(itelement.attribute(attribute));
        }
    }
}

/**
 * @brief HauptFenster::writeXML
 * Schreibt das Projekt in eine XML Datei.
 */
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

/**
 * @brief HauptFenster::readXML
 * @param imagePath
 * liest ein Projekt über eine XML Datei ein, welche über einen Pfad angegeben wurde.
 *
 */
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

/**
 * @brief HauptFenster::setHelpOnQToolBarAndOnPos
 * @param nameOfPos der lesbare Text des QToolBarItem, welches man verwenden möchte.
 * @param qToolBar die QToolBar die verwendet werden soll.
 * @param helpWindow das HelpWindow auf das die Hilfe gesetzt werden soll.
 * setzt die Hilfe neben ein QToolBarItem.
 */
void HauptFenster::setHelpOnQToolBarAndOnPos(QString nameOfPos, QToolBar *qToolBar,  Overlay *helpWindow){
    QRect temp = HauptFenster::geometry();
    QRect temp2 = qToolBar->geometry();
    QList<QObject*> listChildrenToolbar = qToolBar->children();
    foreach (QObject* firstObject, listChildrenToolbar) {
        if(firstObject->inherits("QToolButton")){
            QToolButton *inhertObject = qobject_cast<QToolButton *>(firstObject);
            QRect geo = inhertObject->geometry();
            int x = 0;
            int y = 0;
            if(geo.y() +temp.y() + geo.height() + temp2.y()- temp2.height() > 0 ){
                x = geo.x() + temp.x()  + geo.width() + temp2.x() - 10;
                y = geo.y() +temp.y() + geo.height() + temp2.y()- temp2.height();
            }else  {
                x = geo.x() + temp.x()  + geo.height() + temp2.x() + 45;
                y = geo.y() +temp.y() + geo.width() + temp2.y()- temp2.width() +20;
            }
            if(inhertObject->text()== nameOfPos){
              QPushButton *helpButton = new QPushButton(helpWindow);
              helpButton->setText("<--- Click here.");
              helpButton->setGeometry(x,y,100,30);
              helpButton->setWindowOpacity(1.0);
              helpButton->setAttribute(Qt::WA_TranslucentBackground, false);
              helpButton->setFlat(true);
              helpButton->show();
              helpButtons.push_front(helpButton);
            }
        }
    }
}

/**
 * @brief HauptFenster::slotActionWorkflowFileOpenFile
 * Startet den Help-Workflow für OpenFile.
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

/**
 * @brief HauptFenster::slotActionWorkflowFileSave
 *  not implemented yet.
 */
void HauptFenster::slotActionWorkflowFileSave(){

}

/**
 * @brief HauptFenster::slotActionWorkflowFileSaveProject
 * Startet den Help-Workflow für SaveProject
 */
void HauptFenster::slotActionWorkflowFileSaveProject(){
    if(isHelpOn){
        helpWindow->close();
        isHelpOn = false;
    }
    slotActionDynamicHelp();
    QToolBar *toolBar = ui->toolBarFileAndEdit;
    setHelpOnQToolBarAndOnPos("Save Project", toolBar,  helpWindow);
}

/**
 * @brief HauptFenster::slotActionWorkflowFileCloseProject
 * Startet den Help-Workflow für CloseProject
 */
void HauptFenster::slotActionWorkflowFileCloseProject(){
if(isHelpOn){
    helpWindow->close();
    isHelpOn = false;
}
    slotActionDynamicHelp();
        QToolBar *toolBar = ui->toolBarFileAndEdit;
        setHelpOnQToolBarAndOnPos("Close Project", toolBar,  helpWindow);
}

/**
 * @brief HauptFenster::slotActionWorkflowFileExit
 * not implemented yet.
 */
void HauptFenster::slotActionWorkflowFileExit(){
}

/**
 * @brief HauptFenster::slotActionWorkflowContextAddItem
 * not implemented yet.
 */
void HauptFenster::slotActionWorkflowContextAddItem(){
}

/**
 * @brief HauptFenster::slotActionWorkflowContextRemoveItem
 * not implemented yet.
 */
void HauptFenster::slotActionWorkflowContextRemoveItem(){
}

/**
 * @brief HauptFenster::slotActionWorkflowContextSaveItem
 * not implemented yet.
 */
void HauptFenster::slotActionWorkflowContextSaveItem(){
}

/**
 * @brief HauptFenster::slotActionWorkflowShowPicture
 * not implemented yet.
 */
void HauptFenster::slotActionWorkflowShowPicture(){
}

/**
 * @brief HauptFenster::slotActionOpenFile
 * Erster Schritt des Workflows OpenFile (sind zwei gleichzeitig).
 */
void HauptFenster::slotActionOpenFile(){
    dialog = new QFileDialog(this, tr("Open File"),"C://","Picture (*.png);; Project (*.xml)");
    dialog->show();
    connect(dialog, SIGNAL(finished(int)), this, SLOT(slotActionOpenFileTaskOne()));
}

/**
 * @brief HauptFenster::slotActionOpenFileTaskOne
 * Zweiter Schritt des Workflows OpenFile.
 */
void HauptFenster::slotActionOpenFileTaskOne(){
    if(isHelpOn){
         helpWindow->close();
         isHelpOn = false;
         foreach (QPushButton* btn, helpButtons) {
             btn->close();
         }
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
         connect(helpButton, SIGNAL(clicked(bool)), this, SLOT(slotActionOpenFileTaskTwo()));
     }
   QString imagePath = dialog->selectedFiles()[0];
     if(imagePath.endsWith(".png")){
         addFile(imagePath);
     }else if (imagePath.endsWith(".xml")){
         ui->listWidget->clear();
         readXML(imagePath);
     }
}

/**
 * @brief HauptFenster::slotActionOpenFileTaskTwo
 * Dritter Schritt des Workflows OpenFile.
 */
void HauptFenster::slotActionOpenFileTaskTwo(){
    helpWindow->close();
    t->stop();
    isHelpOn = false;
    foreach (QPushButton* btn, helpButtons) {
        btn->close();
    }
    helpButtons.clear();
}

/**
 * @brief HauptFenster::slotActionDynamicHelpOpenFile
 * Öffnet ein neues HelpWindow.
 */
void HauptFenster::slotActionDynamicHelpOpenFile(){
    if(isHelpOn){
        helpWindow->close();
        foreach (QPushButton* btn, helpButtons) {
            btn->close();
        }
        helpButtons.clear();
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

/**
 * @brief HauptFenster::slotActionOpen_File_Triggered
 * Erster Schritt des Workflows OpenFile (sind zwei gleichzeitig).
 */
void HauptFenster::slotActionOpen_File_Triggered(){
    Sleep(100);
    if(isHelpOn){
        helpWindow->close();
        isHelpOn = false;
        slotActionDynamicHelpOpenFile();
        QPushButton *helpButton = new QPushButton(helpWindow);
        helpButton->setText("<--- Choose your File.\nPicture: PNG\nProject: XML");
        helpButton->setGeometry(dialog->x() + (dialog->width()/2),dialog->y() + (dialog->height()/2), 150,130);
        helpButton->setWindowOpacity(1.0);
        helpButton->setFlat(true);
        helpButton->show();
        helpButtons.push_front(helpButton);
    }
}

/**
 * @brief HauptFenster::slotLoadPicture
 * @param item
 * Lädt ein Bild in ein QListWidget.
 */
void HauptFenster::slotLoadPicture(QListWidgetItem *item){
    imageObject = new QImage();
    imageObject->load(item->text());
    image = QPixmap::fromImage(*imageObject);
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->graphicsView->setScene(scene);
}

// Methode um die Position eines QMenueItems zuermittlen, noch nicht ganz fertig.
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
