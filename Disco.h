#pragma once
#include "Arbol.h"
#include <list>
#include <string>
#include <string.h>
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
	void readFile(Nodo* nodo);
	void writeBlock(char* datos, int cantidad, int idBloque);
	void readBlock(char* datos, int cantidad, int idBloque);

};

#endif
