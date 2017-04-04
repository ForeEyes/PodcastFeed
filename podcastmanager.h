#ifndef PODCASTMANAGER_H
#define PODCASTMANAGER_H

#include <QString>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

#include <QXmlStreamReader>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFile>
#include <QStandardPaths>

#include <QEventLoop>

#include <QImage>

class PodcastManager
{
public:
    PodcastManager();

    QString addPodcast(QString Link, QString Type);

    QString removePodcast(QString podcastName);


private:

    QNetworkAccessManager *manager;

    QString appDataFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/PodcastFeed";

    QString xmlFolder = appDataFolder + "/xml";

    QString iconFolder = appDataFolder + "/icons";

    QString appDataFile = appDataFolder + "/podcasts.json";

    bool getRSSurl(QString itunesLink, QString &rssLink);

    bool storeXmlFile(QString podcastName, QByteArray rawReply);

    bool storeIcon(QString podcastName, QString iconURL);

    bool addPodcast_toAppDataFile(QString podcastName, QString rssLink);

    bool removePodcast_fromAppDataFile(QString podcastName);

    bool checkPodcastExists(QString podcastName);

};

#endif // PODCASTMANAGER_H
