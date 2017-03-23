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

#include <QMediaPlayer>

// Temporary code to populate the episode list until the SSL issue is resolved
// https://github.com/ForeEyes/PodcastFeed/issues/10
#include <QStringList>
#include <QStringListModel>

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

    void on_PodcastList_clicked(const QModelIndex &index);

    void on_EpisodeList_clicked(const QModelIndex &index);

    void updateUIPodcastList();

    QString addPodcast_dlg(QString Label, QString Title, bool &ok);

    void getRSSurl(QString itunesLink);

    void parseItunesReply(QNetworkReply *reply);

    void addPodcast(QString rssLink);

    void storeXmlFile(QString podcastName, QByteArray rawReply);

    void storeIcon(QString podcastName, QString iconURL);

    void addPodcast_toAppDataFile(QString podcastName, QString rssLink);

    void removePodcast_fromAppDataFile(QString podcastName);

    bool checkPodcastExists(QString podcastName);

    void on_playButton_clicked();

    void on_playerSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager* manager;

    QString appDataFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/PodcastFeed";

    QString xmlFolder = appDataFolder + "/xml";

    QString iconFolder = appDataFolder + "/icons";

    QString appDataFile = appDataFolder + "/podcasts.json";

    QMediaPlayer *player = new QMediaPlayer;

    QString getURL(QString episode);

    QUrl episodeFile();

    void playAudio(QString URL);

    // Temporary code to populate the episode list until the SSL issue is resolved
    // https://github.com/ForeEyes/PodcastFeed/issues/10
    void populatePodcasts();
};

#endif // MAINWINDOW_H
