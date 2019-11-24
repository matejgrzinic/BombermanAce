#ifndef SCENA_H
#define SCENA_H

#include <QGraphicsScene>

class Scena: public QGraphicsScene
{
public:
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // SCENA_H
