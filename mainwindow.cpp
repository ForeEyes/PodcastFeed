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
    //Check if user clicked ok and it the string is empty
    if(ok && !itunesLink.isEmpty()){
        //Pass Itunes Link to getRSSurl
        //function will then get the rss url and call addPodcast Function
        //If there is an error, it is displayed on the status bar
        getRSSurl(itunesLink);
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
void MainWindow::getRSSurl(QString itunesLink){
    //If the link is an itunes link and for a podcast then continue
    if(itunesLink.contains("itunes.apple.com") && itunesLink.contains("podcast") && itunesLink.contains("id")){
        //Get the index of the id string
        int idPosition = itunesLink.lastIndexOf("id");
        idPosition += 2;
        //Isolate everythign after id
        itunesLink = itunesLink.remove(0, idPosition);
        //Remove everything that is not the id on the right of the string
        while(itunesLink.toInt() == 0 && !itunesLink.isEmpty()){
            itunesLink.chop(1);
        }

        QString PodcastID = itunesLink;

        //If unable to find a podcast ID, return false
        if (PodcastID.toInt() == 0 || PodcastID.isEmpty()){
            ui->statusBar->showMessage("Itunes Link Invalid!", 3000);
        }
        //Create the request url using the podcast id
        QUrl url("https://itunes.apple.com/lookup?id=" + PodcastID + "&entity=podcast");
        //When the http request is finished, call the parseItunesReply function
        QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseItunesReply(QNetworkReply*)));
        //http request
        manager.get(QNetworkRequest(url));

    }
}

void MainWindow::parseItunesReply(QNetworkReply *reply){
    //If there is a reply error then display message
    if (reply->error() == QNetworkReply::NoError) {

        //parse the json reply and get the rss link string
        QString rssLink = QJsonDocument::fromJson(((QString)reply->readAll()).toUtf8())
                        .object()
                        .value("results")
                        .toArray()
                        .at(0)
                        .toObject().value("feedUrl").toString();

        //Call addPodcast function and pass rss link


        reply->deleteLater();
    }
    else {
        //reply error, display message
        ui->statusBar->showMessage("Network Request Failed..." + reply->errorString(), 3000);
        reply->deleteLater();
    }
}
