#pragma once
#include "Nodo.h"
#include <string>
#include <sys/stat.h>

#ifndef ARBOL
#define ARBOL

using namespace std;

class Arbol{

public:

	int numeroNodos;
	Nodo* root;
	unsigned int ultimoID;
	Nodo* directorioActual;



	Arbol();

	Nodo* addChild(string nombreNodo, bool directorio);

	Nodo* findChild(string nombreABuscar);

	void updateChild(string nombreABuscar,string nuevoNombre/*, off_t nuevoTamano, time_t nuevaUltimaModificacion*/);

	void removeChild(string nombreABuscar);

};

#endif
