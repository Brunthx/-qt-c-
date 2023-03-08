#ifndef STRUCT_H
#define STRUCT_H
enum MoveDirection//�ߵ��ƶ�����
{
    moveUp,
    moveDown,
    moveLeft,
    moveRight
};

enum GameStatus//��Ϸ״̬
{
    gameInit,
    gameStart,
    gameOver
};

struct Block
{
    int x;//ˮƽ����ĸ��ӵ�����
    int y;//��ֱ����ĸ��ӵ�����
};

//�ߵ�����
struct SnakeBody:Block
{};

//ʳ��
struct Food:Block
{};

#endif // STRUCT_H
