#include "stream.h"
#include <QDebug>

// two constructors:
//    To instantiate device camera stream, need to pass in int 0
//    To instantiate online/local video stream, need to pass in string url/filepath
stream::stream(QObject *parent, int source)
    : QThread{parent}, myVideoCap{source}
{
}
stream::stream(QObject *parent, std::string source)
    : QThread{parent}, myVideoCap{source}
{
}

// run thread to continuously read next frame from source and emit signal,
// which will be received by QLabel slot, until video ends
void stream::run()
{
   if (myVideoCap.isOpened())
   {
      while (true)
      {
         myVideoCap.read(myFrame);
         if (!myFrame.empty())
         {
            myPixmap = cvMatToQPixmap(myFrame);
            emit newPixmapCaptured();
            cv::waitKey(5);
         }
      }
   }
}

// helper function to convert OpenCV format to qt QImage format
QImage stream::cvMatToQImage(const cv::Mat &inMat)
{
   switch (inMat.type())
   {
   // 8-bit, 4 channel
   case CV_8UC4:
   {
      QImage image(inMat.data,
                   inMat.cols, inMat.rows,
                   static_cast<int>(inMat.step),
                   QImage::Format_ARGB32);

      return image;
   }

   // 8-bit, 3 channel
   case CV_8UC3:
   {
      QImage image(inMat.data,
                   inMat.cols, inMat.rows,
                   static_cast<int>(inMat.step),
                   QImage::Format_RGB888);

      return image.rgbSwapped();
   }

   // 8-bit, 1 channel
   case CV_8UC1:
   {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
      QImage image(inMat.data,
                   inMat.cols, inMat.rows,
                   static_cast<int>(inMat.step),
                   QImage::Format_Grayscale8);
#else
      static QVector<QRgb> sColorTable;

      // only create our color table the first time
      if (sColorTable.isEmpty())
      {
         sColorTable.resize(256);

         for (int i = 0; i < 256; ++i)
         {
            sColorTable[i] = qRgb(i, i, i);
         }
      }

      QImage image(inMat.data,
                   inMat.cols, inMat.rows,
                   static_cast<int>(inMat.step),
                   QImage::Format_Indexed8);

      image.setColorTable(sColorTable);
#endif

      return image;
   }

   default:
      qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
      break;
   }

   return QImage();
}

// helper function to convert QImage to pixmap as QLabel uses latter
QPixmap stream::cvMatToQPixmap(const cv::Mat &inMat)
{
   return QPixmap::fromImage(cvMatToQImage(inMat));
}
