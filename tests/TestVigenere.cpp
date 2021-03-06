/*
 * TestCriptografia.cpp
 *
 *  Created on: 12/11/2011
 *      Author: tincho
 */

#include "TestVigenere.h"
#include "../src/Criptografia/Kasiski.h"


TestVigenere::TestVigenere() {
	// TODO Auto-generated constructor stub

}

int TestVigenere::testCifrado(){

	string clave = "ABCD";

	Vigenere* vigenere = new Vigenere(clave);

	string mensaje = "Estoy haciendo una prueba de vigenere a ver que tal se comporta, saludos!";

	string* criptograma = vigenere->cifrar(&mensaje);

	string* mensajeDescifrado = vigenere->descifrar(criptograma);

	int resultado = mensajeDescifrado->compare(mensaje);

	if (resultado != 0)
		cout << "testVigenere.testCifrado: FALLO" << endl;

	delete criptograma;
	delete mensajeDescifrado;
	delete vigenere;

	return resultado;
}

int TestVigenere::testEnBloques(){

	string clave = "HZDIOP";

	Vigenere* vigenere = new Vigenere(clave);

	string m1 = "mensaje1 ";
	string m2 = "mensaje2 ";
	string m3 = "mensaje3 ";
	string m4 = "mensaje4";

	string* criptograma = new string();
	string* temp;

	temp = vigenere->cifrar(&m1);
	criptograma->append(*temp);
	delete temp;

	temp = vigenere->cifrar(&m2);
	criptograma->append(*temp);
	delete temp;

	temp = vigenere->cifrar(&m3);
	criptograma->append(*temp);
	delete temp;

	temp = vigenere->cifrar(&m4);
	criptograma->append(*temp);
	delete temp;

	string mensaje;
	mensaje.append(m1);
	mensaje.append(m2);
	mensaje.append(m3);
	mensaje.append(m4);

	string* mensajeDescifrado = vigenere->descifrar(criptograma);


	int resultado = mensajeDescifrado->compare(mensaje);

	if (resultado != 0)
		cout << "testVigenere.testEnBloques: FALLO" << endl;

	delete criptograma;
	delete mensajeDescifrado;
	delete vigenere;

	return resultado;
}


int TestVigenere::testCifradoCadenaLarga(){

	string clave = "ABCD";
	ManejadorDeArchivo* archivo = new ManejadorDeArchivo("./temp/SalidaCripto(Clave ABCD).txt");

	Vigenere* vigenere = new Vigenere(clave,256);

	Constitucion constitucion;
	string mensaje = constitucion.getTexto();

//	cout << "Mensaje plano: "<< mensaje<<endl;
	string* criptograma = vigenere->cifrar(&mensaje);

	// Salida a archivo
	char* buf = new char[criptograma->size()+1];
	strcpy(buf,criptograma->c_str());
	archivo->escribir(buf,criptograma->size());
	delete[] buf;
	archivo->guardarBuffer();
	delete archivo;

//	cout <<"Encriptado: "<< *criptograma<<endl;
	string* mensajeDescifrado = vigenere->descifrar(criptograma);
//	cout <<"DESEncriptado: "<< * mensajeDescifrado<<endl;
	int resultado = mensajeDescifrado->compare(mensaje);

	if (resultado != 0)
		cout << "testVigenere.testCifradoCadenaLarga: FALLO" << endl;

	delete criptograma;
	delete mensajeDescifrado;
	delete vigenere;

	return resultado;
}

TestVigenere::~TestVigenere() {
	// TODO Auto-generated destructor stub
}

