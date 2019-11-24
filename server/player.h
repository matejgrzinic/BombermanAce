#ifndef PLAYER_H
#define PLAYER_H

#include <QTcpSocket>

class player
{
public:
    player();
    QTcpSocket *cli;
    int x;
    int y;
};

#endif // PLAYER_H
