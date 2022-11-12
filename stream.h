#ifndef STREAM_H
#define STREAM_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>

class stream:public QThread
{
    Q_OBJECT
public:
    stream(QObject *parent = nullptr, std::string source = "");
    stream(QObject *parent = nullptr, int source = 0);
    QPixmap pixmap() const
    {
        return myPixmap;
    }
signals:
    void newPixmapCaptured();
protected:
    void run() override;
private:
    QPixmap myPixmap; // converted image to be displayed
    cv::Mat myFrame; // openCV image
    cv::VideoCapture myVideoCap; // video stream

    QImage cvMatToQImage( const cv::Mat &inMat );
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );
};

#endif // STREAM_H
