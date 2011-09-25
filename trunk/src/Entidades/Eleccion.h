/*
 * Eleccion.h
 *
 *  Created on: 17/09/2011
 *      Author: martin
 */

#ifndef ELECCION_H_
#define ELECCION_H_
#include <list>
#include <string>
#include <iostream>
#include "Distrito.h"
#include "Entidad.h"
#include "Cargo.h"
#include <iostream>



class Eleccion : public Entidad {

private:
	string			fecha;				// identificador
	string			cargoPrincipal;		// identificador
	list<Distrito>	distritos;

public:
	Eleccion();

	Eleccion(string fecha,string cargoPrincipal);

	int getTamanio();

	string getFecha();

	void setFecha(string fecha);

	string getCargo();

	void setCargo(string cargoPrincipal);

	bool agregarDistrito(Distrito distrito);

	bool eliminarDistrito(Distrito distrito);

	list<Distrito>::iterator obtenerIterador();

	list<Distrito> getLista();

	~Eleccion();

	string* serializar();

	void deserializar(string*);

};

#endif /* ELECCION_H_ */