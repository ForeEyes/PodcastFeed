#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QInputDialog>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QXmlStreamReader>

#include <QDir>
#include <QStandardPaths>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionUsing_Itunes_Link_triggered();

    void on_actionUsing_RSS_Link_triggered();

    void on_actionRefresh_Feed_triggered();

    void on_actionRemove_Podcast_triggered();

    QString addPodcast_dlg(QString Label, QString Title, bool &ok);

    void getRSSurl(QString itunesLink);

    void parseItunesReply(QNetworkReply *reply);

    void addPodcast(QString rssLink);

    void storeXmlFile(QString podcastName, QByteArray rawReply);

    void storeIcon(QString podcastName, QString iconURL);

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager* manager;

    QString AppDataFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/PodcastFeed";

    QString xmlFolder = AppDataFolder + "/xml";

    QString IconFolder = AppDataFolder + "/icons";
};

#endif // MAINWINDOW_H
