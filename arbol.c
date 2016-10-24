

Arbol* inicializarArbol(){

	Arbol elArbol;
	Nodo nodoPadre;

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

	return elArbol;

}

Nodo* addChild(char nombreNodo[25], bool directorio, Arbol* arbol){

	if(arbol.directorioActual.esDirectorio && !findChild()){

		Nodo* nuevoNodo;

		nuevoNodo.nombre = nombreNodo;
		nuevoNodo.elArbol = arbol;
		nuevoNodo.id = arbol.ultimoID + 1;
		nuevoNodo.nivel = nodoPadre.nivel + 1;
		nuevoNodo.esDirectorio = directorio;
		//off_t tamano;
		//time_t ultimaModificacion;
		nuevoNodo.padre = arbol.directorioActual;
		//nodo* hijos;
		//unsigned int numeroHijosMaximo

		return nuevoNodo;
	}

	return NULL;
}

Nodo* findChild(char nombreABuscar[25], Arbol* arbol){

	int tamanoHijos = sizeof(arbol.directorioActual.hijos)/sizeof(int); // int seria el tamaño de los hijos

	for(int i = 0;i<tamanoHijos;i++){

		if(arbol.directorioActual.hijos[i].nombre == nombreABuscar)	return arbol.directorioActual.hijos[i];
		
	}

	return NULL;

}

void updateChild(Arbol* arbol, char nombreABuscar[25],char nuevoNombre[25], off_t nuevoTamano, time_t nuevaUltimaModificacion){

	Nodo* nodoAActualizar;

	nodoAActualizar = arbol.findChild(nombreABuscar, arbol);

	if(nodoAActualizar == NULL){
			nodoAActualizar.nombre = nuevoNombre;
			nodoAActualizar.tamano = nuevoTamano;
			nodoAActualizar.ultimaModificacion = nuevaUltimaModificacion;
	}
}

void removeChild(char nombreABuscar[25], Arbol* arbol){

	Nodo* nodoAEliminar;

	nodoAEliminar = arbol.findChild(nombreABuscar, arbol);

	int tamanoHijos = sizeof(nodoAEliminar.hijos)/sizeof(int); // int seria el tamaño de los hijos

	//Si es directorio y no tiene hijos
	if((nodoAEliminar.esDirectorio && nodoAEliminar.hijos == NULL) || !nodoAEliminar.esDirectorio){

		arbol.numeroNodos--;

		nodo* nodoPadre = nodoAEliminar.padre;

		nodoPadre

	}
}