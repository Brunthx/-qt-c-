#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include<QVector>
#include"struct.h"

class Snake : public QObject
{
    Q_OBJECT
public:
    explicit Snake(QObject *parent = nullptr);

    void snakeMove(MoveDirection direction);//移动方向

    bool isHitItself();//撞到自己

    bool isBeyondBoundary();//超出游戏边界

    bool isEatFood(Food food);//吃到食物

    void SnakeInit();//对蛇进行初始化

    QVector<SnakeBody>s_bodys;
};

#endif // SNAKE_H
