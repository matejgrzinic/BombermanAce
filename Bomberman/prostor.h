#ifndef PROSTOR_H
#define PROSTOR_H

#include <razbitina.h>
#include <dodatek.h>

class Prostor
{
public:
    bool zapoljenost=false;
    bool zid=false;
    bool add=false;
    bool bomba=false;
    Razbitina *povezava=NULL;
    Dodatek *link=NULL;
};


#endif // PROSTOR_H
