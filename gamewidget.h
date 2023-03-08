#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "snake.h"

class QPainter;
class QTimer;
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);

    void start();
    void stop();
    void pause();

private:
    void paintBackground(QPainter *painter);
    void paintSnakebody(QPainter *painter);
    void paintGameInit(QPainter *painter);
    void paintGameOver(QPainter *painter);
    void paintCentreStr(QPainter *painter,QString str);
    void paintFood(QPainter *painter);
    int get_random(int max);// 获取0 - max-1的随机数
    Food createFood();

    void init();

public slots:
    void slotTimer();//计时器，游戏动起来的关键

private:
    QTimer *m_timer;
    Snake m_snake;
    Food m_food;
    MoveDirection m_direction;
    int m_score;//用户得分
    int m_status;//用户状态

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void sigUpdateScore(int score);

};

#endif // GAMEWIDGET_H
