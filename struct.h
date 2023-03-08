#ifndef STRUCT_H
#define STRUCT_H
enum MoveDirection//蛇的移动方向
{
    moveUp,
    moveDown,
    moveLeft,
    moveRight
};

enum GameStatus//游戏状态
{
    gameInit,
    gameStart,
    gameOver
};

struct Block
{
    int x;//水平方向的格子的坐标
    int y;//垂直方向的格子的坐标
};

//蛇的身体
struct SnakeBody:Block
{};

//食物
struct Food:Block
{};

#endif // STRUCT_H
