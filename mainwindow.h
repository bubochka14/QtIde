#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <syntaxhighlighter.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void setCurrentFile(const QModelIndex& index);
    void setupFileSystem();
private:
    Ui::MainWindow  *ui;
    QFileSystemModel fileModel;
    QTreeView       *fileView;
    QString          currentFile;

};
#endif // MAINWINDOW_H
