#ifndef ELECCIONANTERIOR_H_
#define ELECCIONANTERIOR_H_

#include <iterator>
#include <string>
#include "Constantes.h"

using namespace std;

class EleccionAnterior{
private:
	string fecha;
	string cargo;
public:
	EleccionAnterior(string fecha, string cargo);
	EleccionAnterior();
	int getTamanio();
	string getFecha ();
	string getCargo ();
	EleccionAnterior* duplicar();
	virtual ~EleccionAnterior();
};

#endif /* ELECCIONANTERIOR_H_ */
