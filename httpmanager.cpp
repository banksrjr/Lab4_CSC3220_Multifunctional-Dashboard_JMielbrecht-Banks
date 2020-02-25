#include "httpmanager.h"
#include <iostream>

httpManager::httpManager(QObject *parent) : QObject(parent),
    imageDownloadManager(new QNetworkAccessManager)
{
    connect(imageDownloadManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(ImageDownloadedHandler(QNetworkReply*)));
}

httpManager::~httpManager()
{
    delete imageDownloadManager;
}

void httpManager::sendImageRequest(QString zip)
{
    QNetworkRequest request;
    QString address = "https://dev.virtualearth.net/REST/V1/Imagery/Map/Road/"
            + zip
            + "/13?mapSize=600,300&mapLayer=TrafficFlow&format=png&key=At14ISaQrcssgnbusM6kAkN-0CIQJxhompctQATywuF-rk_-H9HJ41Ad7VKIPBjO";
    request.setUrl(QUrl(address));
    imageDownloadManager->get(request);
    qDebug() << "Image Request Sent to Address " << request.url();
}

void httpManager::ImageDownloadedHandler(QNetworkReply *reply)
{
    qDebug() << "Image Reply has Arrived";
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "Download  was Successful";
    QPixmap *image = new QPixmap();
    image->loadFromData(reply->readAll());


    emit ImageReady(image);
}


// Delete this Comment later
