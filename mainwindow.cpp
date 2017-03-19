#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Disable the resize grip on the lower right corner
    ui->statusBar->setSizeGripEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionUsing_Itunes_Link_triggered()
{

}

void MainWindow::on_actionUsing_RSS_Link_triggered()
{

}

void MainWindow::on_actionRefresh_Feed_triggered()
{

}

void MainWindow::on_actionRemove_Podcast_triggered()
{

}
