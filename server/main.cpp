#include <QCoreApplication>
#include <QDebug>
#include <myserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer mServer;


    return a.exec();
}
