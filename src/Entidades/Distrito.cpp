#include "Distrito.h"


using std::string;
using std::stringstream;
using std::istringstream;
using std::locale;
using std::collate;
using std::use_facet;
//using namespace std;

Distrito::Distrito(){
	this->distrito = "";
}


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

	if ( distrito.size() != 0 ){
		int sizeOfDistrito = this->distrito.size();
		streamDatos.write((char*)&sizeOfDistrito,TAM_INT);
		streamDatos.write((char*)distrito.c_str(),sizeOfDistrito);
	}
	return new string(streamDatos.str());
}

void Distrito::deserializar(string * source){

	if (source->size() != 0){
		istringstream streamDatos(*source);
		stringstream * miString = new stringstream();
		int sizeOfDistrito;
		streamDatos.read((char*)&sizeOfDistrito,TAM_INT);
		char* distritoChar = new char[sizeOfDistrito];
		streamDatos.read((char*)distritoChar,sizeOfDistrito);
		miString->write(distritoChar,sizeOfDistrito);
		string distritoString = miString->str();
		this->distrito = distritoString;

		delete []distritoChar;
		delete miString;
	}

}


int Distrito::getTamanio(){
	int tamanio = 0;
	if ( this->distrito.size() != 0){
		tamanio = TAM_INT + this->getDistrito().size();
	}
	return tamanio;
}

unsigned long Distrito::getClave(){

//	int c = 0;
//	int size = this->distrito.length();
//	for (int i=0; i< size; i++) {
//		c += (int)this->distrito[i];
//	}
//	return c;
//	locale loc;                 //
//	const collate<char>& coll = use_facet<collate<char> >(loc);
//	unsigned long strHash = coll.hash(this->distrito.data(),this->distrito.data()+this->distrito.length());

	  locale loc;                 // the "C" locale

	  const collate<char>& coll = use_facet<collate<char> >(loc);

	  unsigned long myhash = coll.hash(this->distrito.data(),this->distrito.data()+this->distrito.length());

	  return myhash;
}

ResultadoComparacion Distrito::comparar(Entidad *entidad)
{
	ResultadoComparacion resultado = comparacionInvalida;

	if ( tDistrito == entidad->getNombreDeEntidad() ){

		int r = distrito.compare(((Distrito*)entidad)->distrito);

		resultado = mayor;

		if ( r == 0 )
			resultado = igual;

		else if ( r < 0 )
			resultado = menor;
	}
	return resultado;
}

Distrito::~Distrito(){}

void Distrito::verEntidad(){
	cout << "Distrito: " << distrito << endl;
}

Entidad* Distrito::duplicar(){
	return new Distrito(this->distrito);
}

Entidad* Distrito::hidratar(string* source){
	Distrito* d = new Distrito();
	d->deserializar(source);
	return d;
}

