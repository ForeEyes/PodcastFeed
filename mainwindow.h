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

#include <QCloseEvent>
#include <QSystemTrayIcon>

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

    void closeEvent (QCloseEvent *event);

    void setSliderRange(qint64 duration);

    void on_stopAudio_clicked();

    void updatePosition(qint64 timeElapsed);

    void on_pauseResumeAudio_clicked();

    void on_skip_backward_clicked();

    void on_skip_forward_clicked();

    void on_playPodcast_clicked();

    void setPosition(int position);

    void displayWindow();

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *manager;

    QString appDataFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/PodcastFeed";

    QString xmlFolder = appDataFolder + "/xml";

    QString iconFolder = appDataFolder + "/icons";

    QString appDataFile = appDataFolder + "/podcasts.json";

    QMediaPlayer *player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);

    QUrl episodeFile();

    void playAudio();
};

#endif // MAINWINDOW_H
