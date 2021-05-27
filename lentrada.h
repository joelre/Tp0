#ifndef _LENTRADA_
#define _LENTRADA_

#include <string>
#include <iostream>


class lentrada{
private:
    std::istream *entrada;
    std::string linea;
    size_t pos;
    bool signo;
    bool multiplicacion;

    lentrada();
public:
    lentrada(std::istream *);
    ~lentrada();
    void obtenerdigito(unsigned short &,bool &);
    bool operacionmultiplicar();
    bool obtenersigno();    
};

#endif
