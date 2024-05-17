#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamecontroller.h"
#include <QMouseEvent>
#include <QPixMap>
#include <QPainter>
#include <QImage>
#include <QVector>
#include <QLabel>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPoint getCoordsPlayer(int x, int y);
    QPoint getCoords(int x, int y, int fieldX, int fieldY);

private:
    GameController* gameController;
    QLabel* infoLabel;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};


#endif // MAINWINDOW_H
