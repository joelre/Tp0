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
            //cout<<"tamagno: "<<tam<<endl;
            break;
        }
        digits[i]=num;
        //cout<<"lectura: "<<digits[i]<<endl;

        if(i==0)
            signo= lectura.obtenersigno();
    }

}

bignum::~bignum(){
    if(tam!=0)
        delete[] digits;
}

bool bignum::obtenersigno(){
    return signo;
}

//Reservo tres posiciones más de memoria dinamica respecto al
//tamaño más grande de arreglos entre ambas entradas bignum.
//


bignum operator+(const bignum& n1, const bignum& n2){
    int mayor,menor,i;

    if(n1.tam > n2.tam){
        mayor=n1.tam-1;
        menor=n2.tam-1;
    }else{
        mayor=n2.tam-1;
        menor=n1.tam-1;
    }

    bignum n(3+mayor);

    for(i=n.tam-1;i>=0 && mayor>=0;i--){
        unsigned short aux;

        if(menor>=0){
            aux= n1.digits[mayor--] + n2.digits[menor--];
        }else{
            aux= n1.digits[mayor--];
        }
        
        if(aux>9){
            n.digits[i]= aux%10;
            n.digits[i-1]= aux/10;
        }else{
            n.digits[i]+=aux;
        }
    }

    if(n1.signo==true){
        n.signo=true;
    }else{
        n.signo = false;
    }

    return n;
}

bignum operator-(const bignum& n1, const bignum& n2){
    const bignum *mayor,*menor;    
    int tam_ma,tam_me,acumulador=0;

    if(n1.tam > n2.tam){
        mayor=&n1;
        menor=&n2;
    }else if(n1.tam < n2.tam){
        mayor=&n2;
        menor=&n1;
    }else{
        if(n1.digits[0] > n2.digits[0]){
            mayor=&n1;
            menor=&n2;
        }else{
            mayor=&n2;
            menor=&n1;
        }
    }

    tam_ma = mayor->tam-1;
    tam_me = menor->tam-1;

    bignum n(tam_ma+1);

    for(int i=tam_ma;i>=0 && tam_ma>=0;i--){
        unsigned short aux;

        if(tam_me>=0){
            if((mayor->digits[tam_ma]-acumulador)< menor->digits[tam_me]){
                if(mayor->digits[tam_ma]==0){
                    aux = 10;
                    n.digits[i]= aux- menor->digits[tam_me];
                }else{
                    aux= (mayor->digits[tam_ma]-acumulador) + 10;
                    n.digits[i]= aux- menor->digits[tam_me];
                }
                tam_ma--;
                tam_me--;
                acumulador=1;
            }else{
                n.digits[i] = (mayor->digits[tam_ma--]-acumulador) - menor->digits[tam_me--];
                acumulador=0;
            }
        }else{
            n.digits[i]= mayor->digits[tam_ma--]-acumulador;
            acumulador=0;
        }
    }

    n.signo= mayor->signo;

    return n;
}

bignum operator*(const bignum& n1, const bignum& n2){
    const bignum *mayor,*menor;    
    int tam_ma,tam_me,aux=0;

    if(n1.tam > n2.tam){
        mayor=&n1;
        menor=&n2;
    }else if(n1.tam < n2.tam){
        mayor=&n2;
        menor=&n1;
    }else{
        if(n1.digits[0] > n2.digits[0]){
            mayor=&n1;
            menor=&n2;
        }else{
            mayor=&n2;
            menor=&n1;
        }
    }

    tam_ma = mayor->tam-1;
    tam_me = menor->tam-1;

    bignum n(n1.tam+n2.tam);
    int n_tam;

    for(int i=tam_me;i>=0;i--){
        unsigned short num=0;
        n_tam=n1.tam+n2.tam-1;

        for(int j=tam_ma;j>=0;j--){
            num = mayor->digits[j]*menor->digits[i]+n.digits[n_tam-aux];
            if(num>9){
                n.digits[n_tam-aux]= num%10;
                n.digits[n_tam-aux-1]+= num/10;
            }else{
                n.digits[n_tam-aux]=num;
            }
            n_tam--;
        }
        aux++;
    }

    n.signo= mayor->signo;

    return n;
}

std::ostream& operator<<(std::ostream &os, const bignum &n){
    if(n.signo==false){
        os<<"-";
    }
    bool flag=true;
    for(size_t i=0;i<n.tam;i++){
        while(flag){
            if(n.digits[i]==0 && i<n.tam-1){
                i++;
            }else{
                flag=false;
            }
        }
        os<<n.digits[i];
    }
    return os;
}

std::istream& operator>>(std::istream &is, bignum &n){
    //lentrada lectura(is);
    //n(lectura);
    return is;
}