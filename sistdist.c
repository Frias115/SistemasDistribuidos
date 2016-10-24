#include <sys/stat.h>

struct arbol{

	int numeroNodos;
	nodo* root;
	unsigned int ultimoID;
	nodo* directorioActual;
};

struct nodo{

	char nombre[25];
	arbol* elArbol;
	unsigned int ID;
	unsigned int nivel;
	bool esDirectorio;
	off_t tamano;
	time_t ultimaModificacion;
	nodo* padre;
	nodo* hijos[];

};