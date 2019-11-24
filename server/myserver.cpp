#include "myserver.h"
#include <QDateTime>

MyServer::MyServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);

    ran=QDateTime::currentMSecsSinceEpoch() / 1000;
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any,1234))
    {
        qDebug() << "Server could not start !";
    }
    else
    {
        qDebug() << "Server started !";
    }
}

void MyServer::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    qDebug() << "New Client";    
    qDebug() << socket->localAddress().toString();
    clients[st].cli=socket;
    st++;
    ready++;
    QString line=QString::number(ran)+"\n";
    socket->write(line.toUtf8());
    line=QString::number(st)+"\n";
    socket->write(line.toUtf8());
    qDebug() << line;    
    qDebug() << line;
    line.left(line.size()-1);
    qDebug() << line;

    if(st>1)
    {
        QTcpSocket *client = (QTcpSocket*)sender();
        for (int i=0; i<st; i++)
        {
            if (st==2)
                line="j2";
            else if (st==3)
                line="j3";
            else
                line="j4";
            if(client!=clients[i].cli)
               clients[i].cli->write(line.toUtf8()+"\n");
        }
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
}

void MyServer::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {        
        QString line = QString::fromUtf8(client->readLine()).trimmed();
        qDebug() << client->localAddress().toIPv4Address() << ":" << line;
        //QList <QTcpSocket*> cli = clients.toList();
        if(line=="p1rdy" || line=="p2rdy" || line=="p3rdy" || line=="p4rdy")
        {
            ready--;
            qDebug() << ready;
            if (ready==0 && st>=2)
            {
                for (int i=0; i<st; i++)
                {
                     QString line2 ="start\n";
                     clients[i].cli->write(line2.toUtf8());
                }
            }
        }

        for (int i=0; i<st; i++)
        {
            if(client!=clients[i].cli)
               clients[i].cli->write(line.toUtf8()+"\n");
        }        
    }   
}

void MyServer::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client disconnected:" << client->peerAddress().toString();
    //clients.remove(client);
    st--;
    if (st==0)
        ran=QDateTime::currentMSecsSinceEpoch() / 1000;
}
