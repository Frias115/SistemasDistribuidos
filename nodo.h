

#ifndef NODO 
#define NODO

typedef struct Nodo{

	char nombre[25];
	arbol* elArbol;
	unsigned int id;
	unsigned int nivel;
	bool esDirectorio;
	off_t tamano;
	time_t ultimaModificacion;
	nodo* padre;
	nodo* hijos;
	unsigned int numeroHijosMaximo;

}Nodo;

#endif