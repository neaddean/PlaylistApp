#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString placeHolder1 = "SONG1";
QString placeHolder2 = "SONG2";
QString placeHolder3 = "SONG3";
QString placeHolder4 = "SONG4";

QStringList placeHolderList = (QStringList()<< placeHolder1<<placeHolder2<<placeHolder3<<placeHolder4);

QStringList Top4List = (QStringList());


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    /*QTreeWidget *popup;

    //popup->setUpdatesEnabled(false);
    //popup->clear();

    for (int i = 0; i<3; i++){ //adds, one by one, each produced song to the treeview
        QTreeWidgetItem * item;
        item = new QTreeWidgetItem(popup);
        item->setText(0, placeHolderList.at(i));
    }

    popup->setCurrentItem(popup->topLevelItem(0));
    popup->resizeColumnToContents(0);
    popup->setUpdatesEnabled(true);
    popup->setFocus();
    popup->show();*/

    ui->listWidget->clear();
    ui->listWidget->insertItems(0, placeHolderList);


}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //When suggested song is double clicked, this is slot
    //Loads the most popular playlist containing selected song into middle pane

    QString resutLabelText = "Most popular playlist containing " + item->text();
    ui->resultLabel->setText(resutLabelText);


}
