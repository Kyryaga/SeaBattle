#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(555, 309);

    gameController = new GameController();

    // ОТЛАДКА
    qDebug() << "Главное окно создано, контроллер инициализирован";
    qDebug() << "Координаты поля игрока: " << MYFIELD_X << ", " << MYFIELD_Y;

    // Отрисовка фона
    QPalette pal;
    pal.setBrush(QPalette::Active, QPalette::Window, QBrush(QPixmap(":/images/background.png")));
    this->setPalette(pal);
}

MainWindow::~MainWindow() {
    delete gameController;
}

QPoint MainWindow::getCoords(int x, int y)
{
    QPoint res;
    res.setX(-1);
    res.setY(-1);
    if (x<MYFIELD_X || x>(MYFIELD_X+FIELD_WIDTH) || y<MYFIELD_Y || y>(MYFIELD_Y+FIELD_HEIGHT)) return res;
    double cfx=1.0*FIELD_WIDTH/10.0;
    double cfy=1.0*FIELD_HEIGHT/10.0;
    res.setX(1.0*(x-MYFIELD_X)/cfx);
    res.setY(1.0*(y-MYFIELD_Y)/cfy);
    return res;
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // обработка нажатия правой кнопкой мыши
    if (event->button() == Qt::RightButton) {
        QPoint pos = event->pos();

        qDebug() << "Mouse click at (" << pos.x() << "," << pos.y() << ")";

    } else if (event->button() == Qt::LeftButton) {

        // проверяем состояние игры

        // если состояние = расстановка кораблей
        if (gameController->getGameState() == GameController::GameState::SHIPS_PLACING) {
            QPointF pos = event->position();

            if (pos.x() >= MYFIELD_X && pos.x() <= FIELD_WIDTH + MYFIELD_X
                && pos.y() >= MYFIELD_Y && pos.y() <= FIELD_HEIGHT + MYFIELD_Y) {
                qDebug() << "MyField" << "Coords:" << pos.x() << "," << pos.y() << getCoords(pos.x(), pos.y());

                QPoint qp = getCoords(pos.x(), pos.y());

                if (qp.x() == 10)
                    qp.setX(9);
                if (qp.y() == 10)
                    qp.setY(9);

                // проверяем, пуста ли клетка
                // если пуста ...

                points.append(qp);
                update(); // перерисовка полей(вызов функции paintEvent)
            }
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    for (const QPoint point : points) {
        QPoint drawPoint;
        if (point.x() < 5 && point.y() < 5) {
            drawPoint.setX(MYFIELD_X + (point.x() * CELL_SIZE));
            drawPoint.setY(MYFIELD_Y + (point.y() * CELL_SIZE));

        } else {
            drawPoint.setX(MYFIELD_HALF_X + ((point.x() - 5) * CELL_SIZE));
            drawPoint.setY(MYFIELD_HALF_Y + ((point.y() - 5) * CELL_SIZE));
        }

        painter.drawPixmap(drawPoint, QPixmap(":images/full.png"));
    }
}


