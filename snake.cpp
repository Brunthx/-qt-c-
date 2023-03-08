#include "snake.h"
#include"config.h"

Snake::Snake(QObject *parent)
    : QObject{parent}
{
    SnakeBody s;
    s.x=10;
    s.y=10;
    s_bodys.push_back(s);//从尾部添加
}

void Snake::SnakeInit()
{
    s_bodys.clear();//清理小蛇数据

    //初始化小蛇头部位置
    SnakeBody s;
    s.x=10;
    s.y=10;
    s_bodys.push_back(s);
}

bool Snake::isBeyondBoundary()
{
    //直接判断蛇头是否超出边界
    if(s_bodys[0].x<0||s_bodys[0].x>=GAME_MAX_W||s_bodys[0].y<0||s_bodys[0].y>=GAME_MAX_H)
    {
        return true;
    }
    return false;
}

bool Snake::isEatFood(Food food)
{
    if(s_bodys[0].x==food.x && s_bodys[0].y==food.y)
    {
        SnakeBody body;
        body.x=food.x;
        body.y=food.y;

        s_bodys.push_front(body);
        return true;
    }
    return false;
}

bool Snake::isHitItself()
{
    for(int i=s_bodys.size()-1;i>0;i--)
    {
        if(i!=0)
        {
            if(s_bodys[0].x==s_bodys[i].x && s_bodys[0].y==s_bodys[i].y)
            {
                return true;
            }
        }
    }
    return false;
}

void Snake::snakeMove(MoveDirection direction)
{
    for(int i=s_bodys.size()-1;i>0;i--)
    {
        if(i!=0)
        {
            s_bodys[i]=s_bodys[i-1];//例：第四节身子的坐标等于第三节身子的坐标
        }
    }

    switch(direction)
    {
        case moveRight:
            s_bodys[0].x += 1;
            break;
        case moveLeft:
            s_bodys[0].x -= 1;
            break;
        case moveUp:
            s_bodys[0].y -= 1;
            break;
        case moveDown:
            s_bodys[0].y += 1;
            break;
    }
}
