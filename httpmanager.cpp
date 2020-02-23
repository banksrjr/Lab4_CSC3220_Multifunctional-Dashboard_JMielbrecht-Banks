#include "httpmanager.h"

httpManager::httpManager(QObject *parent) : QObject(parent),
    imageDownloadManager(new QNetworkAccessManager)
{
    connect(imageDownloadManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(ImageDownloadedHandler(QNetworkReply)));
}

httpManager::~httpManager()
{
    delete imageDownloadManager;
}

void httpManager::sendImageRequest()
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://spu.edu/depts/uc/VIS/images/Screen/JPEG/logo-spu-legacy-maroon.jpg"));
    imageDownloadManager->get(request);
    qDebug() << "Image Reguest Sent to Address " << request.url();
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
