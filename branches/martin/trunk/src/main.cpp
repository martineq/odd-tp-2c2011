#include <iostream>
#include <list>
#include "./tests/Pruebas.h"
#include "./tests/Test.h"
#include "./tests/TestArchivoBloques.h"
#include "./tests/TestArchivoDeBuckets.h"
#include "./tests/TestHashingExtensible.h"

using namespace std;

	/*
	 * Para probar en el main crear el código correspondiente
	 * en una función nueva dentro de la clase "Pruebas", para
	 * luego invocarlo con "prueba.<nombreDeLaPrueba>()".
	 */
int main(int argc,char* argv[]) {

//	Pruebas* prueba = new Pruebas();

//	Pruebas de Bucket!
//	prueba->pruebaAgregarRegistrosAlBucket();
//	prueba->pruebaEliminarRegistrosDelBucket();
//	prueba->pruebaReemplazarRegistroEnBucket();
//	prueba->serializarDeserializarBucket();

//  Pruebas de serializar y deserializar entidades!
//	prueba->serializarDeserializarVotante();
//	prueba->serializarDeserializarDistrito();
//	prueba->serializarDeserializarCargo();
//	prueba->serializarDeserializarCandidato();
//	prueba->serializarDeserializarLista();
//	prueba->serializarDeserializarEleccion();

//	Pruebas para el Archivo en Bloques:
//	prueba->pruebaArchivoBloques();

//	Pruebas de integracion
//	prueba->pruebaDeSimulacionDePrograma();

//  Prueba que funciona el eclipse!
//	prueba->holaMundo();

//	delete (prueba);

//	Test test;
//	test.testStringstream();
//	test.testConvertir();
//	test.testArchivoDeBuckets();
//	test.serializarDeserializarRegistro();
//	test.testBucket();

//	Pruebas Archivo de Bloques
//	TestArchivoBloques ab;
//	ab.testObtenerBloque();

//	Pruebas Archivo de Buckets
//	TestArchivoDeBuckets testArchivoDeBuckets;
//	testArchivoDeBuckets.testLecturaEscrituraDeBuckets();
//	testArchivoDeBuckets.testAltaBajaDeBucketsEnArchivoDeBuckets();

//	Pruebas de Hashing!
	TestHashingExtensible the;
	the.testAgregarRegistros();
//	the.testObtenerRegistro();
//	the.testEliminarRegistro();
//	the.testEliminarRegistrosReduciendoTablaDehash();
//	the.testEliminarRegistrosYBucketSinReducirTabladeHash();
//	the.testModificarRegistroInexistente();
//	the.testModificarRegistroExistente();
//	the.testModificarRegistroConRedispersion();


	cout << "\n\n** EXITO! **" << endl;
	return 0;
}

