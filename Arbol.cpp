#include "Arbol.h"


Arbol::Arbol(){

	Nodo* nodoPadre = new Nodo();

	this->directorioActual = nodoPadre;
	this->numeroNodos = 1;

	nodoPadre->id = 0;
	nodoPadre->nombre = "root";
	//nodoPadre->elArbol = this;
	nodoPadre->nivel = 0;
	nodoPadre->esDirectorio = true;
	nodoPadre->padre = NULL;

	this->root = nodoPadre;
	this->ultimoID = nodoPadre->id;

}
 
Nodo* Arbol::addChild(string nombreNodo, bool directorio){

	if(directorioActual->esDirectorio && !findChild(nombreNodo)){

		Nodo* nuevoNodo = new Nodo();

		nuevoNodo->nombre = nombreNodo;
		//nuevoNodo->elArbol = arbol;
		nuevoNodo->id = ultimoID + 1;
		nuevoNodo->nivel = directorioActual->nivel + 1;
		nuevoNodo->esDirectorio = directorio;
		//off_t tamano;
		//time_t ultimaModificacion;
		nuevoNodo->padre = directorioActual;
		//unsigned int numeroHijosMaximo

		directorioActual->hijos->push_back(nuevoNodo);

		ultimoID++;
		numeroNodos++;

		return nuevoNodo;
	}

	return NULL;
}

Nodo* Arbol::findChild(string nombreABuscar){

	if(directorioActual->hijos->size() > 0){
		for(std::list<Nodo*>::iterator i = directorioActual->hijos->begin(); i != directorioActual->hijos->end(); i++){

			if((*i)->nombre.compare(nombreABuscar) == 0 ) return (*i);
		
		}
	}

	return NULL;

}

void Arbol::updateChild(string nombreABuscar,string nuevoNombre/*, off_t nuevoTamano, time_t nuevaUltimaModificacion*/){

	Nodo* nodoAActualizar = new Nodo();

	nodoAActualizar = findChild(nombreABuscar);

	if(nodoAActualizar != NULL){
			nodoAActualizar->nombre = nuevoNombre;
			//nodoAActualizar.tamano = nuevoTamano;
			//nodoAActualizar.ultimaModificacion = nuevaUltimaModificacion;
	}
}

void Arbol::removeChild(string nombreABuscar){

	Nodo* nodoAEliminar;
	nodoAEliminar = findChild(nombreABuscar);
	//Si es directorio y no tiene hijos
	if((nodoAEliminar->esDirectorio && nodoAEliminar->hijos->empty()) || !nodoAEliminar->esDirectorio){
		if(nodoAEliminar->bloquesUsados->size()>0){
			for(list<int>::iterator i = nodoAEliminar->bloquesUsados->begin(); i != nodoAEliminar->bloquesUsados->end(); i++){
				bool free = true;
				FILE* sectoresLibres = fopen("sectoreslibres.dat","r+");
				fseek(sectoresLibres,sizeof(bool)*(*i),SEEK_SET);
				fwrite(&free, sizeof(bool), 1, sectoresLibres);
			}
		}
		numeroNodos--;

		Nodo* nodoPadre = nodoAEliminar->padre;

		nodoPadre->hijos->remove(nodoAEliminar);

	}
}
