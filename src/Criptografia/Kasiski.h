
#ifndef KASISKI_H
#define	KASISKI_H

#include <string>
#include <vector>
#include <algorithm>
#include <utility>

class Kasiski {
public:
    Kasiski();
    Kasiski(const Kasiski& orig);
    virtual ~Kasiski();
    int getkeylen(std::string c);
    std::vector<std::vector<char> > ngram(std::string c, unsigned int keylen);
    std::vector<std::vector<std::pair<char,int> > > buildhisto(std::string c, unsigned int keylen);
    std::string getkey(std::string c);
private:
    static int compare(std::pair<char, int> l, std::pair<char, int> r);
};

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
/*
#include <string>
#include <list>
#include "Patron.h"

using std::string;
using std::list;

class Kasiski {
private:
	string textoCifrado;
	list<Patron> listaPatrones;
	list<int> listaDistancias;
	int maximaLongitudPatron;

	int MCDDistancias();
	int gcd(int a, int b);
	bool noExiste(Patron patron);
	void agregarPatron(Patron patron, int posicion);
	void listarPatrones();
public:
	Kasiski(string);
	string romper();
	virtual ~Kasiski();
};
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
*/

#endif /* KASISKI_H_ */
