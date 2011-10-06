#include "Distrito.h"

using std::string;
using std::stringstream;
using std::istringstream;

Distrito::Distrito(){
	this->distrito = "";
};


Distrito::Distrito(string distrito){
		this->distrito = distrito;
	}

NombreDeEntidad Distrito::getNombreDeEntidad(){
	return tDistrito;
}

string Distrito::getDistrito(){
		return this->distrito;
	}


void Distrito::setDistrito(string distrito){
		this->distrito = distrito;
	}

string* Distrito::serializar(){
	stringstream streamDatos;
	int sizeOfDistrito = this->distrito.size();
	streamDatos.write((char*)&sizeOfDistrito,TAM_INT);
	streamDatos.write((char*)distrito.c_str(),sizeOfDistrito);
	string* datos = new string(streamDatos.str());
	return datos;
}

void Distrito::deserializar(string * source){
	cout << "Estamos deserializando un distrito" << endl;
	istringstream streamDatos(*source);

	stringstream * miString = new stringstream();
	int sizeOfDistrito;
	streamDatos.read((char*)&sizeOfDistrito,TAM_INT);
    char* distritoChar = new char[sizeOfDistrito];
    streamDatos.read((char*)distritoChar,sizeOfDistrito);
    miString->write(distritoChar,sizeOfDistrito);
    string distritoString = miString->str();
    this->distrito = distritoString;
    cout << "Ya cargamos el nombre del distrito" << endl;
    delete []distritoChar;
    delete miString;
    cout << "Terminamos de deserializar un distrito" << endl;
//    delete source; hay que hacer el delete este corregir
}


int Distrito::getTamanio(){
	return (TAM_INT + this->getDistrito().size());
}

int Distrito::getClave(){

	#warning "Hay que modificar la obtención de la clave";

	return this->distrito.size();
}

Distrito::~Distrito(){};

Entidad* Distrito::duplicar(){
	return new Distrito(this->distrito);
}

Entidad* Distrito::hidratar(string* source){
	Distrito* d = new Distrito();
	d->deserializar(source);
	return d;
}

