#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include <bignum.h>
#include <lentrada.h>

using namespace std;

bignum::bignum(){
}

bignum::bignum(lentrada &lectura,int presicion){
    digits = new unsigned short[presicion];
    tam= presicion;

    bool seguir=true;
    unsigned short num;

    for(int i=0;i<presicion;i++){
        lectura.obtenerdigito(num,seguir);
        if(!seguir){
            tam=i;
            break;
        }
        digits[i]=num;
        cout<<digits[i];

        if(i==0)
            signo= lectura.obtenersigno();
    }
    cout<<endl;

    /*
    string l1;
    *entrada>>l1;
    cout<<l1<<endl;
    */
}

bignum::~bignum(){
    if(digits)
        delete[] digits;
}

bool bignum::obtenersigno(){
    return signo;
}