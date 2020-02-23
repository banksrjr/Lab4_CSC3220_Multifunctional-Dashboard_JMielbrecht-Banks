#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

class httpManager : public QObject
{
    Q_OBJECT
public:
    explicit httpManager(QObject *parent = nullptr);
    ~httpManager();

    void sendImageRequest();

signals:
    void ImageReady(QPixmap *image);

public slots:
    void ImageDownloadedHandler(QNetworkReply * reply);

private:
    QNetworkAccessManager * imageDownloadManager;
    QByteArray downloadedData;

};

#endif // HTTPMANAGER_H
