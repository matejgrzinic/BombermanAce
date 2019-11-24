#include <game.h>
#include <QGraphicsScene>
#include <player.h>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QImage>
#include <QTime>
#include <razbitina.h>
#include <QGraphicsView>
#include <QKeyEvent>
#include <bomba.h>
#include <QApplication>
#include <dodatek.h>
#include <QTimer>
#include <qdebug>
#include <QTime>
#include <QPushButton>
#include <QPointF>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <typeinfo>
#include <QThread>



Game::Game()
{

    scene= new QGraphicsScene(this);
    menu= new QGraphicsScene(this);


    // Velikost scene
    scene->setSceneRect(0,0,1008,1008);
    menu->setSceneRect(0,0,1008,1008);


    setScene(menu);

    //setScene(scene);

    //qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);






    // Nastavimo ozadje
    setBackgroundBrush(QBrush(QImage(":/images/bomberman")));





    setDragMode(QGraphicsView::NoDrag);


    // Nastavimo velikost scene
    setFixedSize((scene->height()+2)*0.8,(scene->width()+2)*0.8);

    // Naredimo da scene nemoremo scrollati
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    startt = new QTimer(this);
    startt->setInterval(1000);
    connect(startt,SIGNAL(timeout()),this,SLOT(pomansaj()));


    time = new QTimer(this);

    remaker = new QTimer(this);

    suddent = new QTimer (this);

    time->setInterval(1000);
    connect(time,SIGNAL(timeout()),this,SLOT(povecaj()));
   // time->start();

    time2 = new QTimer(this);
    time2->setInterval(100);
    connect(time2,SIGNAL(timeout()),this,SLOT(SuddenDeath()));

    gumb1 = new QPushButton("Play",this);
    gumb1->setGeometry(QRect(QPoint(1008/2-225, 400),
       QSize(250, 50)));

    gumb2 = new QPushButton("Exit",this);
    gumb2->setGeometry(QRect(QPoint(1008/2-225, 550),
       QSize(250, 50)));

    ip = new QLineEdit(this);
    ip->setGeometry(QRect(QPoint(1008/2-225, 300),
                          QSize(250, 30)));
    ip->setText("127.0.0.1");

    ig2 = new QPushButton("2 Players",this);
    ig2->setGeometry(QRect(QPoint(1008/2-225, 300),
       QSize(250, 50)));

    ig3 = new QPushButton("3 Players",this);
    ig3->setGeometry(QRect(QPoint(1008/2-225, 400),
       QSize(250, 50)));

    ig4 = new QPushButton("4 Players",this);
    ig4->setGeometry(QRect(QPoint(1008/2-225, 500),
       QSize(250, 50)));

    back = new QPushButton("Back",this);
    back->setGeometry(QRect(QPoint(1008/2-225, 600),
       QSize(250, 50)));
    
    connect(gumb1, SIGNAL (pressed()),this, SLOT (gumb1click()));
    connect(gumb2, SIGNAL (pressed()),this, SLOT (zapri()));
    connect(ig2, SIGNAL (pressed()),this, SLOT (ig2click()));
    connect(ig3, SIGNAL (pressed()),this, SLOT (ig3click()));
    connect(ig4, SIGNAL (pressed()),this, SLOT (ig4click()));
    connect(back, SIGNAL (pressed()),this, SLOT (backclick()));



    ig2->setVisible(false);
    ig3->setVisible(false);
    ig4->setVisible(false);
    back->setVisible(false);


    background = new QMediaPlayer();
    background->setMedia(QUrl("qrc:/sounds/background.mp3"));
    background->setVolume(50);

    scale(0.8,0.8);




}

void Game::NastaviPlayerja1()
{
    player=new Player(this);
    player->setPos(48,48);
    player->setPixmap(QPixmap(":/images/blue"));
    player->setFlag(QGraphicsItem::ItemIsFocusable);  
    scene->addItem(player);
    player->alive=true;
    player->velikost=1;
    player->bombe=1;
    player->ready=false;


    player->readyy->setFont(QFont("times",50,QFont::Bold));
    player->readyy->setDefaultTextColor(Qt::red);
    player->readyy->setPlainText(QString("NOT READY"));
    player->readyy->setZValue(6);
    player->readyy->setX(60);
    player->readyy->setY(230);
    scene->addItem(player->readyy);
    player->readyy->setVisible(false);

    player->tipke->setPixmap(QPixmap(":/images/tipke1"));
    player->tipke->setX(100);
    player->tipke->setY(100);
    player->tipke->setScale(0.5);
    player->tipke->setZValue(5);
    player->tipke->setVisible(false);
    scene->addItem(player->tipke);
}

void Game::NastaviPlayerja2()
{
    player2=new Player(this);
    player2->setPos(912,48);
    player2->setPixmap(QPixmap(":/images/red"));
    player2->setFlag(QGraphicsItem::ItemIsFocusable);
    player2->velikost=1;
    player2->bombe=1;   
    player2->alive=true;
    scene->addItem(player2);   
    player2->ready=false;

    player2->readyy->setFont(QFont("times",50,QFont::Bold));
    player2->readyy->setDefaultTextColor(Qt::red);
    player2->readyy->setPlainText(QString("NOT READY"));
    player2->readyy->setZValue(6);
    player2->readyy->setX(560);
    player2->readyy->setY(230);
    scene->addItem(player2->readyy);
    player2->readyy->setVisible(false);

    player2->tipke->setPixmap(QPixmap(":/images/tipke1"));
    player2->tipke->setX(600);
    player2->tipke->setY(100);
    player2->tipke->setScale(0.5);
    player2->tipke->setZValue(5);
    player2->tipke->setVisible(false);
    scene->addItem(player2->tipke);
}

void Game::NastaviPlayerja3()
{
    player3=new Player(this);
    player3->setPos(48,912);
    player3->setPixmap(QPixmap(":/images/green"));
    player3->setFlag(QGraphicsItem::ItemIsFocusable);
    player3->velikost=1;
    player3->bombe=1;
    player3->alive=true;
    scene->addItem(player3);
    player3->ready=false;

    player3->readyy->setFont(QFont("times",50,QFont::Bold));
    player3->readyy->setDefaultTextColor(Qt::red);
    player3->readyy->setPlainText(QString("NOT READY"));
    player3->readyy->setZValue(6);
    player3->readyy->setX(60);
    player3->readyy->setY(720);
    scene->addItem(player3->readyy);
    player3->readyy->setVisible(false);

    player3->tipke->setPixmap(QPixmap(":/images/tipke1"));
    player3->tipke->setX(85);
    player3->tipke->setY(780);
    player3->tipke->setScale(0.5);
    player3->tipke->setZValue(5);
    player3->tipke->setVisible(false);
    scene->addItem(player3->tipke);

}
void Game::NastaviPlayerja4()
{
    player4=new Player(this);
    player4->setPos(912,912);
    player4->setPixmap(QPixmap(":/images/pink"));
    player4->setFlag(QGraphicsItem::ItemIsFocusable);
    player4->velikost=1;
    player4->bombe=1;
    player4->alive=true;
    scene->addItem(player4);
    player4->ready=false;

    player4->readyy->setFont(QFont("times",50,QFont::Bold));
    player4->readyy->setDefaultTextColor(Qt::red);
    player4->readyy->setPlainText(QString("NOT READY"));
    player4->readyy->setZValue(6);
    player4->readyy->setX(560);
    player4->readyy->setY(720);
    scene->addItem(player4->readyy);
    player4->readyy->setVisible(false);

    player4->tipke->setPixmap(QPixmap(":/images/tipke1"));
    player4->tipke->setX(600);
    player4->tipke->setY(800);
    player4->tipke->setScale(0.5);
    player4->tipke->setZValue(5);
    player4->tipke->setVisible(false);
    scene->addItem(player4->tipke);
}

void Game::Okvir()
{
    for (int i=0; i<20; i++)
    {
        DodajRazb(i,0);
        DodajRazb(0,i+1);
        DodajRazb(i+1,20);
        DodajRazb(20,i);
    }
    for (int i=3; i<=18; )
    {
         for (int j=3; j<=18;){
             DodajRazb(j,i);
             j=j+3;}
         i=i+3;
    }
}



void Game::Skatle()
{
    int ax,ay,hully;

        for (int i=48; i<scene->height();)
        {
            int j=48;
            int n=scene->height();
            if (i==48 || i==912)
                {
                    j=144;
                    n=864;
                }
            if (i==96 || i==864)
                {
                    j=96;
                    n=912;
                }

        for(; j<n;)
        {

            ax=j/48;
            ay=i/48;
            if(!zasedenost[ax][ay].zapoljenost)
            {
                hully=qrand()%100;
                if (hully>40)
                {
                    Razbitina *razbitina=new Razbitina(this);
                    razbitina->setPos(j,i);
                    razbitina->setScale(0.75);
                    scene->addItem(razbitina);
                    zasedenost[ax][ay].zapoljenost=true;
                    zasedenost[ax][ay].povezava=razbitina;
                }
            }
            j=j+48;
        }
        i=i+48;
        }
}

void Game::keyPressEvent(QKeyEvent *event)
{
    QString line;
    if (igra)
    {
        int premik=48;
        int premik2=48;
        int ax1,ay1;
        int ax2,ay2;
        int ax3,ay3;
        int ax4,ay4;
        ax1=player->pos().x()/48;
        ay1=player->pos().y()/48;
        ax2=player2->pos().x()/48;
        ay2=player2->pos().y()/48;
        ax3=player3->pos().x()/48;
        ay3=player3->pos().y()/48;
        ax4=player4->pos().x()/48;
        ay4=player4->pos().y()/48;
        if(igralec==1)
        {

            if (event->key() == Qt::Key_Left && player->alive==true)
            {

                    if (!zasedenost[ax1-1][ay1].zapoljenost && !zasedenost[ax1-1][ay1].bomba)
                    {
                         player->setPos(player->x()-premik,player->y());
                         SuperP(ax1-1,ay1,player);
                         line="p1l\n";
                         socket->write(line.toUtf8());
                    }

            }
            else if (event->key() == Qt::Key_Right && player->alive==true)
            {
                    if (!zasedenost[ax1+1][ay1].zapoljenost && !zasedenost[ax1+1][ay1].bomba)
                    {
                          player->setPos(player->x()+premik,player->y());
                          SuperP(ax1+1,ay1,player);
                          line="p1r\n";
                          socket->write(line.toUtf8());
                    }
            }
            else if (event->key() == Qt::Key_Up && player->alive==true)
            {

                    if (!zasedenost[ax1][ay1-1].zapoljenost && !zasedenost[ax1][ay1-1].bomba)
                    {
                            player->setPos(player->x(),player->y()-premik);
                            SuperP(ax1,ay1-1,player);
                            line="p1u\n";
                            socket->write(line.toUtf8());
                    }
            }
            else if (event->key() == Qt::Key_Down && player->alive==true)
            {

                    if (!zasedenost[ax1][ay1+1].zapoljenost && !zasedenost[ax1][ay1+1].bomba)
                    {
                        player->setPos(player->x(),player->y()+premik);
                        SuperP(ax1,ay1+1,player);
                        line="p1d\n";
                        socket->write(line.toUtf8());
                    }

            }

            else if (event->key() == Qt::Key_Space && player->alive==true && player->bombe>0 && player->bomb==true)
                    {
                        Bomba *bomba = new Bomba(this->player);
                        bomba->setPos(player->x()+player->pixmap().height()/50,player->y()+player->pixmap().width()/50);
                        this->scene->addItem(bomba);
                        int bx=bomba->x()/48;
                        int by=bomba->y()/48;
                        this->zasedenost[bx][by].bomba=true;
                        player->bombe--;
                        player->bomb=false;
                        player->timebomb=player->multbomb;
                        player->timerbomb->start(100);
                        line="p1b\n";
                        socket->write(line.toUtf8());
                    }

        }
        else if (igralec==2)
        {
                    if (event->key() == Qt::Key_Left && player2->alive==true)
                            {

                                if (!zasedenost[ax2-1][ay2].zapoljenost && !zasedenost[ax2-1][ay2].bomba)
                                {
                                     player2->setPos(player2->x()-premik2,player2->y());
                                     SuperP(ax2-1,ay2,player2);
                                     line="p2l\n";
                                     socket->write(line.toUtf8());
                                }


                    }
                    else if (event->key() == Qt::Key_Right && player2->alive==true)
                    {

                            if (!zasedenost[ax2+1][ay2].zapoljenost && !zasedenost[ax2+1][ay2].bomba)
                            {
                                  player2->setPos(player2->x()+premik2,player2->y());
                                  SuperP(ax2+1,ay2,player2);
                                  line="p2r\n";
                                  socket->write(line.toUtf8());
                            }

                    }
                    else if (event->key() == Qt::Key_Up && player2->alive==true)
                    {

                            if (!zasedenost[ax2][ay2-1].zapoljenost && !zasedenost[ax2][ay2-1].bomba)
                            {
                                    player2->setPos(player2->x(),player2->y()-premik2);
                                    SuperP(ax2,ay2-1,player2);
                                    line="p2u\n";
                                    socket->write(line.toUtf8());
                            }

                    }
                    else if (event->key() == Qt::Key_Down && player2->alive==true)
                    {

                            if (!zasedenost[ax2][ay2+1].zapoljenost && !zasedenost[ax2][ay2+1].bomba)
                            {

                                     player2->setPos(player2->x(),player2->y()+premik2);
                                     SuperP(ax2,ay2+1,player2);
                                     line="p2d\n";
                                     socket->write(line.toUtf8());
                            }

                    }
                    else if (event->key() == Qt::Key_Space && player2->alive==true && player2->bombe>0 && player2->bomb==true)
                            {
                                Bomba *bomba = new Bomba(this->player2);
                                bomba->setPos(player2->x()+player2->pixmap().height()/50,player2->y()+player2->pixmap().width()/50);
                                this->scene->addItem(bomba);
                                int bx=bomba->x()/48;
                                int by=bomba->y()/48;
                                zasedenost[bx][by].bomba=true;
                                player2->bombe--;
                                player2->bomb=false;
                                player2->timebomb=player2->multbomb;
                                player2->timerbomb->start(100);
                                line="p2b\n";
                                socket->write(line.toUtf8());
                            }

        }
        else if (igralec==3)
        {
            if (event->key() == Qt::Key_Left && player3->alive==true)
                    {

                            if (!zasedenost[ax3-1][ay3].zapoljenost && !zasedenost[ax3-1][ay3].bomba)
                            {
                                 player3->setPos(player3->x()-premik,player3->y());
                                 SuperP(ax3-1,ay3,player3);
                                 line="p3l\n";
                                 socket->write(line.toUtf8());
                            }

                    }
                    else if (event->key() == Qt::Key_Right && player3->alive==true)
                    {
                            if (!zasedenost[ax3+1][ay3].zapoljenost && !zasedenost[ax3+1][ay3].bomba)
                            {
                                  player3->setPos(player3->x()+premik,player3->y());
                                  SuperP(ax3+1,ay3,player3);
                                  line="p3r\n";
                                  socket->write(line.toUtf8());
                            }
                    }
                    else if (event->key() == Qt::Key_Up && player3->alive==true)
                    {

                            if (!zasedenost[ax3][ay3-1].zapoljenost && !zasedenost[ax3][ay3-1].bomba)
                            {
                                    player3->setPos(player3->x(),player3->y()-premik);
                                    SuperP(ax3,ay3-1,player3);
                                    line="p3u\n";
                                    socket->write(line.toUtf8());
                            }
                    }
                    else if (event->key() == Qt::Key_Down && player3->alive==true)
                    {

                            if (!zasedenost[ax3][ay3+1].zapoljenost && !zasedenost[ax3][ay3+1].bomba)
                            {
                                player3->setPos(player3->x(),player3->y()+premik);
                                SuperP(ax3,ay3+1,player3);
                                line="p3d\n";
                                socket->write(line.toUtf8());
                            }

                    }
                      else if (event->key() == Qt::Key_Space && player3->alive==true && player3->bombe>0 && player3->bomb==true)
                    {
                        Bomba *bomba = new Bomba(this->player3);
                        bomba->setPos(player3->x()+player3->pixmap().height()/50,player3->y()+player3->pixmap().width()/50);
                        this->scene->addItem(bomba);
                        int bx=bomba->x()/48;
                        int by=bomba->y()/48;
                        this->zasedenost[bx][by].bomba=true;
                        player3->bombe--;
                        player3->bomb=false;
                        player3->timebomb=player3->multbomb;
                        player3->timerbomb->start(100);
                        line="p3b\n";
                        socket->write(line.toUtf8());
                    }
        }
        else if (igralec==4)
        {
            if (event->key() == Qt::Key_Left && player4->alive==true)
                    {

                            if (!zasedenost[ax4-1][ay4].zapoljenost && !zasedenost[ax4-1][ay4].bomba)
                            {
                                 player4->setPos(player4->x()-premik,player4->y());
                                 SuperP(ax4-1,ay4,player4);
                                 line="p4l\n";
                                 socket->write(line.toUtf8());
                            }

                    }
                    else if (event->key() == Qt::Key_Right && player4->alive==true)
                    {
                            if (!zasedenost[ax4+1][ay4].zapoljenost && !zasedenost[ax4+1][ay4].bomba)
                            {
                                  player4->setPos(player4->x()+premik,player4->y());
                                  SuperP(ax4+1,ay4,player4);
                                  line="p4r\n";
                                  socket->write(line.toUtf8());
                            }
                    }
                    else if (event->key() == Qt::Key_Up && player4->alive==true)
                    {

                            if (!zasedenost[ax4][ay4-1].zapoljenost && !zasedenost[ax4][ay4-1].bomba)
                            {
                                    player4->setPos(player4->x(),player4->y()-premik);
                                    SuperP(ax4,ay4-1,player4);
                                    line="p4u\n";
                                    socket->write(line.toUtf8());
                            }
                    }
                    else if (event->key() == Qt::Key_Down && player4->alive==true)
                    {

                            if (!zasedenost[ax4][ay4+1].zapoljenost && !zasedenost[ax4][ay4+1].bomba)
                            {
                                player4->setPos(player4->x(),player4->y()+premik);
                                SuperP(ax4,ay4+1,player4);
                                line="p4d\n";
                                socket->write(line.toUtf8());
                            }

                    }
                    else if (event->key() == Qt::Key_Space && player4->alive==true && player4->bombe>0 && player4->bomb==true)
                    {
                        Bomba *bomba = new Bomba(this->player4);
                        bomba->setPos(player4->x()+player4->pixmap().height()/50,player4->y()+player4->pixmap().width()/50);
                        this->scene->addItem(bomba);
                        int bx=bomba->x()/48;
                        int by=bomba->y()/48;
                        this->zasedenost[bx][by].bomba=true;
                        player4->bombe--;
                        player4->bomb=false;
                        player4->timebomb=player4->multbomb;
                        player4->timerbomb->start(100);
                        line="p4b\n";
                        socket->write(line.toUtf8());
                    }
        }
    }
    else
    {
        if (igralec==1)
        {
             if (event->key() == Qt::Key_Space && !player->ready)
             {
                 player->ready=true;
                 player->readyy->setPlainText(QString("   READY"));
                 player->readyy->setDefaultTextColor(Qt::green);
                 readyig--;
                 line="p1rdy\n";
                 socket->write(line.toUtf8());
                 if (readyig==0)
                 {
                     startt->start();
                     time->start();
                     zac->setVisible(true);
                 }
             }
         }
        else if (igralec==2)
        {
            if (event->key() == Qt::Key_Space && !player2->ready)
                 {
                     player2->ready=true;
                     player2->readyy->setPlainText(QString("   READY"));
                     player2->readyy->setDefaultTextColor(Qt::green);
                     readyig--;
                     line="p2rdy\n";
                     socket->write(line.toUtf8());
                     if (readyig==0)
                     {
                         startt->start();
                         time->start();
                         zac->setVisible(true);
                     }
                 }
        }
        else if (igralec==3)
        {
            if (event->key() == Qt::Key_Space && !player3->ready)
                 {
                     player3->ready=true;
                     player3->readyy->setPlainText(QString("   READY"));
                     player3->readyy->setDefaultTextColor(Qt::green);
                     readyig--;
                     line="p3rdy\n";
                     socket->write(line.toUtf8());
                     if (readyig==0)
                     {
                         startt->start();
                         time->start();
                         zac->setVisible(true);
                     }
                 }
        }
        else if (igralec==4)
        {
            if (event->key() == Qt::Key_Space && !player4->ready)
                 {
                     player4->ready=true;
                     player4->readyy->setPlainText(QString("   READY"));
                     player4->readyy->setDefaultTextColor(Qt::green);
                     readyig--;
                     line="p4rdy\n";
                     socket->write(line.toUtf8());
                     if (readyig==0)
                     {
                         startt->start();
                         time->start();
                         zac->setVisible(true);
                     }
                 }
        }
    }

}

void Game::end()
{
    background->stop();
    time->stop();
    time2->stop();
    suddent->stop();
    igra=false;
    QString niz;
    if (player->alive)
        niz=" Player 1 WINS ";
    else if (player2->alive)
        niz=" Player 2 WINS ";
    else if (player3->alive)
        niz=" Player 3 WINS ";
    else if (player4->alive)
        niz=" Player 4 WINS ";
    else
        niz="   GAME OVER";

    zac->setPlainText(niz);
    zac->setFont(QFont("times",90));
    zac->setX(70);
    zac->setY(350);
    zac->setZValue(7);
    zac->setVisible(true);
    connect(remaker,SIGNAL(timeout()),this,SLOT(remake()));
    remaker->start(5000);
}

void Game::dodatek(int x, int y)
{
    int o=qrand()%100;
    int cx=x/48,cy=y/48;
    if (o>=90)
    {
        Dodatek *tmp=new Dodatek();
        zasedenost[cx][cy].link=tmp;
        zasedenost[cx][cy].add=true;
        tmp->velikost=true;
        tmp->setPos(x,y);
        tmp->setPixmap(QPixmap(":/images/nuke"));
        scene->addItem(tmp);
    }
    else if (o>=80)
    {
        Dodatek *tmp=new Dodatek();
        zasedenost[cx][cy].link=tmp;
        zasedenost[cx][cy].add=true;
        tmp->setPos(x,y);
        tmp->cas=true;
        tmp->setPixmap(QPixmap(":/images/timebomb"));
        scene->addItem(tmp);
    }
    else if (o>=70)
    {
        Dodatek *tmp=new Dodatek();
        zasedenost[cx][cy].link=tmp;
        zasedenost[cx][cy].add=true;
        tmp->setPos(x,y);
        tmp->stevilo=true;
        tmp->setPixmap(QPixmap(":/images/stevilo"));
        scene->addItem(tmp);
    }
}

void Game::SuperP(int ax,int ay,Player *p)
{
    if (zasedenost[ax][ay].add==true)
    {        
        zasedenost[ax][ay].add=false;
        if (zasedenost[ax][ay].link->velikost)
            p->velikost++;
        else if (zasedenost[ax][ay].link->stevilo)
            p->bombe++;
        else
        {
            if (p->multbomb>100)
                p->multbomb=p->multbomb-100;
        }
        scene->removeItem(zasedenost[ax][ay].link);
        delete zasedenost[ax][ay].link;
        zasedenost[ax][ay].link=NULL;
    }

}





bool Game::Sudden()
{
    if (igra)
    {
        while(am<8)
        {
            while (ai<20-am)
            {
                DodajRazb(ai,aj);
                Umor(ai,aj);
                ai++;
                return 1;

            }
            while (ak<20-am)
            {
                DodajRazb(ai,ak);
                Umor(ai,ak);
                ak++;
                return 1;
            }
            while (al>am)
            {
                DodajRazb(al,ai);
                Umor(al,ai);
                al--;
                return 1;
            }
            while (an>am)
            {
                DodajRazb(aj,an);
                Umor(aj,an);
                an--;
                return 1;
            }


            am++;
            ai=am;
            ak=am;
            al=20-am;
            an=al;
            aj++;
        }
    }
    return 0;
}


void Game::DodajRazb(int x, int y)
{
    Razbitina *zid = new Razbitina(this);
    zid->setPos(x*48,y*48);
    zid->setScale(0.75);
    scene->addItem(zid);
    zasedenost[x][y].zapoljenost=true;
    zasedenost[x][y].zid=true;
    zid->setPixmap(QPixmap(":/images/zid"));
    zasedenost[x][y].povezava=zid;
}

void Game::Umor(int x, int y)
{
    QPointF p1=player->pos();
    QPointF p2=player2->pos();
    QPointF p3=player3->pos();
    QPointF p4=player4->pos();
    QPoint ogenj;
    ogenj.setX(x*48);
    ogenj.setY(y*48);
    if (ogenj==p1 && player->alive)
    {
        igralci--;
        scene->removeItem(player);
        player->alive=false;
    }

    if (ogenj==p2 && player2->alive)
    {
        igralci--;
        scene->removeItem(player2);
        player2->alive=false;
    }
    if (ogenj==p3 && player3->alive)
    {
        igralci--;
        scene->removeItem(player3);
        player3->alive=false;
    }

    if (ogenj==p4 && player4->alive)
    {
        igralci--;
        scene->removeItem(player4);
        player4->alive=false;
    }
    if (igralci==1)
        end();
}

void Game::nastavi()
{

    zacetek=3;
    cas=0;
    ai=1;
    aj=1;
    am=1;
    ak=1;
    al=20;
    an=20;
    igralci=2;
    for (int i=0; i<21; i++)
    {
        for (int j=0; j<21; j++)
        {
            zasedenost[i][j].zapoljenost=false;
            zasedenost[i][j].povezava=NULL;
            zasedenost[i][j].zid=false;
        }
    }
    NastaviPlayerja1();
    NastaviPlayerja2();
    NastaviPlayerja3();
    NastaviPlayerja4();
    Okvir();
    Skatle();





    zac=new QGraphicsTextItem();
    zac->setDefaultTextColor(Qt::yellow);
    zac->setFont(QFont("times",250));
    zac->setPlainText(QString("") + QString::number(zacetek));
    zac->setX(440);
    zac->setY(250);
    scene->addItem(zac);
    zac->setVisible(false);

   // background->play();


}



void Game::povecaj()
{
    cas++;    
    if (background->state() == QMediaPlayer::StoppedState)
        background->play();
    if (cas==40)
    {        
        time2->start();        ;
        zac->setPlainText(QString("SUDDEN DEATH"));
        zac->setFont(QFont("times",90));
        zac->setX(70);
        zac->setY(350);
        zac->setVisible(true);        
        connect(suddent,SIGNAL(timeout()),this,SLOT(izrisi()));
        suddent->start(3000);
    }
}

void Game::SuddenDeath()
{    

    Sudden();

}

void Game::izrisi()
{
    zac->setVisible(false);
}

void Game::zapri()
{
    QApplication::quit();
}

void Game::remake()
{
    socket->disconnect();
    socket->disconnectFromHost();
    remaker->stop();
    QList<QGraphicsItem *> stvari = scene->items();
        for (int i=0,n=stvari.size(); i<n; i++)
        {
            if((typeid(*(stvari[i]))==typeid(Razbitina)) || (typeid(*(stvari[i]))==typeid(Player)) ||
                    (typeid(*(stvari[i]))==typeid(Dodatek)))
            {
                scene->removeItem(stvari[i]);
            }
        }
    setBackgroundBrush(QBrush(QImage(":/images/bomberman")));
    setScene(menu);
    gumb1->setVisible(true);
    gumb2->setVisible(true);
    zac->setVisible(false);
}

void Game::backclick()
{
    gumb1->setVisible(true);
    gumb2->setVisible(true);
    ip->setVisible(true);
    ig2->setVisible(false);
    ig3->setVisible(false);
    ig4->setVisible(false);
    back->setVisible(false);
}


void Game::readyRead()
{
    while(socket->canReadLine())
    {        
        QString line = QString::fromUtf8(socket->readLine());
        qDebug() << line;
        if (line=="1\n")
        {
            nastavi();
            igralec=1;
            ig2click();
            player->tipke->setVisible(true);
        }
        else if (line=="2\n")
        {
            nastavi();
            igralec=2;
            ig2click();
            player2->tipke->setVisible(true);
        }
        else if (line=="3\n")
        {
            nastavi();
            igralec=3;
            ig3click();
            player3->tipke->setVisible(true);
        }
        else if (line=="4\n")
        {
            nastavi();
            igralec=4;
            ig4click();
            player4->tipke->setVisible(true);
        }
        else if (line=="j2\n")
        {
            ig2click();
        }
        else if (line=="j3\n")
        {
            ig3click();
            player3->alive=true;
            scene->addItem(player3);
        }
        else if (line=="j4\n")
        {
            ig4click();
            player4->alive=true;
            scene->addItem(player4);

        }
        else if (line=="p1l\n")
        {
            player->setPos(player->x()-48,player->y());
            SuperP(player->pos().x()/48,player->pos().y()/48,player);
        }
        else if (line=="p1r\n")
        {
            player->setPos(player->x()+48,player->y());
            SuperP(player->pos().x()/48,player->pos().y()/48,player);
        }
        else if (line=="p1u\n")
        {
            player->setPos(player->x(),player->y()-48);
            SuperP(player->pos().x()/48,player->pos().y()/48,player);
        }
        else if (line=="p1d\n")
        {
            player->setPos(player->x(),player->y()+48);
            SuperP(player->pos().x()/48,player->pos().y()/48,player);
        }
        else if (line=="p2l\n")
        {
            player2->setPos(player2->x()-48,player2->y());
            SuperP(player2->pos().x()/48,player2->pos().y()/48,player2);
        }
        else if (line=="p2r\n")
        {
            player2->setPos(player2->x()+48,player2->y());
            SuperP(player2->pos().x()/48,player2->pos().y()/48,player2);
        }
        else if (line=="p2u\n")
        {
            player2->setPos(player2->x(),player2->y()-48);
            SuperP(player2->pos().x()/48,player2->pos().y()/48,player2);
        }
        else if (line=="p2d\n")
        {
            player2->setPos(player2->x(),player2->y()+48);
            SuperP(player2->pos().x()/48,player2->pos().y()/48,player2);
        }
        else if (line=="p3l\n")
        {
            player3->setPos(player3->x()-48,player3->y());
            SuperP(player3->pos().x()/48,player3->pos().y()/48,player3);
        }
        else if (line=="p3r\n")
        {
            player3->setPos(player3->x()+48,player3->y());
            SuperP(player3->pos().x()/48,player3->pos().y()/48,player3);
        }
        else if (line=="p3u\n")
        {
            player3->setPos(player3->x(),player3->y()-48);
            SuperP(player3->pos().x()/48,player3->pos().y()/48,player3);
        }
        else if (line=="p3d\n")
        {
            player3->setPos(player3->x(),player3->y()+48);
            SuperP(player3->pos().x()/48,player3->pos().y()/48,player3);
        }
        else if (line=="p4l\n")
        {
            player4->setPos(player4->x()-48,player4->y());
            SuperP(player4->pos().x()/48,player4->pos().y()/48,player4);
        }
        else if (line=="p4r\n")
        {
            player4->setPos(player4->x()+48,player4->y());
            SuperP(player4->pos().x()/48,player4->pos().y()/48,player4);
        }
        else if (line=="p4u\n")
        {
            player4->setPos(player4->x(),player4->y()-48);
            SuperP(player4->pos().x()/48,player4->pos().y()/48,player4);
        }
        else if (line=="p4d\n")
        {
            player4->setPos(player4->x(),player4->y()+48);
            SuperP(player4->pos().x()/48,player4->pos().y()/48,player4);
        }
        else if(line=="p1rdy\n")
        {
            player->ready=true;
            player->readyy->setPlainText(QString("   READY"));
            player->readyy->setDefaultTextColor(Qt::green);
        }
        else if(line=="p2rdy\n")
        {
            player2->ready=true;
            player2->readyy->setPlainText(QString("   READY"));
            player2->readyy->setDefaultTextColor(Qt::green);
        }
        else if(line=="p3rdy\n")
        {
            player3->ready=true;
            player3->readyy->setPlainText(QString("   READY"));
            player3->readyy->setDefaultTextColor(Qt::green);
        }
        else if(line=="p4rdy\n")
        {
            player4->ready=true;
            player4->readyy->setPlainText(QString("   READY"));
            player4->readyy->setDefaultTextColor(Qt::green);
        }
        else if(line=="start\n")
        {
            startt->start();
            time->start();
            zac->setVisible(true);

        }
        else if(line=="p1b\n")
        {
            Bomba *bomba = new Bomba(this->player);
            bomba->setPos(player->x()+player->pixmap().height()/50,player->y()+player->pixmap().width()/50);
            this->scene->addItem(bomba);
            int bx=bomba->x()/48;
            int by=bomba->y()/48;
            this->zasedenost[bx][by].bomba=true;
            player->bombe--;
            player->bomb=false;
            player->timebomb=player->multbomb;
            player->timerbomb->start(100);
        }
        else if(line=="p2b\n")
        {
            Bomba *bomba = new Bomba(this->player2);
            bomba->setPos(player2->x()+player2->pixmap().height()/50,player2->y()+player2->pixmap().width()/50);
            this->scene->addItem(bomba);
            int bx=bomba->x()/48;
            int by=bomba->y()/48;
            this->zasedenost[bx][by].bomba=true;
            player2->bombe--;
            player2->bomb=false;
            player2->timebomb=player2->multbomb;
            player2->timerbomb->start(100);
        }
        else if(line=="p3b\n")
        {
            Bomba *bomba = new Bomba(this->player3);
            bomba->setPos(player3->x()+player3->pixmap().height()/50,player3->y()+player3->pixmap().width()/50);
            this->scene->addItem(bomba);
            int bx=bomba->x()/48;
            int by=bomba->y()/48;
            this->zasedenost[bx][by].bomba=true;
            player3->bombe--;
            player3->bomb=false;
            player3->timebomb=player3->multbomb;
            player3->timerbomb->start(100);
        }
        else if(line=="p4b\n")
        {
            Bomba *bomba = new Bomba(this->player4);
            bomba->setPos(player4->x()+player4->pixmap().height()/50,player4->y()+player4->pixmap().width()/50);
            this->scene->addItem(bomba);
            int bx=bomba->x()/48;
            int by=bomba->y()/48;
            this->zasedenost[bx][by].bomba=true;
            player4->bombe--;
            player4->bomb=false;
            player4->timebomb=player4->multbomb;
            player4->timerbomb->start(100);
        }
        else
        {
            int ran=line.toInt();
            qDebug() << "abc: " << ran;
            srand(ran);
        }
    }    
}





void Game::gumb1click()
{

    gumb1->setVisible(false);
    gumb2->setVisible(false);
    ip->setVisible(false);
//    ig2->setVisible(true);
//    ig3->setVisible(true);
//    ig4->setVisible(true);
//    back->setVisible(true);
    // ig4click();
    povezi();
}

void Game::povezi()
{
    socket = new QTcpSocket();
    socket->connectToHost(ip->text(),1234);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}



void Game::ig2click()
{
    //nastavi();
    setBackgroundBrush(QBrush(QImage(":/images/ozadje")));
    ig2->setVisible(false);
    ig3->setVisible(false);
    ig4->setVisible(false);
    back->setVisible(false);
    setScene(scene);
    scene->removeItem(player3);
    player3->alive=false;
    scene->removeItem(player4);
    player4->alive=false;
    igralci=2;

//    player->tipke->setVisible(true);
//    player2->tipke->setVisible(true);

    player3->ready=true;
    player4->ready=true;

    readyig=2;

    player->readyy->setVisible(true);
    player2->readyy->setVisible(true);



//    player2->setPos(912,912);
//    player2->readyy->setPos(560,720);
//    player2->tipke->setPos(600,800);



}

void Game::ig3click()
{
    //nastavi();
    setBackgroundBrush(QBrush(QImage(":/images/ozadje")));
    ig2->setVisible(false);
    ig3->setVisible(false);
    ig4->setVisible(false);
    back->setVisible(false);
    setScene(scene);
    scene->removeItem(player4);
    player4->alive=false;
    igralci=3;

//    player->tipke->setVisible(true);
//    player2->tipke->setVisible(true);
//    player3->tipke->setVisible(true);

    player4->ready=true;

    readyig=3;

    player->readyy->setVisible(true);
    player2->readyy->setVisible(true);
    player3->readyy->setVisible(true);





}

void Game::ig4click()
{
    //nastavi();
    setBackgroundBrush(QBrush(QImage(":/images/ozadje")));
    ig2->setVisible(false);
    ig3->setVisible(false);
    ig4->setVisible(false);
    back->setVisible(false);
    setScene(scene);
    igralci=4;

//    player->tipke->setVisible(true);
//    player2->tipke->setVisible(true);
//    player3->tipke->setVisible(true);
//    player4->tipke->setVisible(true);

    readyig=4;

    player->readyy->setVisible(true);
    player2->readyy->setVisible(true);
    player3->readyy->setVisible(true);
    player4->readyy->setVisible(true);




}

void Game::pomansaj()
{
    zacetek--;
    zac->setPlainText(QString("") + QString::number(zacetek));
    if (zacetek==0)
    {
        startt->stop();
        igra=true;
        cas=0;
        player->tipke->setVisible(false);
        player->readyy->setVisible(false);
        player2->tipke->setVisible(false);
        player2->readyy->setVisible(false);
        player3->tipke->setVisible(false);
        player3->readyy->setVisible(false);
        player4->tipke->setVisible(false);
        player4->readyy->setVisible(false);
        zac->setVisible(false);
    }
}


