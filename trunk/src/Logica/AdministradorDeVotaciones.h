#ifndef ADMINISTRADORDEVOTACIONES_H_
#define ADMINISTRADORDEVOTACIONES_H_

#include <string>
#include "../Archivos/ArbolBMas/bplustree.h"
#include "../Entidades/Eleccion.h"
#include "../Entidades/Conteo.h"
#include "../Archivos/Hashing/Registro.h"
#include "../Archivos/Hashing/HashingExtensible.h"

using std::string;

class AdministradorDeVotaciones {
private:
	bplustree			archivoDeConteo;

	bplustree			indiceSecundario;

	/*
	 * Devuelve un string a partir de un string.
	 */
	string* getString(vector<char> vect);


	/*
	 * Agrega elementos conteo al indice secundario.
	 */
	int agregarConteoAlIndicePorDistrito(Conteo* conteo);

	/*
	 * Obtiene la clave del ínfice pricipal.
	 */
	string obtenerClavePrincipal(Conteo* conteo);

	/*
	 * Obtiene la clave del índice secundario.
	 */
	string obtenerClaveSecundaria(Conteo* conteo);


public:
	AdministradorDeVotaciones();

	/*
	 * Crea un nuevo archivo de conteo.
	 */
	void nuevoArchivoDeConteo(string pathArchivo,string pathArchivoSecundario,int dimensionBloque);

	/*
	 * Abre un archivo de conteo.
	 */
	void abrirArchivoDeConteo(string pathArchivo,string pathArchivoSecundario,int dimensionBloque);

	/*
	 * Devuelve 0 si lo agregó correctamente.
	 */
	int agregarConteo(Conteo* conteo);

	/*
	 * Devuelve 0 si se persistió el voto y 1 en caso contrario.
	 */
	void incrementarVoto(Eleccion* eleccion,string* nombreLista,string* distrito);

	/*
	 * Genera un informe mostrando el resultado de resultados de
	 * cada lista de esa eleccion.
	 */

	void generarInformePorEleccion(Eleccion* eleccion);

	/*
	 * Genera un informe mostrando los cargos y el resultado
	 * de una lista particular.
	 */
	void generarInformePorLista(Lista* lista,HashingExtensible* heCargo);

	/*
	 * Genera un informe mostrando el resultado del ganador
	 * de una eleccion.
	 */
	void generarInformePorDistrito(Distrito* distrio);
	/*
	 * Ver Archivo de conteo.
	 */
	void mostrarArchivoPrincipal();

	/*
	 * Ver el archivo secundario.
	 */
	void mostrarArchivoSecundario();

	~AdministradorDeVotaciones();

};

#endif /* ADMINISTRADORDEVOTACIONES_H_ */
