/*
 * Entidad.h
 *
 *  Created on: 24/09/2011
 *      Author: lucas
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <string>
#include <locale>
#include "Serializable.h"
#include "Constantes.h"
#include "NombreDeEntidad.h"
#include "../ClasesAuxiliares/ResultadoComparacion.h"

using std::string;
using std::stringstream;
using std::istringstream;

class Entidad: public Serializable {

public:

	virtual int getTamanio() = 0;

	virtual unsigned long getClave() = 0;

	virtual void verEntidad() = 0;

	/*
	 * Instancia un nuevo objeto, copia de actual.
	 */
	virtual Entidad* duplicar() = 0;


	/*
	 * Devuelve el resultado de comparar la actual entidad con otra.
	 * Los resultados posibles son mayor, menor, igual o comparacionInvalida.
	 * El resultado es respecto del patrón.
	 * Por ejemplo: sean A y B dos entidades, entonces
	 * A->comparar(B) devuelve "mayor" si A es mayor a "B".
	 */
	virtual ResultadoComparacion comparar(Entidad* entidad) = 0;

	/*
	 * Devuelve el tipo de la entidad instanciada.
	 */
	virtual NombreDeEntidad getNombreDeEntidad() = 0;

	virtual ~Entidad(){};
};

#endif /* ENTIDAD_H_ */
