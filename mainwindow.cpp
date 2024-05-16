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
    // обработка нажатия правой кнопкой мыши - ОТЛАДКА
    if (event->button() == Qt::RightButton) {
        QPoint pos = event->pos();

        qDebug() << "Mouse click at (" << pos.x() << "," << pos.y() << ")";

    }

    // нажатие левой кнопкой мыши
    else if (event->button() == Qt::LeftButton) {

        // если состояние = расстановка кораблей
        if (gameController->getGameState() == GameState::SHIPS_PLACING) {
            QPointF pos = event->position();

            if (pos.x() >= MYFIELD_X && pos.x() <= FIELD_WIDTH + MYFIELD_X
                && pos.y() >= MYFIELD_Y && pos.y() <= FIELD_HEIGHT + MYFIELD_Y) {
                qDebug() << "MyField" << "Coords:" << pos.x() << "," << pos.y() << getCoords(pos.x(), pos.y());

                QPoint qp = getCoords(pos.x(), pos.y());

                if (qp.x() == 10)
                    qp.setX(9);
                if (qp.y() == 10)
                    qp.setY(9);

                if (gameController->isPlayerEmptyCell(qp)) {
                    if (gameController->getPlayerShipCellsCount() < 20) {
                        gameController->setPlayerCellState(qp, 2);

                        if (gameController->checkPlayerShipPlacement()) {
                            gameController->printPlayerAllCellStates();



                            // gameController->setGameState(GameState::PLAYER_TURN);
                        }
                    }
                } else {
                    gameController->setPlayerCellState(qp, 0);
                }


                update();

            }
        }
    }
}

// добавить перебор cells каждый ход и соответствующую перерисовку
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QVector<Cell> currentCellsState = gameController->getPlayerAllCells();

    for (int i {0}; i < currentCellsState.size(); i++) {
        if (currentCellsState[i] == Cell::SHIP) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(MYFIELD_X + (x * CELL_SIZE));
                drawPoint.setY(MYFIELD_Y + (y * CELL_SIZE));
            } else {
                drawPoint.setX(MYFIELD_HALF_X + ((x - 5) * CELL_SIZE));
                drawPoint.setY(MYFIELD_HALF_Y + ((y - 5) * CELL_SIZE));
            }

            painter.drawPixmap(drawPoint, QPixmap(":images/full.png"));
        }
    }
}


