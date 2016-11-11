#pragma once
#include "Arbol.h"
#include <list>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

#ifndef DISCO 
#define DISCO

class Disco{
public:

	void buscarSectoresLibres(int numeroBloques,Nodo* nodo);
	void writeFile(string archivo,Nodo* nodo);
	char* readFile(Nodo* nodo);
	void writeBlock(char* datos, int cantidad, int idBloque);
	char* readBlock(int idBloque);

};

#endif
