#pragma once
#include "Arbol.h"
#include "mpi.h"
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

	void writeBlock(int numeroDisco, int cantidad,int numeroBloque, char* datos);
	void readBlock(int numeroDisco, int cantidad,int numeroBloque);

    //Inicializa los .dat del disco
    void format(int numeroDisco,int size);



};

#endif 
