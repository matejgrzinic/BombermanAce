#include "zarek.h"
#include <QTimer>
#include <game.h>


extern Game * game;

Zarek::Zarek(QGraphicsView *parent)
{
    setPixmap(QPixmap(":/images/ogenj"));
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(zbrisi()));
    timer->start(500);
}



void Zarek::zbrisi()
{    
    scene()->removeItem(this);
    delete this;
}

