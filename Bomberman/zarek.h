#ifndef ZAREK_H
#define ZAREK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>


class Zarek: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Zarek(QGraphicsView *parent=0);
public slots:
    void zbrisi();
};

#endif // ZAREK_H
