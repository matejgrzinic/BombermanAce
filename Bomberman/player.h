#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QGraphicsView *parent=0);
    ~Player();
    int velikost=1;
    int bombe=1;

    QTimer *timerbomb;
    bool bomb=true;

    bool alive=true;
    bool ready=false;


    int timebomb=0;
    int multbomb=600;

    QTimer *timerpremik;
    QGraphicsTextItem *readyy;
    QGraphicsPixmapItem *tipke;
public slots:
    void bombacas();

};

#endif // PLAYER_H
