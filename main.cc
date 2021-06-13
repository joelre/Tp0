// Prueba de la clase cmdline: dado un factor entero pasado por la
// l�nea de comando, leemos una secuencia de n�meros que ingresan
// por la entrada est�ndar, los multiplicamos por ese factor, y
// luego mostramos el resultado por std::cout.
//
// $Id: main.cc,v 1.5 2012/09/15 12:23:57 lesanti Exp $

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include <cmdline.h>
#include <bignum.h>
#include <lentrada.h>


#include <string>



using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_presicion(string const &);
static void opt_help(string const &);

// Tabla de opciones de l�nea de comando. El formato de la tabla
// consta de un elemento por cada opci�n a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opci�n lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opci�n.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opci�n en caso que no est� expl�citamente presente
//   en la l�nea de comandos del programa. Si la opci�n no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al m�todo de parseo de la opci�n,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La �ltima columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opci�n: cuando la
//   opci�n es obligatoria, deber� activarse OPT_MANDATORY.
//
// Adem�s, la �ltima entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "p", "presicion", "10", opt_presicion, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};
static int presicion;
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;

static void opt_input(string const &arg){
	// Si el nombre del archivos es "-", usaremos la entrada
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//

	if (arg == "-") {
		iss = &cin;
	} else {
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "No se logro abrir el archivo."<< arg<< "."<< endl;
		exit(1);
	}
}

static void opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "No se logro abrir el archivo."<< arg<< "."<< endl;
		exit(1);
	}
}


static void opt_presicion(string const &arg){

		istringstream iss(arg);

		// Intentamos extraer la presicion de la l�nea de comandos.
		// Para detectar argumentos que �nicamente consistan de 
		// n�meros enteros, vamos a verificar que EOF llegue justo
		// despu�s de la lectura exitosa del escalar y que el valor
		// introducido sea mayor a cero.
		//
		if (!(iss >> presicion) || !iss.eof() || presicion<=0){
			cerr<<"La presicion introducida es invalida: "<<arg<< "."<< endl;
			exit(1);
		}

		if (iss.bad()) {
			cerr << "No se lorgro leer la presicion."<< endl;
			exit(1);
		}
	
}

static void opt_help(string const &arg)
{
	cout << "bignum -p presicion [-i archivo] [-o archivo]"<< endl;
	exit(0);
}

int main(int argc, char * const argv[]){

	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	lentrada lectura(iss);
	bignum n1(lectura,presicion);
	bignum n2(lectura,presicion);

	bignum n= n1-n2;

	if(n1.obtenersigno()){
		cout<<"n1 es positivo"<<endl;
	}else{
		cout<<"n1 es negativo"<<endl;
	}

	if(n2.obtenersigno()){
		cout<<"n2 es positivo"<<endl;
	}else{
		cout<<"n2 es negativo"<<endl;
	}

	//bignum n2(lectura,presicion);



/*
	for(int i=0;i<presicion;i++){
		unsigned short num = lectura.obtenerdigito();
		cout<<num<<endl;
	}
	

	bool flag=true;
	while(flag){
		lentrada lectura(iss);
	}


	while(getline(*iss,linea)){
		short num=stoi();

		cout<<"entre"<<endl;
		cout<<linea<<endl;
		linea.clear();
	}
*/


/*
	string l1;
	unsigned short num;
    *iss>>l1;
	size_t pos;

	num=stol(l1,&pos);

	cout<<"entrada: "<<l1<<endl;
    cout<<num<<endl;
	cout<<"posicion: "<<pos<<endl;
	cout<<l1[pos]<<endl;
*/


/*
	char num[10];

	*iss>>num;
	*oss<<num<<endl;
*/
	
/*

	string b="205072";
	unsigned short num;

	for(size_t i=0;i<2;i++){
		string a;
		b[i]= a[i];
		*a>>a;
	}
	string b="20";
	unsigned short num;
	*b>>num;
	cout<<num<<endl;


  3

 	4 0 6 0									86 			64
	 5 0			20,503,000				59 			89    		51,888,696
 	------									5074	   5696
 	00 00
  2 03 0-
	00 -

	int a=95;
	int b= a/10;
	int c= a%10;

	cout<<b<<endl;
	cout<<c<<endl;
*/
	
}
