#include <lentrada.h>
#include <ctype.h>
#include <string.h>

using namespace std;


lentrada::lentrada(){
}

lentrada::lentrada(istream *entrante){
    entrada = entrante;

    getline(*entrada,linea);

    if(!linea[0])
        cout<<"termino"<<endl;
  
    pos=0;
    multiplicacion=false;
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

        if(linea[pos]=='-'){
            signo=false;
            pos++;
            break;
        }else if(linea[pos]=='*'){
            multiplicacion=true;
            seguir=false;
            signo=true;
            pos++;
            return;
        }
        
        seguir=false;
        pos++;
    }
    num=(linea[pos++]-'0');
}

bool lentrada::obtenersigno(){
    return signo;
}
