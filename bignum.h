#ifndef _BIGNUM_
#define _BIGNUM_

#include <string>
#include <iostream>


class bignum{
private:
    unsigned short *digits;

    // ...
public:
    bignum();
    bignum(std::istream *);
    ~bignum();
    // ...
    friend bignum operator+(const bignum&, const bignum&);
    friend bignum operator-(const bignum&, const bignum&);
    friend bignum operator*(const bignum&, const bignum&);
    friend std::ostream& operator<<(std::ostream&, const bignum&);
    friend std::istream& operator>>(std::istream&, bignum&);
};

#endif