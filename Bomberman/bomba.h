#ifndef BOMBA_H
#define BOMBA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
#include <player.h>
#include <zarek.h>
#include <QMediaPlayer>

class Bomba: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QMediaPlayer *bombsound;
public:
    Bomba(Player *tmp);
    Player *oce;
    void Umor(Zarek *tmp);
public slots:
    void zbrisi();    
};


#endif // BOMBA_H
