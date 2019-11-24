#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <player.h>

class MyServer : public QObject
{
    Q_OBJECT
public:
    MyServer(QObject *parent = 0);
    int st=0;
    int ran;
    int ready=0;
public slots:
    void newConnection();
    void disconnected();
    void readyRead();
private slots:

private:
    QTcpServer *server;    
    player clients[4];
};

#endif // MYSERVER_H
