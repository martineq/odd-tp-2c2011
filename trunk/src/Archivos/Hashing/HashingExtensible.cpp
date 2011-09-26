#include "HashingExtensible.h"

int HashingExtensible::obtenerDispersion(int numeroDeBucket){
	Bucket* bucket = this->archivo->obtenerBucket(numeroDeBucket);

	#warning "ver manejo de errores";
	if (bucket == NULL)
		throw "Bucket inexistente";

	return bucket->getTamanioDeDispersion();
}

int HashingExtensible::numeroPosicionesAreemplazar(int numeroDeBucket){

	int dispersion = this->obtenerDispersion(numeroDeBucket);
	int repeticionesBloque = dispersion / this->tablaDeHash.size();
	return repeticionesBloque/2;

}

HashingExtensible::HashingExtensible(ArchivoDeBuckets* archivoBloques) {
	this->archivo = archivoBloques;
}

int HashingExtensible::obtenerPosicion(int clave){
	int posicion = 0;

	if (!this->tablaDeHash.empty()){
		int n = log(this->tablaDeHash.size())/log(2);
		posicion = clave & n;
	}

	return posicion;
}

void HashingExtensible::redispersarBucket(Bucket* bucket,int numeroDeBucket,int posicionEnTablaDeHash){
	vector<int>::iterator it;
	Bucket* nuevoBucket;
	Bucket* bucketActualizado;

	int nuevoNumeroDeBucket;
	int dispersionNuevoBucket;
	int dispersionBucketActualizado;

	// Se agrega un nuevo numeroDeBucket en la posicion actual
	nuevoNumeroDeBucket = this->tablaDeDispersion.size();

	// Determina cuantas posiciones en la tabla de Hash serán reemplazadas
	int posicionesAreemplazar = numeroPosicionesAreemplazar(numeroDeBucket);

	if ( posicionesAreemplazar == 0 ){

		// Se duplica la tabla
		it 	= this->tablaDeHash.end();
		this->tablaDeHash.insert(it,this->tablaDeHash.begin(),it);
		this->tablaDeHash[posicionEnTablaDeHash] = nuevoNumeroDeBucket;

		// Se calculan los nuevos tamaños de dispersion, del bucket a redispersar y del nuevo bucket.
		dispersionBucketActualizado = 2 * tablaDeDispersion[numeroDeBucket];
		dispersionNuevoBucket 		 = tablaDeDispersion[nuevoNumeroDeBucket];

	}else{
		// Se calculan los nuevos tamaños de dispersion, del bucket a redispersar y del nuevo bucket.
		dispersionBucketActualizado = 2 * tablaDeDispersion[numeroDeBucket];
		dispersionNuevoBucket 		 = dispersionBucketActualizado;

		// Actualiza la tabla de hash incoorporando el valor del nuevo bloque.
		while (posicionesAreemplazar > 0){
			posicionesAreemplazar--;
			this->tablaDeHash[posicionEnTablaDeHash+posicionesAreemplazar*dispersionNuevoBucket] = nuevoNumeroDeBucket;
		}
	}

	// Se actualiza la dispersion del bucket a redispersar.
	this->tablaDeDispersion[numeroDeBucket] = dispersionBucketActualizado;

	// Se agrega la dispersión del nuevo bloque
	this->tablaDeDispersion.push_back(dispersionNuevoBucket);

	// Se crea el nuevo Bucket.
	nuevoBucket = new Bucket(dispersionNuevoBucket);
	this->archivo->guardarBucket(nuevoBucket);

	// Se crea un nuevo Bucket para redispersar los elementos.
	bucketActualizado = new Bucket(dispersionBucketActualizado);
	this->archivo->guardarBucket(bucketActualizado);

	int cantidadDeRegistros = bucket->getCantidadDeRegistros();
	list<Registro*>::iterator iterador = bucket->ubicarPrimero();
	for(int i = 0;i< cantidadDeRegistros;i++){
		this->agregarRegistro(*iterador);
		iterador++;
	}

}

bool reducirTablaDeHash(){

}

void HashingExtensible::agregarRegistro(Registro* registro){

	int numeroDeBucket;
	Bucket* bucket;
	bool bucketCompleto;
	int posicionEnTablaDeHash;

	//Obtener clave devuelve el resultado de aplicar la función de hashing sobre el registro.
	int clave = registro->obtenerClave();

	// Se aplica la "función modulo" para obtener la posicion de la tabla aplicando el logaritmo en base 2 del tamaño de la tabla.
	posicionEnTablaDeHash = this->obtenerPosicion(clave);

	if ( !this->tablaDeHash.empty()) {
		// Busco el numero de bucket si la tabla no está vacía.
		numeroDeBucket = this->tablaDeHash.at(posicionEnTablaDeHash);
		bucket = this->archivo->obtenerBucket(numeroDeBucket);

	}else {
		// Si la tabla está vacía entonces tengo que crear un nuevo bucket
		numeroDeBucket = this->archivo->crearNuevoBucket();

		// Agrego el nuevo bucket en la lógica del hashing y le asigno su dispersión.
		this->tablaDeHash.push_back(numeroDeBucket);
		this->tablaDeDispersion.push_back(this->tablaDeHash.size());

		// Obtengo el nuevo bucket y le modifico el tamaño de dispersión.
		Bucket* bucket = this->archivo->obtenerBucket(numeroDeBucket);
		bucket->setTamanioDeDispersion(tablaDeDispersion.at(numeroDeBucket));
	}

	bucketCompleto = bucket->agregarRegistro(registro);

	if (!bucketCompleto){
		this->archivo->guardarBucket(bucket);

	}else{
		redispersarBucket(bucket,numeroDeBucket,posicionEnTablaDeHash);

		// Reintento agregar el registro que generó la redispersion
		this->agregarRegistro(registro);
	}
}

void HashingExtensible::modificarRegistro(Registro* registro){
	bool exito = 0;

	int clave = registro->obtenerClave();
	int posicionEnTablaDeHash = obtenerPosicion(clave);
	int numeroDeBucket = tablaDeHash[posicionEnTablaDeHash];

	Bucket* bucket = archivo->obtenerBucket(numeroDeBucket);

	if (bucket != NULL){
		exito = bucket->reemplazarRegistro(registro);
		if (!exito){
			if ( bucket->getRegistro(numeroDeBucket) !=NULL ){
				// En este caso no hubo exito al almacenar el registro y
				// estaba disponible dentro del bucket.
				redispersarBucket(bucket,numeroDeBucket,posicionEnTablaDeHash);
				agregarRegistro(registro);
			}
		}
	}
}

int HashingExtensible::eliminarRegistro(int clave){
	int exito = 1;

	int posicionEnTablaDeHash = obtenerPosicion(clave);
	int numeroDeBucket = tablaDeHash[posicionEnTablaDeHash];

	Bucket* bucket = archivo->obtenerBucket(numeroDeBucket);

	Registro* registro = bucket->getRegistro(clave);
	if ( registro !=NULL ){
		exito = bucket->eliminarRegistro(clave);
		if ( bucket->getCantidadDeRegistros() == 0 ){
			int dispersionBucket;
			if ((dispersionBucket = bucket->getTamanioDeDispersion()) == this->tablaDeHash.size()){
				this->archivo->liberarBucket(numeroDeBucket);
				tablaDeHash[posicionEnTablaDeHash] = tablaDeHash[posicionEnTablaDeHash & 1];

				// Evaluar nuevo valor de dispersión del bucket.

				// Verificar si los bloques se encuentran duplicados.
				//if (reducirTablaDeHash()==0){

					// Se reduce el tamaño de la tabla de hash.

				//}
			}else{

				// Dispersión diferente al tamaño de la tabla.
			}
		}
	}else{
		exito = 0;
	}

	return exito;
}

HashingExtensible::~HashingExtensible() {
	// TODO Auto-generated destructor stub
}

