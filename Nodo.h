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

	string nombre;
	//Arbol* elArbol;
	unsigned int id;
	unsigned int nivel;
	bool esDirectorio;
	off_t tamano;
	time_t ultimaModificacion;
	Nodo* padre;
	list<Nodo*> *hijos;
	unsigned int numeroHijosMaximo;

	
};

#endif
