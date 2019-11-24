#ifndef RAZBITINA_H
#define RAZBITINA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>


class Razbitina: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Razbitina(QGraphicsView *parent=0);
    ~Razbitina();
public slots:
    void zbrisi();
};

#endif // RAZBITINA_H
