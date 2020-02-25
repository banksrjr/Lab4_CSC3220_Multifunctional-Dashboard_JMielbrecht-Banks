#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      timer(new QTimer),
      HTTPManager(new httpManager)
{
    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()),
            this, SLOT(setCurrentTime()));

    setCurrentTime();
    timer->start(1000);

    connect(HTTPManager, SIGNAL(ImageReady(QPixmap *)),
            this, SLOT(processImage(QPixmap *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentTime()
{
    QTime time = QTime::currentTime();
    QString hour = time.toString("hh");
    QString minute = time.toString("mm");
    QString second = time.toString("ss");

    ui->hourLCD->display(hour);
    ui->minuteLCD->display(minute);
    ui->secondLCD->display(second);
}

void MainWindow::processImage(QPixmap *image)
{
    ui->imageLabel->setPixmap(*image);
}

void MainWindow::on_imageDownloadButton_clicked()
{
    QString zip = ui->zipCodeInput->text();
    qDebug() << zip;
    HTTPManager->sendImageRequest(zip);
}


// Delete this Comment later
