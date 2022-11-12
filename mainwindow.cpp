#include "mainwindow.h"
#include "stream.h"
#include <opencv2/opencv.hpp>
#include <QLabel>
#include <QPixmap>

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // set up screen1 which is my webcam
    screen1 = new QLabel(this);
    screen1->resize(500, 500);
    openCvStream1 = new stream(this, 0);
    openCvStream1->start(QThread::HighestPriority);
    connect(openCvStream1, &stream::newPixmapCaptured, this->screen1, [&]()
            { screen1->setPixmap(openCvStream1->pixmap().scaledToWidth(500)); });
    // Note: for MacOS, I have to add this to Info.plist file
    //     <key>NSCameraUsageDescription</key>
    //     <string>Uses camera to see vision targets</string>

    // set up screen2 which is an online video
    screen2 = new QLabel(this);
    screen2->resize(500, 500);
    screen2->move(550, 0);
    openCvStream2 = new stream(this, "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mp4");
    openCvStream2->start(QThread::HighestPriority);
    connect(openCvStream2, &stream::newPixmapCaptured, this->screen2, [&]()
            { screen2->setPixmap(openCvStream2->pixmap().scaledToWidth(500)); });

    // set up screen3 which is a locally stored video
    screen3 = new QLabel(this);
    screen3->resize(500, 500);
    screen3->move(1100, 0);
    openCvStream3 = new stream(this, "/Users/aaron/Desktop/videoplayback.mp4");
    openCvStream3->start(QThread::HighestPriority);
    connect(openCvStream3, &stream::newPixmapCaptured, this->screen3, [&]()
            { screen3->setPixmap(openCvStream3->pixmap().scaledToWidth(500)); });
}

MainWindow::~MainWindow()
{
    openCvStream1->terminate();
    openCvStream2->terminate();
    openCvStream3->terminate();
}
