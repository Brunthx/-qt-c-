#include "gamewidget.h"
#include<QPainter>
#include"config.h"
#include<QTimer>
#include<QTime>
#include<QtDebug>
#include<QKeyEvent>
#include <QRandomGenerator>
#include<QPainterPath>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    ,m_timer(new QTimer(this))
    ,m_direction(moveUp)
    ,m_status(0)
{
    QRandomGenerator(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));
    setFocusPolicy(Qt::ClickFocus);
    setFixedSize(GAME_WINDOW_WIDTH,GAME_WINDOW_HEIGHT);
    m_timer->setInterval(100);
    connect(m_timer,&QTimer::timeout,this,&GameWidget::slotTimer);
    m_food=createFood();
}

void GameWidget::start()
{
    setFocus();
    init();
    m_timer->start();
    m_status=1;
}

void GameWidget::stop()
{
    setFocus();
    init();
    m_timer->stop();
}

void GameWidget::pause()
{
    m_timer->stop();
}

void GameWidget::paintBackground(QPainter *painter)
{
    QPen pen=painter->pen();
    pen.width();//线的宽度
    painter->drawLine(0,0,0,this->height());
    painter->drawLine(GAME_WINDOW_WIDTH-pen.width(),0,GAME_WINDOW_WIDTH-pen.width(),this->height());
    painter->drawLine(0,0,this->width(),0);
    painter->drawLine(0,GAME_WINDOW_HEIGHT-pen.width(),this->width(),GAME_WINDOW_HEIGHT-pen.width());
}

void GameWidget::paintSnakebody(QPainter *painter)
{
    //QPainterPath path;
    int i=0;
    foreach (auto item, m_snake.s_bodys)
    {
        QRectF body=QRectF(item.x*BLOCK_WIDTH,item.y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH);

        //绘制蛇头
        if(i==0)
        {
            painter->setBrush(Qt::red);//蛇头红色
            painter->setPen(Qt::red);//线条为红色
            painter->drawRect(body);
        }
        else//绘制蛇身
        {
            painter->setBrush(Qt::transparent);//蛇身透明
            painter->setPen(Qt::red);//线条为红色
            painter->drawRect(body);
        }
        i=1;
    }
}

void GameWidget::paintFood(QPainter *painter)
{
    QPainterPath path;
    path.addEllipse(QRectF(m_food.x*BLOCK_WIDTH+2,m_food.y*BLOCK_WIDTH+2,BLOCK_WIDTH-4,BLOCK_WIDTH-4));
    painter->fillPath(path,QBrush(QColor(0,255,0)));
}

void GameWidget::paintCentreStr(QPainter *painter,QString str)
{
    QFont font;
    font.setPixelSize(50);
    painter->setFont(font);
    QFontMetrics fm(font);
    painter->drawText((GAME_WINDOW_WIDTH/2)-(fm.horizontalAdvance(str)/2),(GAME_WINDOW_HEIGHT/2),str);
}

void GameWidget::paintGameInit(QPainter *painter)
{
    paintCentreStr(painter,QString::fromLocal8Bit("贪吃蛇"));
}

void GameWidget::paintGameOver(QPainter *painter)
{
    paintCentreStr(painter,"Game Over!");
}

int GameWidget::get_random(int max)
{
    int res=QRandomGenerator::global()->bounded(0,32767);//代替qrand()
    res=res%max;
    qInfo()<<"random:"<<res;
    return res;
}

Food GameWidget::createFood()
{
    Food food;
    bool flag=false;
    do
    {
        flag=false;
        food.x=get_random(GAME_MAX_W);
        food.y=get_random(GAME_MAX_H);
        foreach (auto item, m_snake.s_bodys)
        {
            if(food.x==item.x && food.y==item.y)
            {
                flag=true;
            }
        }

        qInfo()<<"food.x:"<<food.x;
        qInfo()<<"food.y:"<<food.y;

    }while(flag);
    return food;
}

void GameWidget::init()
{
    m_food=createFood();

    m_score=0;
    emit sigUpdateScore(m_score);

    m_snake.SnakeInit();
}

void GameWidget::slotTimer()//计时器，游戏动起来的关键
{
    if(m_snake.isEatFood(m_food))
    {
        m_food=createFood();

        m_score++;
        emit sigUpdateScore(m_score);
    }

    m_snake.snakeMove(m_direction);

    if(m_snake.isHitItself())
    {
        m_status=gameOver;
        m_timer->stop();
    }
    else if(m_snake.isBeyondBoundary())
    {
        m_status=gameOver;
        m_timer->stop();
    }
    update();
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    paintBackground(&painter);
    if(gameStart==m_status)
    {
        paintFood(&painter);
        paintSnakebody(&painter);
    }
    else if(gameInit==m_status)
    {
        paintGameInit(&painter);
    }
    else
    {
        paintGameOver(&painter);
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    qInfo()<<"keyPressEvent start";
    switch (event->key())
    {
    case Qt::Key_Up:
        if(m_direction!=moveDown)
        {
            m_direction=moveUp;
            qInfo()<<"moveUp";
        }
        break;

    case Qt::Key_Down:
        if(m_direction!=moveUp)
        {
            m_direction=moveDown;
            qInfo()<<"moveDown";
        }
        break;

    case Qt::Key_Left:
        if(m_direction!=moveRight)
        {
            m_direction=moveLeft;
            qInfo()<<"moveLeft";
        }
        break;

    case Qt::Key_Right:
        if(m_direction!=moveLeft)
        {
            m_direction=moveRight;
            qInfo()<<"moveRight";
        }
        break;
    }
}
