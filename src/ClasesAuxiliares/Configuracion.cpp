/*
 * Configuracion.cpp
 *
 *  Created on: 15/10/2011
 *      Author: mart
 */

#include "Configuracion.h"

Configuracion::Configuracion(int argc, const char** argv ){
	this->cargarArgumentos(argc,argv);
	this->cargarArchivoConfig();
}

// Opciones por ahora: '-a', '-m', '-h','-c path'
void Configuracion::cargarArgumentos(int argc, const char** argv){
	this->vAuto = false;
	this->vManual = false;
	this->rutaConfig = "";

	int index,c;
    opterr = 0;
    while ((c = getopt (argc, (char* const*)argv, "amhvc:")) != -1)
    	switch (c){
    	case 'a':
    		this->vAuto = true;
    		break;
        case 'm':
        	this->vManual = true;
        	break;
        case 'h':
        	this->mostrarAyuda();
        	exit(0);
        	break;
        case 'v':
        	this->mostrarVersion();
        	exit(0);
        	break;
        case 'c':
			this->rutaConfig = optarg;
			break;
        case '?':
          if (optopt == 'c')
            fprintf (stderr, "La opción -%c requiere un argumento.\n",optopt);
          else if (isprint (optopt))
            fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
          else
            fprintf (stderr,"Caracter de opción desconocida `\\x%x'.\n",optopt);
          break;
        default:
        	cerr << "Para ayuda consulte con: -h \nPrograma terminado."<<endl;
        	exit(1);
        }
    for (index = optind; index < argc; index++)
      printf ("Argumento inválido %s\n", argv[index]);
    if(this->rutaConfig == ""){
    	cerr << "Falta la ruta de archivo de configuración, Para ayuda consulte con: -h \nPrograma terminado."<<endl;
    	exit(1);
    }
}


void Configuracion::cargarArchivoConfig(){
	char chr1='\0';
	char chr2='\0';
	vector<string> v;
	ManejadorDeArchivo man(this->rutaConfig);

	// Salteo el texto hasta llegar a detectar una doble barra "//" o llegar al EOF
	while ( ( (chr1!='/') || (chr2!='/') ) && (man.fin()!= true) ){
		man.leer(&chr1,1);
		man.leer(&chr2,1);
	}

	// Si no se acabó el archivo comienzo el parseo
	while(man.fin()!= true){
		man.leer(&chr1,1);
		if ( (chr1 == '-') || (chr1 == '+') ){ // El '-' indica que viene un argumento, el '+' indica un valor
			string cad("");
			if (chr1 == '-') cad += "-";
			man.leer(&chr1,1);
			while( (chr1 != ' ') && (man.fin()!= true) ){
				cad += chr1;
				man.leer(&chr1,1);
			}
			v.push_back(cad);
		}
	}
	// Acá ya tengo lleno el vector de strings, ahora lo paso al argc y argv
	int argc = v.size()+1; // El "+1" es para no usar la posición [0]
	int i;
	char** argv = new char*[argc];
	argv[0] = new char[(this->rutaConfig).size()+1]();
	strcpy (argv[0], (this->rutaConfig).c_str() );
	for(i=0; i<(int)v.size() ; i++ ){
		string dato (v[i]);
		int size = dato.size();
		argv[i+1] = new char[size+1](); // El "+1" es por el caracter de fin de string al hacer strcpy
		strcpy (argv[i+1], dato.c_str());
	}

	// Ahora cargo los parámetros que se obtuvieron del archivo de configuración
	this->rutaArbol = "";
	this->rutaHash = "";
	this->rutaApellidos= "";
	this->rutaDistritos = "";
	this->rutaDomicilios = "";
	this->rutaDomicilios = "";
	this->rutaLog = "";
	this->rutaNombres = "";
	this->rutaInformes = "";
	this->claveVigenere = "";
	this->tamanioNodo = 0;
	this->tamanioBucket = 0;
	int index,c;
    opterr = 0;
    optind = 1; // Inicalo la variable para poder usar el getopt otra vez
    while ((c = getopt (argc, (char* const*)argv, "A:D:N:B:P:S:M:C:R:L:I:K:")) != -1)
    	switch (c){
    	case 'D':
    		this->rutaHash = optarg;
    		break;
        case 'A':
        	this->rutaArbol = optarg;
        	break;
        case 'N':
        	this->tamanioNodo = atoi(optarg);
        	break;
        case 'B':
        	this->tamanioBucket = atoi(optarg);
        	break;
        case 'P':
        	this->rutaPass = optarg;
        	break;
        case 'S':
        	this->rutaApellidos = optarg;
        	break;
        case 'M':
        	this->rutaNombres = optarg;
        	break;
        case 'C':
        	this->rutaDistritos = optarg;
        	break;
        case 'R':
        	this->rutaDomicilios = optarg;
        	break;
        case 'L':
        	this->rutaLog = optarg;
        	break;
        case 'I':
            this->rutaInformes = optarg;
            break;
        case 'K':
            this->claveVigenere = optarg;
            break;
        case '?':
          if (optopt == 'A')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'D')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'N')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'B')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'P')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'S')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'M')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'C')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'R')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'L')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'I')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (optopt == 'K')fprintf (stderr, "Arch. Config. > La opción -%c requiere un argumento.\n",optopt);
          else if (isprint (optopt))
            fprintf (stderr, "Arch. Config. > Opción desconocida `-%c'.\n", optopt);
          else
            fprintf (stderr,"Arch. Config. > Caracter de opción desconocida `\\x%x'.\n",optopt);
          break;
        default:
        	cerr << "Arch. Config. > Corregir archivo. "<<endl;
        	cerr << "Para ayuda consulte con: -h"<<endl;
        	break;
        }
    for (index = optind; index < argc; index++)
    	cerr << "Arch. Config. > Opción inválida: " << argv[index] << endl;

    if( (this->rutaArbol == "") || (this->rutaHash == "") ){
    	cerr << "Arch. Config. > Falta la ruta de archivo de Árbol y/o Hash."<<endl;
    	cerr << "Para ayuda consulte con: -h\nPrograma terminado."<<endl;
    	exit(1);
    }
	// Libero la memoria que yo instancié
	for(i=0; i<argc ; i++ ){ delete[] argv[i]; }
	delete[] argv;
}


string Configuracion::pathArbol(){
	return this->rutaArbol;
}

string Configuracion::pathHash(){
	return this->rutaHash;
}

string Configuracion::pathPassword(){
	return this->rutaPass;
}

bool Configuracion::isAuto(){
	return this->vAuto;
}

bool Configuracion::isManual(){
	return this->vManual;
}

int Configuracion::darTamanioNodo(){
	return this->tamanioNodo;
}

int Configuracion::darTamanioBucket(){
	return this->tamanioBucket;
}



void Configuracion::mostrarAyuda(){
	cout << "Argumentos válidos pasados por parámetro: "<<endl;
	cout << "	-c <ruta>	Agrega la ruta del archivo de configuración (obligatorio para acceder al sistema)."<<endl;
	cout << "	-v		Muestra la versión y sale del programa."<<endl;
	cout << "	-h		Muestra esta ayuda y sale del programa."<<endl<<endl;
	cout << "Para obtener el User/Pass de ingreso al sistema consulte el manual de usuario."<<endl<<endl<<endl;
	cout << "Archivo de configuración. Para su uso:"<<endl;
	cout << "La lectura de las opciones se relizará a partir del delimitador '/"<<"/'."<<endl;
	cout << "La lectura se realizará hasta el final del archivo."<<endl;
	cout << "Todo texto anterior al delimitador será tomado como comentario."<<endl;
	cout << "Si el mismo no existe, todo el archivo será tomado como comentario."<<endl<<endl;
	cout << "Archivo de configuración. Opciones válidas (cada una debe estar separada con un espacio):"<<endl;
	cout << "	-A +<ruta>		Asigna la ruta del archivo de árbol B+."<<endl;
	cout << "	-D +<ruta>		Asigna la ruta del archivo de dispersión."<<endl;
	cout << "	-N +<valor>		Asigna el tamaño del Nodo del árbol B+."<<endl;
	cout << "	-B +<valor>		Asigna el tamaño del Bucket del archivo de dispersión."<<endl;
	cout << "	-P +<ruta>		Asigna la ruta del archivo de Password del administrador."<<endl;

	cout << "	-S +<ruta>		Asigna la ruta de los apellidos." << endl;
	cout << "	-M +<ruta>		Asigna la ruta de los nombres." << endl;
	cout << "	-C +<ruta>		Asigna la ruta de los distritos." << endl;
	cout << "	-R +<ruta>		Asigna la ruta de los domicilios." << endl;
	cout << "	-L +<ruta>		Asigna la ruta del log." << endl;
	cout << "	-I +<ruta>		Asigna la ruta de los informes." << endl;
	cout << ""<<endl;
}

void Configuracion::mostrarVersion(){
	cout <<"Versión 2.1"<<endl;
	// Versíon xx.yy   Con:  xx etapa del TP, yy entrega del TP
}

string Configuracion::pathApellidos()
{
	return this->rutaApellidos;
}

string Configuracion::pathNombres()
{
	return this->rutaNombres;
}

string Configuracion::pathDomicilios()
{
	return this->rutaDomicilios;
}

string Configuracion::pathDistritos()
{
	return this->rutaDistritos;
}

string Configuracion::pathLog()
{
	return this->rutaLog;
}

string Configuracion::pathInformes(){
	return this->rutaInformes;
}

string Configuracion::getClaveVigenere() const
{
    return claveVigenere;
}

void Configuracion::setClaveVigenere(string claveVigenere)
{
    this->claveVigenere = claveVigenere;
}

Configuracion::~Configuracion() {

}
