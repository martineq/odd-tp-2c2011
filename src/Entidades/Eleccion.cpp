/*
 * Eleccion.cpp
 *
 *  Created on: 17/09/2011
 *      Author: martin
 */

#include "Eleccion.h"
using namespace std;

Eleccion::Eleccion() {
	this->fecha = "";
	this->cargoPrincipal = "";

}

void Eleccion::verEntidad(){
	cout << "Fecha: " << fecha << endl;
	cout << "Cargo Principal: " << cargoPrincipal << endl;
	list<Distrito>::iterator it = this->distritos.begin();
	while (it != this->distritos.end()){
		cout << "Distrito: " << (*it).getDistrito() << endl;
		it++;
	}
}

Eleccion::Eleccion(string fecha,string cargoPrincipal){
	this->fecha 		= fecha;
	this->cargoPrincipal= cargoPrincipal;
}

int Eleccion::getTamanio(){
	int tamanioFecha = TAM_FECHA; //por default es 8
	int tamanioCargoPrincipal = TAM_INT + this->cargoPrincipal.size();
	int tamanioListaDistritos = TAM_INT; // este tam_int es la cantidad de distritos
	list<Distrito>::iterator it = this->distritos.begin();
	while (it != this->distritos.end()){
		tamanioListaDistritos += (TAM_INT +  it->getTamanio());
		it++;
	}
	return (tamanioFecha + tamanioCargoPrincipal + tamanioListaDistritos);
}

unsigned long Eleccion::getClave(){
//	int c = 0;
//	int size = fecha.length();
//	for (int i=0; i<size; i++) {
//		c += (int)this->fecha[i];
//	}
//	size = cargoPrincipal.length();
//	for (int i=0; i<size; i++) {
//		c += (int)this->cargoPrincipal[i];
//	}
//	return c;
	  string stringClave = this->fecha + this->cargoPrincipal;
	  locale loc;                 // the "C" locale

	  const collate<char>& coll = use_facet<collate<char> >(loc);

	  unsigned long myhash = coll.hash(stringClave.data(),stringClave.data()+stringClave.length());

	  return myhash;


}

string Eleccion::getFecha(){
	return this->fecha;
}

void Eleccion::setFecha(string fecha){
	this->fecha = fecha;
}

string Eleccion::getCargo(){
	return this->cargoPrincipal;
}

void Eleccion::setCargo(string cargoPrincipal){
	this->cargoPrincipal = cargoPrincipal;
}

bool Eleccion::agregarDistrito(string nombre){
	Distrito unDistrito (nombre);
	list<Distrito>::iterator iterador = this->distritos.begin();
	while (iterador != this->distritos.end()){
		if ((iterador->getDistrito()).compare(unDistrito.getDistrito()) == 0){
			cout << "El distrito ya esta habilitado en esta eleccion" << endl;
			return false;
		}
		iterador++;
	}
	this->distritos.push_back(unDistrito);
	return true;
}

bool Eleccion::eliminarDistrito(Distrito distrito){
	bool encontrado = false;
	list<Distrito>::iterator iterador = this->distritos.begin();
	while( iterador != this->distritos.end() and !encontrado ){
		if( (iterador->getDistrito().compare(distrito.getDistrito()))==0){
			encontrado = true;
			this->distritos.erase(iterador);
		}
		iterador++;
	}
	return (!encontrado); //devuelve el resultado de la inserción
}

list<Distrito> Eleccion::getLista(){
	return this->distritos;
}

list<Distrito>::iterator Eleccion::obtenerIterador(){
	list<Distrito>::iterator iterador = this->distritos.begin();
	return iterador;
}

int Eleccion::ultimo(list<Distrito>::iterator it){
	if (it == distritos.end())
		return 1;
	else
		return 0;
}


Entidad *Eleccion::duplicar(){
	Eleccion* copia = new Eleccion();
	copia->cargoPrincipal = this->cargoPrincipal;
	copia->fecha = this->fecha;
	list<Distrito>::iterator it = this->distritos.begin();
	while (it != this->distritos.end()){
		copia->agregarDistrito(it->getDistrito());
		it++;
	}
	return copia;

}

Eleccion::~Eleccion() {
	// TODO Auto-generated destructor stub
}

string* Eleccion::serializar() {
	stringstream buffer;
	int cantidadDeBytes;
	cantidadDeBytes   = this->fecha.size();
//	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->fecha.c_str(),cantidadDeBytes);
	cantidadDeBytes   = this->cargoPrincipal.size();
	buffer.write((char*)&cantidadDeBytes,TAM_INT);
	buffer.write((char*)this->cargoPrincipal.c_str(),cantidadDeBytes);
	int tamanioDeListaDeDistritos = this->distritos.size();
	buffer.write((char*)&tamanioDeListaDeDistritos,TAM_INT);
	list<Distrito>::iterator it = this->distritos.begin();
	for (int i=0; i<tamanioDeListaDeDistritos; i++) {
		cantidadDeBytes = ((*it).getDistrito()).size();
		buffer.write((char*)&cantidadDeBytes,TAM_INT);
		buffer.write((char*)((*it).getDistrito()).c_str(),cantidadDeBytes);
		it++;
	}
	string* datos = new string(buffer.str());
	return datos;
}

void Eleccion::deserializar(string* source) {
	istringstream buffer (*source);
	stringstream* miString;
	int cantidadDeBytes;

//	hidrato la fecha
//    buffer.read((char*)&cantidadDeBytes,TAM_INT);
	cantidadDeBytes = TAM_FECHA;
    char* fechaSerializada = new char[cantidadDeBytes];
    buffer.read((char*)fechaSerializada,cantidadDeBytes);

	miString = new stringstream();
	miString->write(fechaSerializada,TAM_FECHA);
    string* pasoAString = new string (miString->str());
    this->fecha = *pasoAString;
    delete []fechaSerializada;
    delete pasoAString;
    delete miString;

//  hidrato el cargo principal
    buffer.read((char*)&cantidadDeBytes,TAM_INT);
    char* cargoPrincipalSerializado = new char[cantidadDeBytes];
    buffer.read((char*)cargoPrincipalSerializado,cantidadDeBytes);
	miString = new stringstream();
	miString->write(cargoPrincipalSerializado,cantidadDeBytes);
    pasoAString = new string (miString->str());
    this->cargoPrincipal = *pasoAString;
    delete []cargoPrincipalSerializado;
    delete pasoAString;
    delete miString;

//  hidrato la lista de distritos
    int tamanioDeLaLista;
    buffer.read((char*)&tamanioDeLaLista,TAM_INT);
    for (int i=0; i<tamanioDeLaLista;i++){
    	stringstream* bufferAuxiliar = new stringstream;
    	buffer.read((char*)&cantidadDeBytes,TAM_INT);
    	char* distritoSerializado = new char[cantidadDeBytes];
    	buffer.read(distritoSerializado,cantidadDeBytes);
    	bufferAuxiliar->write(distritoSerializado,cantidadDeBytes);
    	Distrito unDistrito(bufferAuxiliar->str());
    	this->distritos.push_back(unDistrito);
    	delete bufferAuxiliar;
    	delete []distritoSerializado;
    }
}

NombreDeEntidad Eleccion::getNombreDeEntidad(){
	return tEleccion;
}

ResultadoComparacion Eleccion::comparar(Entidad* entidad){
	if (entidad->getNombreDeEntidad() != tEleccion){
		return comparacionInvalida;
	}

	Eleccion* eleccionNueva = (Eleccion*) entidad;
	int compararFecha = this->fecha.compare(eleccionNueva->fecha);
	int compararCargo = this->cargoPrincipal.compare(eleccionNueva->cargoPrincipal);

	if (compararFecha < 0){
		return menor;
	}
	if (compararFecha > 0){
		return mayor;
	}

	return (ResultadoComparacion)compararCargo;

}


