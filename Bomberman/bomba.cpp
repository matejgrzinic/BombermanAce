#include "bomba.h"
#include <QTimer>
#include <game.h>
#include <zarek.h>
#include <QDebug>
#include <QList>
#include <typeinfo>
#include <QPointF>
#include <razbitina.h>

extern Game * game;



Bomba::Bomba(Player *parent)
{
    // Nastavimo bombo
    setPixmap(QPixmap(":/images/bomb2"));
    setScale(0.3515);
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(zbrisi()));
    timer->start(1500);
    oce=parent;

    bombsound = new QMediaPlayer();
    bombsound->setMedia(QUrl("qrc:/sounds/bomb.mp3"));
    bombsound->setVolume(50);
}

void Bomba::zbrisi()
{
    // Naredimo zarke
    int premik=48;
    Zarek *fire = new Zarek(game);

    fire->setPos(x(),y());
    scene()->addItem(fire);

    Umor(fire);

    int ax;
    int ay;

    if(bombsound->state()==QMediaPlayer::PlayingState)
        bombsound->setPosition(0);
    else if (bombsound->state() == QMediaPlayer::StoppedState)
        bombsound->play();

    for (int i=0, mx=x()+premik; i< this->oce->velikost; i++)
    {
        ax=mx/48;
        ay=y()/48;
        if (game->zasedenost[ax][ay].zapoljenost)
        {
            if (!game->zasedenost[ax][ay].zid)
            {
                scene()->removeItem(game->zasedenost[ax][ay].povezava);
                game->dodatek(ax*48,ay*48);
                game->zasedenost[ax][ay].zapoljenost=false;
                game->zasedenost[ax][ay].povezava=NULL;
            }
            break;
        }
        else
        {
            Zarek *fire = new Zarek(game);
            fire->setPos(mx,y());
            scene()->addItem(fire);
            Umor(fire);
            mx+=premik;
        }
    }

    for (int i=0, mx=x()-premik; i< this->oce->velikost; i++)
    {
        ax=mx/48;
        ay=y()/48;
        if (game->zasedenost[ax][ay].zapoljenost)
        {
            if (!game->zasedenost[ax][ay].zid)
            {
                scene()->removeItem(game->zasedenost[ax][ay].povezava);
                game->dodatek(ax*48,ay*48);
                game->zasedenost[ax][ay].zapoljenost=false;
                game->zasedenost[ax][ay].povezava=NULL;
            }
            break;
        }
        else
        {
            Zarek *fire = new Zarek(game);
            fire->setPos(mx,y());
            scene()->addItem(fire);
            Umor(fire);
            mx-=premik;
        }
    }
    for (int i=0, mx=y()-premik; i< this->oce->velikost; i++)
    {
        ax=x()/48;
        ay=mx/48;
        if (game->zasedenost[ax][ay].zapoljenost)
        {
            if (!game->zasedenost[ax][ay].zid)
            {
                scene()->removeItem(game->zasedenost[ax][ay].povezava);
                game->dodatek(ax*48,ay*48);
                game->zasedenost[ax][ay].zapoljenost=false;
                game->zasedenost[ax][ay].povezava=NULL;
            }
            break;
        }
        else
        {
            Zarek *fire = new Zarek(game);
            fire->setPos(x(),mx);
            scene()->addItem(fire);
            Umor(fire);
            mx-=premik;
        }
    }
    for (int i=0, mx=y()+premik; i< this->oce->velikost; i++)
    {
        ax=x()/48;
        ay=mx/48;
        if (game->zasedenost[ax][ay].zapoljenost)
        {
            if (!game->zasedenost[ax][ay].zid)
            {
                scene()->removeItem(game->zasedenost[ax][ay].povezava);
                game->dodatek(ax*48,ay*48);
                game->zasedenost[ax][ay].zapoljenost=false;
                game->zasedenost[ax][ay].povezava=NULL;
            }
            break;
        }
        else
        {
            Zarek *fire = new Zarek(game);
            fire->setPos(x(),mx);
            scene()->addItem(fire);
            Umor(fire);
            mx+=premik;
        }
    }
    int bx=this->x()/48;
    int by=this->y()/48;
    this->oce->bombe++;
    game->zasedenost[bx][by].bomba=false;
    scene()->removeItem(this);
    delete this;
}

void Bomba::Umor(Zarek *tmp)
{
    QPointF p1=game->player->pos();
    QPointF p2=game->player2->pos();
    QPointF p3=game->player3->pos();
    QPointF p4=game->player4->pos();
    QPointF ogenj=tmp->pos();

    if (ogenj==p1 && game->player->alive)
    {
        game->igralci--;
        game->scene->removeItem(game->player);
        game->player->alive=false;
    }

    if (ogenj==p2 && game->player2->alive)
    {
        game->igralci--;
        game->scene->removeItem(game->player2);
        game->player2->alive=false;
    }
    if (ogenj==p3 && game->player3->alive)
    {
        game->igralci--;
        game->scene->removeItem(game->player3);
        game->player3->alive=false;
    }

    if (ogenj==p4 && game->player4->alive)
    {
        game->igralci--;
        game->scene->removeItem(game->player4);
        game->player4->alive=false;
    }
    if (game->igralci<=1)
        game->end();
}
