#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "songinfo.h"
#include <QTreeWidget>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    songInfo.loadPlaylistFile("../../../../datasets/day01.txt");
    songInfo.loadPlaylistFile("../../../../datasets/day02.txt");
    songInfo.loadPlaylistFile("../../../../datasets/day03.txt");
    songInfo.loadPlaylistFile("../../../../datasets/day04.txt");

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
    ui->mostPop->clear();

    QStringList mostPopularPlaylist = (QStringList()<<"This"<<"Is"<<"A"<<"Playlist"<<":)");
    ui->mostPop->insertItems(0, mostPopularPlaylist);

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

    QString current = ui->lineEdit->displayText();
    QStringList topFourSongs = songInfo.findFourSongs(current);
    ui->listWidget->clear();
    if(current == ""){
        QStringList blank = (QStringList()<<"");
        ui->listWidget->insertItems(0,blank);
    }
    else{
    ui->listWidget->insertItems(0, topFourSongs);
    }

}

void MainWindow::on_BrowseButton_clicked()
{
    PlaylistFileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "../../../../datasets/",
                "All Files (*.*)"
                );

    ui->PlaylistFileEdit->insert(PlaylistFileName);
}

void MainWindow::on_PlaylistFileEdit_textChanged(const QString &arg1)
{
    PlaylistFileName = ui->PlaylistFileEdit->displayText();
}

void MainWindow::on_UploadButton_clicked()
{
    int x = songInfo.loadPlaylistFile(PlaylistFileName);
    if (x == 0) {
        QMessageBox::information(this,tr("Successful Upload"),"The file " + PlaylistFileName +" was successfully uploaded!");
    }
    else {
        QMessageBox::critical(this,tr("Unsuccessful Upload"),"The file " + PlaylistFileName +" does not exist");
    }
    ui->PlaylistFileEdit->clear();
}

void MainWindow::on_pushButton_clicked()
{
    QString scoretext = ui->PopularityScore->text();
    QString playlist = ui->PlaylistNumbers->toPlainText();
    int score = scoretext.toInt();
    playlist = playlist.simplified();
    playlist.replace( " ", "" );
    QRegExp re("^[0-9,.]*$");
    if (re.exactMatch(playlist) && score > 0 && score < 1000000) {
        QStringList Playlist_List = playlist.split(",");
        songInfo.addPlaylist(Playlist_List, score);
        QMessageBox::information(this,tr("Successful Upload"),"Your playlist was successfully uploaded!");
    }
    else {
        QMessageBox::critical(this,tr("Unsuccessful Upload"),"There exists a problem with one or both of your inputs.");
    }
    ui->PopularityScore->setValue(1);
    ui->PlaylistNumbers->clear();

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->trending->clear();

    QStringList TopPlaylists = (QStringList()<<"This"<<"Is"<<"Are"<<"Playlists"<<":)");
    ui->trending->insertItems(0,TopPlaylists);
}
