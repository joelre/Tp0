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

bignum::bignum(size_t tamagno){
    digits = new unsigned short[tamagno];
    tam= tamagno;
    for(size_t i=0;i<tam;i++)
        digits[i]=0;
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
            cout<<"tamagno: "<<tam<<endl;
            break;
        }
        digits[i]=num;
        cout<<"lectura: "<<digits[i]<<endl;

        if(i==0)
            signo= lectura.obtenersigno();
    }

}

bignum::~bignum(){
    if(digits)
        delete[] digits;
}

//Reservo tres posiciones más de memoria dinamica respecto al
//tamaño más grande de arreglos entre ambas entradas bignum.
//

bignum operator+(const bignum& n1, const bignum& n2){
    bignum *n;
    int mayor,menor,i;

    if(n1.tam > n2.tam){
        mayor=n1.tam-1;
        menor=n2.tam-1;
        n = new bignum(3+mayor);
    }else{
        mayor=n2.tam-1;
        menor=n1.tam-1;
        n= new bignum(3+mayor);
    }

    for(i=n->tam-1;i>=0 && mayor>=0;i--){
        unsigned short aux;
        
        if(menor>=0){
            aux= n1.digits[mayor--] + n2.digits[menor--];
        }else{
            aux= n1.digits[mayor--];
        }
        
        if(aux>9){
            n->digits[i]= aux%10;
            n->digits[i-1]= aux/10;
        }else{
            n->digits[i]+=aux;
        }
        cout<<"suma: "<<n->digits[i]<<endl;
    }

    n->signo=true;
    return *n;
}

bool bignum::obtenersigno(){
    return signo;
}