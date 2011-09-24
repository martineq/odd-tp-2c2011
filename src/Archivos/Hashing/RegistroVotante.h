#ifndef REGISTROVOTANTE_H_
#define REGISTROVOTANTE_H_

#include "../Registro.h"
#include "../../Entidades/Votante.h"

using namespace std;

class RegistroVotante : public Registro {

public:

	RegistroVotante();

	int obtenerClave();

    Candidato* getContenido();


	string* serializar();
	void deserializar(string * source);


	virtual ~RegistroCandidato();
};

#endif /* REGISTROVOTANTE_H_ */
