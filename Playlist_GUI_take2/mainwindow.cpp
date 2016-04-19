#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "songinfo.h"
#include <QTreeWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //SongInfo songInfo;
    //songInfo.loadPlaylistFile("/Users/codiesmith/Downloads/day01.txt");
    //songInfo.loadPlaylistFile("/Users/codiesmith/Downloads/day02.txt");
    //songInfo.loadPlaylistFile("/Users/codiesmith/Downloads/day03.txt");
    //songInfo.loadPlaylistFile("/Users/codiesmith/Downloads/day04.txt");

    QStringList DisBeTrending = (QStringList()<<"#dis"<<"#be"<<"#trending");
    ui->trending->insertItems(0, DisBeTrending);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{

    //ui->listWidget->clear();
    //ui->listWidget->insertItems(0, placeHolderList);

}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //When suggested song is double clicked, this is slot
    //Loads the most popular playlist containing selected song into middle pane

    QString resutLabelText = "Most popular playlist containing " + item->text();
    ui->resultLabel->setText(resutLabelText);

    QStringList mostPopularPlaylist = (QStringList()<<"Suck"<<"My"<<"Dick"<<"Bitch");
    ui->mostPop->insertItems(0, mostPopularPlaylist);

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    SongInfo songInfo;
    songInfo.loadPlaylistFile("/Users/codiesmith/Downloads/day01.txt");
    songInfo.loadPlaylistFile("/Users/codiesmith/Downloads/day02.txt");
    songInfo.loadPlaylistFile("/Users/codiesmith/Downloads/day03.txt");
    songInfo.loadPlaylistFile("/Users/codiesmith/Downloads/day04.txt");

    QString current = ui->lineEdit->displayText();

    QStringList topFourSongs = songInfo.findFourSongs(current);
    ui->listWidget->clear();
    ui->listWidget->insertItems(0, topFourSongs);

}
