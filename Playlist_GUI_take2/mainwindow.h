#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "songinfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SongInfo songInfo;
    QString PlaylistFileName;

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_BrowseButton_clicked();

    void on_PlaylistFileEdit_textChanged(const QString &arg1);

    void on_UploadButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
