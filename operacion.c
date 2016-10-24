#include <sisdist.c>



void inicializarArbol(){

	struct arbol elArbol;
	struct nodo nodoPadre;

	elArbol.directorioActual = nodoPadre;
	elArbol.numeroNodos = 1;
	nodoPadre.ID = 0;
	nodoPadre.nombre = "root";
	nodoPadre.elArbol = elArbol;
	nodoPadre.nivel = 0;
	nodoPadre.esDirectorio = true;
	nodoPadre.padre = NULL;
	elArbol.root = nodoPadre;
	elArbol.ultimoID = nodoPadre.ID;

}

nodo* addChild(nodo* nodoPadre){

	nodo *nuevoNodo;

	if(nodoPadre.esDirectorio && !findChild()){

		nuevoNodo.nivel = nodoPadre.nivel +1;
		nuevoNodo.ID = nodoPadre.elArbol.ultimoID +1;

		return nuevoNodo;
	}
}

nodo* findChild(char nombreNodoABuscar[25],nodo* padre){

	int tamanoHijos = sizeof(padre.hijos)/sizeof(int);

	for(int i = 0;i<tamanoHijos;i++){

		if(padre.hijos[i].nombre == nombreNodoABuscar)	return padre.hijos[i];
		
	}

	return NULL;

}

void updateChild(nodo* nodoAActualizar,char nuevoNombre[25],off_t nuevoTamano, time_t nuevaUltimaModificacion){

	if(findChild(nuevoNombre,nodoAActualizar.padre) == NULL){
			nodoAActualizar.nombre = nuevoNombre;
			nodoAActualizar.tamano = nuevoTamano;
			nodoAActualizar.ultimaModificacion = nuevaUltimaModificacion;

	}
}

void removeChild(nodo* nodoAEliminar){

	//Si es directorio y no tiene hijos
	if((nodoAEliminar.esDirectorio && nodoAEliminar.hijos[] == NULL) || !nodoAEliminar.esDirectorio){

		nodoAEliminar.elArbol.numeroNodos--;

		nodo* nodoPadre = nodoAEliminar.padre;

	}




}














