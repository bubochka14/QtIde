#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    setupFileSystem();



}
void MainWindow::setCurrentFile(const QModelIndex &index){

    QString file = fileModel.filePath(index);
    QFileInfo info(file);
    if(info.isDir())
        return;
    currentFile = file;
    ui->codeEditor->readTextFromFile(currentFile);

}
void MainWindow::setupFileSystem(){
    fileView = new QTreeView;
    connect(fileView, &QTreeView::doubleClicked,
            this, &MainWindow::setCurrentFile);

    fileModel.setRootPath(QDir::currentPath());
    fileView->setModel(&fileModel);

    ui->fileDock->setWidget(fileView);

    for(int i=1; i<fileModel.columnCount();++i)
        fileView->hideColumn(i);

    fileView->setHeaderHidden(true);
}
MainWindow::~MainWindow()
{
    delete ui;
}

