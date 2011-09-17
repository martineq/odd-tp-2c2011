/*
 * Candidato.h
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#ifndef CANDIDATO_H_
#define CANDIDATO_H_
//Candidato ( ( (lista)ie, (votante)ie, (cargo)ie)i )
//Candidato ( (fecha),(cargo),(nombre),(dni), (cargo) )

#include <string>
using namespace std;

class Candidato {

private:
	string fecha;		//Identificador
	string cargo;		//Identificador
	string nombre;		//Identificador
	int dni;			//Identificador

public:
	Candidato();
	Candidato( string fecha, string cargo, string nombre, int dni);
	virtual ~Candidato();

};

#endif /* CANDIDATO_H_ */
