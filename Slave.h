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

#ifndef SLAVE
#define SLAVE

class Slave {
public:
	Disco(int numeroDiscos);
	int numeroDiscos;
	void buscarSectoresLibres(int numeroBloques,Nodo* nodo);
	void writeFile(string archivo,Nodo* nodo);
	void readFile(Nodo* nodo);
	void writeBlock(char* datos, int cantidad, int idBloque);
	void readBlock(char* datos, int cantidad, int idBloque);
	int findDisco(int idBloque,int numeroDiscos);
	int findSectorDelDisco(int idBloque,int numeroDiscos);

    //Inicializa los .dat del disco
    void format(int numeroDiscos,int size);



};

#endif /* SLAVE_H_ */
