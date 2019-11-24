#include "razbitina.h"
#include <game.h>
#include <QDebug>

extern Game * game;

Razbitina::Razbitina(QGraphicsView *parent)
{
    setPixmap(QPixmap(":/images/block1"));
}

Razbitina::~Razbitina()
{
    delete this;
}

void Razbitina::zbrisi()
{
    game->scene->removeItem(this);
    delete this;
}
