#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include <bignum.h>

using namespace std;

bignum::bignum(){
}

bignum::bignum(istream *entrada){
    string l1;
    *entrada>>l1;
    cout<<l1<<endl;
}

bignum::~bignum(){
}
