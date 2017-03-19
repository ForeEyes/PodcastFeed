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
    //Bool to tell if user clicked ok on dialog.
    bool ok;
    //call the Podcast dialog function and pass the label, and window title
    QString itunesLink = addPodcast_dlg("Itunes Link:", "Add Podcast using Itunes Link", ok);
    //Variable for storing rss link.
    QString rssLink;
    //Check if user clicked ok and it the string is empty
    if(ok && !itunesLink.isEmpty()){
        //Pass Itunes Link & Reference of FeedURL to getRSSurl
        //function return true if it was able to get the rss link
        if(getRSSurl(itunesLink, rssLink)){
            //Call addPodcast function and pass rss link

        }

    }


}

void MainWindow::on_actionUsing_RSS_Link_triggered()
{
    //Bool to tell if user clicked ok on dialog.
    bool ok;
    //call the Podcast dialog function and pass the label, and window title
    QString rssLink = addPodcast_dlg("RSS Link:", "Add Podcast using RSS Link", ok);
    //Check if user clicked ok and it the string is empty
    if(ok && !rssLink.isEmpty()){
        //Call addPodcast function and pass rss link
    }

}

void MainWindow::on_actionRefresh_Feed_triggered()
{

}

void MainWindow::on_actionRemove_Podcast_triggered()
{

}

//Custom Dialog for Adding Podcast
QString MainWindow::addPodcast_dlg(QString Label, QString Title, bool &ok){
    //Create New Dialog
    QInputDialog *dlg = new QInputDialog();
    //Set the input as text input
    dlg->setInputMode(QInputDialog::TextInput);
    //Label for text input
    dlg->setLabelText(Label);
    //Label for Dialog
    dlg->setWindowTitle(Title);
    //Set Dialog Size
    dlg->resize(600,500);
    //Exec Dialog and return true is user clicks ok, else return false
    //Store this value in bool reference ok.
    ok = dlg->exec();
    //Return the Text From the Text Input
    return dlg->textValue();
}


//Take Itunes Link, make http request, get json reply
//Parse json reply and find the rss link for podcast
bool MainWindow::getRSSurl(QString itunesLink,QString &rssLink){
    return true;
}
