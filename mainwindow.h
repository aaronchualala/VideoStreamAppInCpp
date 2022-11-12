#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

class stream;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel *screen1;
    QLabel *screen2;
    QLabel *screen3;
    stream *openCvStream1;
    stream *openCvStream2;
    stream *openCvStream3;
};
#endif // MAINWINDOW_H
