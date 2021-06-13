#include <lentrada.h>
#include <ctype.h>
#include <string.h>

using namespace std;


lentrada::lentrada(){
}

lentrada::lentrada(istream *entrante){
    entrada = entrante;

    getline(*entrada,linea); 
    pos=0;
    multiplicacion=false;
    signoleido=false;
    signo=true;
}


lentrada::~lentrada(){
}


void lentrada::obtenerdigito(unsigned short &num,bool &seguir){
    seguir=true;
    while(!isdigit(linea[pos])){
        if(!linea[pos]){
            linea.clear();
            getline(*entrada,linea);
            seguir=false;
            signo = true;
            pos=0;
            return;
        }

        if(linea[pos]=='*'){
            multiplicacion=true;
            seguir=false;
            signo=true;
            signoleido=false;
            pos++;
            return;
        }

        if(signoleido){
            signo=true;
            signoleido=false;
            seguir=false;
            return;
        }

        while(!signoleido){
            if(linea[pos]=='-'){
                signo=false;
                pos++;
            }else if(linea[pos]=='+'){
                signo=true;
                pos++;
            }

            if(linea[pos]==' '){
                pos++;
                continue;
            }

            signoleido=true;
        }

    }

    if(pos==0 && !signoleido){
        signo=true;
        signoleido=true;
    }

    num=(linea[pos++]-'0');
}

bool lentrada::obtenersigno(){
    return signo;
}
