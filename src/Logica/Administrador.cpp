/*
 * Administrador.cpp
 *
 *  Created on: 17/09/2011
 *      Author: mart
 */

#include "Administrador.h"


Administrador::Administrador(string pathArchivo) {
	archivo = new fstream(pathArchivo.c_str());

	char cadena[LONGITUD_BLOQUE];
	archivo->getline(cadena,LONGITUD_BLOQUE);

	string str(cadena);

	int espacio  = str.find(" ");
	nombre   = str.substr(0,espacio);
	espacio++;
	password = str.substr(espacio);

	cout << nombre;
	cout << password;

	archivo->close();
}

bool Administrador::acceder(string nomb,string pass){
	if (((this->nombre.compare(nomb))==0) && ((this->password.compare(pass))==0)) return true;
	else return false;
}

string* Administrador::getString(vector<char> vect){
	string* s = new string();
	vector<char>::iterator it = vect.begin();
	while( it != vect.end() ){
		s->push_back(*it);
		it++;
	}
	return s;
}

Resultados Administrador::altaHash (HashingExtensible* he,Registro* unRegistro){
	return he->agregarRegistro(unRegistro);
}

int Administrador::altaArbol (bplustree* arbolB,Registro* registro){
	string* registroSerializado = registro->serializar();
	vector<char> data(registroSerializado->begin(),registroSerializado->end());
	int claveInt = registro->obtenerClave();
	stringstream claveIntAString;//create a stringstream
	claveIntAString << claveInt;//add number to the stream
	string claveString = claveIntAString.str();
	return  arbolB->add(claveString,data);
}

bool Administrador::habilitarEleccion(Eleccion* unaEleccion){
	if (this->verificarEleccion(unaEleccion)) {
		list<Eleccion*>::iterator it = this->listaDeEleccionesHabilitadas.begin();
		int size = listaDeEleccionesHabilitadas.size();
		for (int i=0; i < size; i++){
			Eleccion* eleccion = new Eleccion ((*it)->getFecha(),(*it)->getCargo());
			if ((unaEleccion->getCargo()==eleccion->getCargo()) && (unaEleccion->getFecha()==eleccion->getFecha())) {
				cout << "LA ELECCION YA ESTA HABILITADA" << endl;
				delete eleccion;
				delete unaEleccion;
				return false;
			}
			delete eleccion;
			it++;
		}
		Eleccion* eleccion = (Eleccion*) unaEleccion->duplicar();
		this->listaDeEleccionesHabilitadas.push_back(eleccion);
		delete unaEleccion;
		return true;
	}
	else cout << "NO EXISTE ELECCION. CREE LA ELECCION PRIMERO" << endl;
	delete unaEleccion;
	return false;

}

void Administrador::getEleccionesHabilitadas(){
	cout << endl;
	cout << endl;
	if (this->listaDeEleccionesHabilitadas.size()==0) cout << "No hay elecciones habilitadas" << endl;
	else{
		list<Eleccion*>::iterator it=this->listaDeEleccionesHabilitadas.begin();
		int i=1;
		while (it!=this->listaDeEleccionesHabilitadas.end()){
			Eleccion* eleccion = *it;
			cout << "Eleccion " << i << endl;
			cout << "Fecha: " << eleccion->getFecha() << endl;
			cout << "Cargo Principal: " << eleccion->getCargo() << endl;
			cout << "------------------------------------------" << endl;
			it++; i++;
		}
	}
	cout << endl;
	cout << endl;
}

list <Eleccion*> Administrador::getListaDeEleccionesHabilitadas(){
	return this->listaDeEleccionesHabilitadas;
}

list <Lista*> Administrador::getListaDeBoletas(){
	return this->listaDeBoletas;
}

void Administrador::mostrarEleccionesDelVotante(list<Eleccion*>listaDeEleccionesDelVotante){
	if (listaDeEleccionesDelVotante.size()==0) {
		cout << "USTED NO TIENE ELECCIONES HABILITADAS" << endl;
		cout << "Si piensa que este mensaje es un error comuniquese con el administrador" << endl;
	}
	else {
		list<Eleccion*>::iterator it = listaDeEleccionesDelVotante.begin();
		cout << "Las elecciones activas en las que usted emitir su voto son las siguientes" << endl;
		int i=1;
		while (it!=listaDeEleccionesDelVotante.end()){
			cout << "Eleccion " << i << ":" << endl;
			cout << "Fecha: " << (*it)->getFecha() << endl;
			cout << "Cargo Principal: " << (*it)->getCargo() << endl;
			cout << "---------------" << endl;
			it++; i++;
		}
	}
}

void Administrador::consultarEleccionesHabilitadasParaElVotante(Votante* votante){
	list<Eleccion*> listaDeEleccionesDelVotante;
	list<Eleccion*>::iterator it = this->listaDeEleccionesHabilitadas.begin();
	if (this->listaDeEleccionesHabilitadas.size()==0) cout << "El administrador no ha habilitado ninguna eleccion aun" << endl;
	while (it!=this->listaDeEleccionesHabilitadas.end()){
		list<Distrito> listaDeDistritos = (*it)->getLista();
		list<Distrito>::iterator itDistritos = listaDeDistritos.begin();
		bool fin=false;
		while ((itDistritos!=listaDeDistritos.end()) && (!fin)){
			if (votante->getDistrito()==itDistritos->getDistrito()){
				listaDeEleccionesDelVotante.push_back(*it);
				fin=true;
			}
			else itDistritos++;
		}
		it++;
	}
	this->mostrarEleccionesDelVotante(listaDeEleccionesDelVotante);
}

int Administrador::elegirBoleta(int numeroDeEleccion, Bucket* bucketLista){
	cout << endl;
	cout << "Estas son sus boletas a elegir" << endl;
	int j=1;
	list <Lista*>::iterator itListas = this->listaDeBoletas.begin();
	while (itListas!=this->listaDeBoletas.end()) {
		cout << "Lista " << j << endl; j++;
		cout << "Nombre: " << (*itListas)->getNombre() << endl;
		itListas++;
	}
	cout << "Opcion " << j << endl; j++;
	cout << "Voto En Blanco" << endl;
	cout << "Opcion " << j << endl; j++;
	cout << "Voto Nulo, Impugnado, etc " << endl;
	cout << endl;
	bool ok=false;
	int c;
	while (!ok) {
		cout << "Elija su boleta en base al numero de opcion indicado" << endl;
		cin >> c;
		if ((((c)<=(((int)(this->listaDeBoletas.size()))+2)))&&(c>0)) ok=true;
		else cout << "Numero de boleta invalido" << endl;
	}
	return c;
}

void Administrador::cargarListasDeEleccion(Eleccion* eleccion, bplustree* arbol){

	// Busco la clave en arbol B+
	string clave;
	clave  = eleccion->getFecha();
	clave += eleccion->getCargo();

	arbol->search(clave);

	// Obtengo el contenido.
	pair<vector<char>,std::string> registroVectorizado = arbol->getnext();

	string* registroSerializado = getString(registroVectorizado.first);

	Registro* registro = new Registro();
	registro->deserializar(registroSerializado);
	delete registroSerializado;

	Lista* boletaDelArbol = (Lista*)registro->getContenido();
	while (boletaDelArbol->getFecha() == eleccion->getFecha()){

		if (boletaDelArbol->getCargo() == eleccion->getCargo()){
			Lista* lista = (Lista*)boletaDelArbol->duplicar();
			this->listaDeBoletas.push_back(lista);
			cout << "Encontre a Marina corriendo desnuda en la playa." << endl;
		}

		delete registro;
		registroVectorizado = arbol->getnext();
		registroSerializado = getString(registroVectorizado.first);

		registro = new Registro();
		registro->deserializar(registroSerializado);
		delete registroSerializado;

		delete boletaDelArbol;
		boletaDelArbol = (Lista*)registro->getContenido();
	}
	delete registro;
	cout << "acabe sobre marina" << endl;
	delete boletaDelArbol;

}

char Administrador::sufragar (int numeroDeBoleta){
	char c;
	int size;
	list <Lista*>::iterator itListas = this->listaDeBoletas.begin();
	size = listaDeBoletas.size();
	if (numeroDeBoleta==size+1) {
		cout << "La opcion elegida es: VOTO EN BLANCO" << endl;
		cout << "Si esta seguro presione s si desea corregir su voto presione n" << endl;
		cin >> c;
		if (c=='s') this->blancos++;
		return c;
	}
	if (numeroDeBoleta==size+2) {
		cout << "La opcion elegida es: VOTO NULO, IMPUGNADO, ETC" << endl;
		cout << "Si esta seguro presione s si desea corregir su voto presione n" << endl;
		cin >> c;
		if (c=='s') this->novalidos++;
		return c;
	}
//	me posiciono en la lista elegida de las opciones dadas
	for (int i=0; i< numeroDeBoleta-1;i++) itListas++;
	cout << "La opcion elegida es: " <<  numeroDeBoleta << endl;
	cout << "LISTA: " << (*itListas)->getNombre() << endl;
	cout << "Si esta seguro presione s si desea corregir su voto presione n" << endl;
	cin >> c;
	//if (c=='s') (*itListas)->incrementarVotos();
	return c;
}

bool Administrador::verificarEleccion(Eleccion* unaEleccion) {
#warning "verificar que la eleccion exista en el archivo de elecciones"
	return true;
}

Administrador::~Administrador() {
	list<Eleccion*>::iterator it = listaDeEleccionesHabilitadas.begin();
	while (it!=this->listaDeEleccionesHabilitadas.end()) {
		delete *it;
		it++;
	}
	list<Lista*>::iterator it2 = this->listaDeBoletas.begin();
	while (it2!=this->listaDeBoletas.end()) {
		delete *it2;
		it2++;
	}
//	delete archivo;
}