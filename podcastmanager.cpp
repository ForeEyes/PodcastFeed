#include "podcastmanager.h"

PodcastManager::PodcastManager()
{

}

QString PodcastManager::addPodcast(QString Link, QString Type){
    QString rssLink;


    if(Type == "itunes"){
        if(!getRSSurl(Link, rssLink)){
            return "Invalid Itunes Link!";
        }
    } else if(Type == "rss" || Type == "refresh"){
        rssLink = Link;
    }

    //Create a event loop to keep everythin inline, rather than using other functions.
    QEventLoop eventLoop;
    //create new network manager
    manager = new QNetworkAccessManager();
    //When the http request is finished, end the eventloop
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    //Make the http request and store as a QNetworkReply Object
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(rssLink)));
    //Start the loop
    eventLoop.exec();

    QString podcastName, podcastIconURL;
    bool nameReached = false, iconReached = false;

    //check if reply is not xml or if there is an error
    if (reply->error() == QNetworkReply::NoError && reply->header(QNetworkRequest::ContentTypeHeader).toString().contains("xml")){
        QByteArray rawReply = reply->readAll();
        //Create a xml parser object
        QXmlStreamReader podcastXml;
        //Pass the reply to the xml parser
        podcastXml.addData(rawReply);
        //Loop until end of xml doc
        while(!podcastXml.atEnd() && !podcastXml.hasError()) {
            // Read next element
            QXmlStreamReader::TokenType token = podcastXml.readNext();
            //If token is just StartDocument - go to next
            if(token == QXmlStreamReader::StartDocument) {
                    continue;
            }
            //If token is StartElement - read it
            if(token == QXmlStreamReader::StartElement){
                //If the element name is title and is the first title element, save it
                if(podcastXml.name() == "title" && !nameReached){
                    podcastName = podcastXml.readElementText();
                    nameReached = true;
                }
                //If the element name is image and is the first image element, save the url
                if(podcastXml.qualifiedName() == "itunes:image" && !iconReached){
                    podcastIconURL = podcastXml.attributes().value("href").toString();
                    iconReached = true;
                }
                //If both name and icon url have been parsed, then break loop
                if(nameReached && iconReached){
                    break;
                }
            }
        }

        if(!podcastName.isEmpty() && !podcastIconURL.isEmpty()){
            if(!storeXmlFile(podcastName, rawReply)){
                return podcastName + ": Error Saving xml file";
            } else if(!storeIcon(podcastName, podcastIconURL)){
                return podcastName + ": Failed to store podcast icon";
            } else if(!addPodcast_toAppDataFile(podcastName, rssLink) && Type != "refresh"){
                return podcastName + ": Podcast Already Exists!";
            }
        }
        if(Type != "refresh"){
            return podcastName + ": Podcast Added!";
        } else {
            return podcastName + ": Feed Refreshed!";
        }
    } else {
        //reply error or reply is not xml
        reply->deleteLater();
        return "RSS Link Invalid or Request Failed";
    }
}

QString PodcastManager::removePodcast(QString podcastName){
    //Remove podcast from app data file
    if(removePodcast_fromAppDataFile(podcastName)){
        //Remove xml file
        QFile podcastXML(xmlFolder + "/" + podcastName + ".xml");
        podcastXML.remove();
        //Remove icon file
        QFile podcastIcon(iconFolder + "/" + podcastName + ".bmp");
        podcastIcon.remove();

        return "Podcast Removed";
    } else{
        return "Podcast does not exist!";
    }
}

//Take Itunes Link, make http request, get json reply
//Parse json reply and find the rss link for podcast
bool PodcastManager::getRSSurl(QString itunesLink, QString &rssLink){
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
            return false;
        }
        //Create a event loop to keep everythin inline, rather than using other functions.
        QEventLoop eventLoop;
        //Create the request url using the podcast id
        QUrl url("https://itunes.apple.com/lookup?id=" + PodcastID + "&entity=podcast");
        //create new network manager
        manager = new QNetworkAccessManager();
        //When the http request is finished, call the parseItunesReply function
        QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        //http request
        QNetworkReply *reply = manager->get(QNetworkRequest(url));
        //Start the loop
        eventLoop.exec();

        //If there is a reply error then display message
        if (reply->error() == QNetworkReply::NoError) {

            //parse the json reply and get the rss link string
            rssLink = QJsonDocument::fromJson(((QString)reply->readAll()).toUtf8())
                    .object()
                    .value("results")
                    .toArray()
                    .at(0)
                    .toObject().value("feedUrl").toString();

            reply->deleteLater();

            return true;
        }
        else {
            //reply error, return false
            reply->deleteLater();
            return false;
        }

    } else {
        return false;
    }
}

bool PodcastManager::storeXmlFile(QString podcastName, QByteArray rawReply){
    //Podcast xml file path
    QString podcastFile = xmlFolder + "/" + podcastName + ".xml";

    QFile xmlfile(podcastFile);
    //Open the file and write the data to it
    if (xmlfile.open(QFile::WriteOnly) )
    {
        xmlfile.write(rawReply);
        //close file
        xmlfile.close();
        return true;
    } else {
        //close file
        xmlfile.close();
        return false;
    }
}

bool PodcastManager::storeIcon(QString podcastName, QString iconURL){
    //Create a event loop to keep everythin inline, rather than using other functions.
    QEventLoop eventLoop;
    //create new network manager
    manager = new QNetworkAccessManager();
    //When the http request is finished, end the eventloop
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    //Make the http request and store as a QNetworkReply Object
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(iconURL)));
    //Start the loop
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        //Icon File Path
        QString IconPath = iconFolder + "/" + podcastName + ".bmp";
        //using QImage to convert from unknown format to bmp
        QImage icon;
        //load reply data into icon
        icon.loadFromData(reply->readAll());
        //unless icon data is null store image as bmp at the given path
        if(icon.isNull()){
            return false;
        } else {
            icon.save(IconPath);
            return true;
        }
        reply->deleteLater();
    } else {
        //Failed to get icon
        reply->deleteLater();
        return false;
    }
}

bool PodcastManager::addPodcast_toAppDataFile(QString podcastName, QString rssLink){
    //check if the podcast already exists
    if(!checkPodcastExists(podcastName)){

        QFile jsonFile(appDataFile);
        jsonFile.open(QFile::ReadWrite);

        QJsonDocument document = QJsonDocument().fromJson(jsonFile.readAll());
        //If this is a new file, i.e first time adding a podcast, create the json object and store in file
        if(jsonFile.pos() == 0){
            QJsonObject jsonObject;
            QJsonObject arrayObject{
                {"podcastName", podcastName},
                {"rssLink", rssLink}
            };
            QJsonArray jsonArray;
            jsonArray.append(arrayObject);
            jsonObject.insert("Podcasts", jsonArray);
            document.setObject(jsonObject);
            jsonFile.write(document.toJson());
            jsonFile.close();
        }else{
        //If this is not a new file, edit the json object and store in file
            QJsonObject jsonObject = document.object();
            QJsonObject arrayObject{
                {"podcastName", podcastName},
                {"rssLink", rssLink}
            };
            QJsonArray jsonArray = jsonObject["Podcasts"].toArray();
            jsonArray.append(arrayObject);
            jsonObject.insert("Podcasts", jsonArray);
            document.setObject(jsonObject);
            jsonFile.close();
            //reopen file inorder to clear existing data and place the updated podcasts object
            jsonFile.open(QFile::WriteOnly | QFile::Truncate);
            jsonFile.write(document.toJson());
            jsonFile.close();

        }

        return true;
    }else{
        return false;
    }
}

bool PodcastManager::removePodcast_fromAppDataFile(QString podcastName){
    if(checkPodcastExists(podcastName)){
        //keep track of the array element in foreach loop
        int podcastNumber = 0;

        QFile jsonFile(appDataFile);
        jsonFile.open(QFile::ReadWrite);

        QJsonDocument document = QJsonDocument().fromJson(jsonFile.readAll());

        QJsonObject jsonObject = document.object();

        QJsonArray jsonArray = jsonObject["Podcasts"].toArray();
        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            if(obj["podcastName"].toString() == podcastName){
                //if the podcast is found, remove it from array using the podcastNumber
                jsonArray.removeAt(podcastNumber);
                break;
            }else{
                //else update number
                podcastNumber++;
            }
        }
        jsonObject.insert("Podcasts", jsonArray);
        document.setObject(jsonObject);
        jsonFile.close();
        //reopen file inorder to clear existing data and place the updated podcasts object
        jsonFile.open(QFile::WriteOnly | QFile::Truncate);
        jsonFile.write(document.toJson());
        jsonFile.close();

        return true;
    }else{
        return false;
    }
}

bool PodcastManager::checkPodcastExists(QString podcastName){
    //Open json file as read only
    QFile jsonFile(appDataFile);
    //if file does not exit return false
    if(!jsonFile.open(QFile::ReadOnly)){
        return false;
    }else{
        //convert all object in the app data file into an array
        QJsonDocument document = QJsonDocument().fromJson(jsonFile.readAll());
        QJsonObject jsonObject = document.object();
        QJsonArray jsonArray = jsonObject["Podcasts"].toArray();

        //go through array and look for the podcast
        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            if(obj["podcastName"].toString() == podcastName){
                //if the podcast is found return true
                jsonFile.close();
                return true;
            }
        }
    }
    //If the podcast is not found return false
    jsonFile.close();
    return false;
}
