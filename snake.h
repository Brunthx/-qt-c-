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

    void snakeMove(MoveDirection direction);//�ƶ�����

    bool isHitItself();//ײ���Լ�

    bool isBeyondBoundary();//������Ϸ�߽�

    bool isEatFood(Food food);//�Ե�ʳ��

    void SnakeInit();//���߽��г�ʼ��

    QVector<SnakeBody>s_bodys;
};

#endif // SNAKE_H
