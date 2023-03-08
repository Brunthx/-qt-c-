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
    int get_random(int max);// ��ȡ0 - max-1�������
    Food createFood();

    void init();

public slots:
    void slotTimer();//��ʱ������Ϸ�������Ĺؼ�

private:
    QTimer *m_timer;
    Snake m_snake;
    Food m_food;
    MoveDirection m_direction;
    int m_score;//�û��÷�
    int m_status;//�û�״̬

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void sigUpdateScore(int score);

};

#endif // GAMEWIDGET_H
