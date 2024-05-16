#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamecontroller.h"
#include <QMouseEvent>
#include <QPixMap>
#include <QPainter>
#include <QImage>
#include <QVector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPoint getCoords(int x, int y);

private:
    GameController* gameController;
    QVector<QPoint> points;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};


#endif // MAINWINDOW_H
