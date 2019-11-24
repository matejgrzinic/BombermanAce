#include <scena.h>
#include <game.h>

extern Game *game;

void Scena::keyReleaseEvent(QKeyEvent *event)
{
    int premik=48;
        int ax,ay;
        ax=pos().x()/48;
        ay=pos().y()/48;
        if (event->key() == Qt::Key_Left)
        {

                if (!game->zasedenost[ax-1][ay].zapoljenost)
                {
                     //game->scene->setFocusItem(game->player);
                     setPos(x()-premik,y());
                }

        }
}
