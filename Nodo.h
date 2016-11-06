#pragma once
#include <list>
#include <string>
#include <iostream>
#include <sys/stat.h>
using namespace std;

#ifndef NODO
#define NODO


class Nodo
{

public:
	Nodo();
	string nombre;
	//Arbol* elArbol;
	int id;
	int nivel;
	bool esDirectorio;
	off_t tamano;
	time_t ultimaModificacion;
	Nodo* padre;
	list<Nodo*> *hijos;
	//unsigned int numeroHijosMaximo;

	
};

#endif
