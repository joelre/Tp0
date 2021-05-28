#ifndef _BIGNUM_
#define _BIGNUM_

#include <string>
#include <iostream>
#include <lentrada.h>

class bignum{
private:
    unsigned short *digits;
    size_t tam;
    bool signo;

    bignum();
    bignum(size_t);
    // ...
public:
    bignum(lentrada &,int);
    ~bignum();
    bool obtenersigno();
    friend bignum operator+(const bignum&, const bignum&);
    friend bignum operator-(const bignum&, const bignum&);
    friend bignum operator*(const bignum&, const bignum&);
    friend std::ostream& operator<<(std::ostream&, const bignum&);
    friend std::istream& operator>>(std::istream&, bignum&);
};

#endif