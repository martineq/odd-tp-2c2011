/*
 * Serializable.h
 *
 *  Created on: 17/09/2011
 *      Author: lucas
 */

#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <string>
#include <sstream>
#include <fstream>
#include "../ClasesAuxiliares/Serializadora.h"

class Serializable {
public:
	virtual std::string* serializar() = 0;

	virtual void deserializar(std::string* source) = 0;

	virtual ~Serializable(){};

};

#endif /* SERIALIZABLE_H_ */
