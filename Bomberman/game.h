#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <player.h>
#include <prostor.h>
#include <QObject>
#include <QPushButton>
#include <QMediaPlayer>
#include <QTcpSocket>
#include <QLineEdit>




class Game: public QGraphicsView
{
    Q_OBJECT
private:
    QMediaPlayer *background;
    int ai=1;
    int aj=1;
    int am=1;
    int ak=1;
    int al=20;
    int an=20;
public:
    int igralec;
    QTcpSocket *socket;
    int readyig;
    QPushButton *gumb1;
    QPushButton *gumb2;
    QPushButton *back;
    QPushButton *ig2;
    QPushButton *ig3;
    QPushButton *ig4;
    QLineEdit *ip;
    Game();
    QGraphicsScene *menu;
    QGraphicsScene *scene;    
    int igralci=4;
    Player *player;
    Player *player2;
    Player *player3;
    Player *player4;    
    Prostor zasedenost[21][21];
    void povezi();
    void NastaviPlayerja1();
    void NastaviPlayerja2();
    void NastaviPlayerja3();
    void NastaviPlayerja4();
    void Okvir();
    void Skatle();
    void keyPressEvent(QKeyEvent *event);
    void end();
    void dodatek(int x,int y);
    void SuperP(int ax,int ay,Player *p);
    int cas=0;
    bool Sudden();
    QTimer *time;      // ura za sudden death
    QTimer *time2;     // postavljanje kvadratkov za sudden death
    QTimer *remaker;
    QTimer *suddent;
    void DodajRazb(int x, int y);
    void Umor(int x, int y);
    void nastavi();
    QTimer *startt;  // freeze preden se game zacne
    int zacetek=3;
    bool igra=false;
    QGraphicsTextItem *zac;
private slots:
    void povecaj();
    void SuddenDeath();
    void gumb1click();
    void ig2click();
    void ig3click();
    void ig4click();
    void pomansaj();
    void izrisi();
    void zapri();
    void remake();
    void backclick();
    void readyRead();
};


#endif // GAME_H
