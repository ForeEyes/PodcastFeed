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
#include <QBuffer>

#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

#include <QSettings>

#include <QFileInfo>

#include "podcastmanager.h"

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

    void CreateEpisodeTextFile(QString podcastName, QString episodeName);

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

    void closeWindow();

    void bufferPlayEpisode();

    bool FileExists(QString filechkPath);

    void SaveSettings();

    void LoadSettings();

    void on_actionSave_Settings_triggered();

    void on_actionLoad_Settings_triggered();

    void on_actionEnable_Buffering_triggered();

    void on_actionSort_Order_Ascending_triggered();

    void on_actionSort_Order_Descending_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *manager;

    QString appDataFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/PodcastFeed";

    QString xmlFolder = appDataFolder + "/xml";

    QString txtListened = appDataFolder + "/listened";

    QString iconFolder = appDataFolder + "/icons";

    QString appDataFile = appDataFolder + "/podcasts.json";

    PodcastManager podcastMgr;

    QMediaPlayer *player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);

    QUrl episodeFile();

    void refreshPodcasts();

    bool canClose = false;

    QBuffer immPlay;
};

#endif // MAINWINDOW_H
