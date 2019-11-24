#include "player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <bomba.h>
#include <game.h>
#include <QDebug>

extern Game * game;


Player::Player(QGraphicsView *parent)
{
    timerbomb= new QTimer();
    connect(timerbomb,SIGNAL(timeout()),this,SLOT(bombacas()));
    timerbomb->setInterval(100);




    readyy=new QGraphicsTextItem();
    tipke=new QGraphicsPixmapItem();
}



Player::~Player()
{
    delete this;
}

void Player::bombacas()
{
    timebomb=timebomb-100;
    if (timebomb==0)
    {
        timerbomb->stop();
        bomb=true;
    }
}


