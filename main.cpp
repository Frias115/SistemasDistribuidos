#include "Arbol.h"
#include "Nodo.h"
#include <list>
#include <string>
#include <iostream>
#include <sys/stat.h>
using namespace std;

int main(){

	Arbol* nuevoarbol = new Arbol();

	nuevoarbol->addChild("documentos", true);



	nuevoarbol->addChild("prueba", false);

	for (list<Nodo*>::iterator it=nuevoarbol->directorioActual->hijos->begin(); it != nuevoarbol->directorioActual->hijos->end(); ++it)
    cout << ' ' << (*it)->nombre;

	return 0;
}