#pragma once
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


	void writeFile(char* datos);
	char* readFile();
	void writeBlock(char* datos, int idBloque);
	char* readBlock(int idBloque);

};

#endif
