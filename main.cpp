#include "Arbol.h"
#include "Nodo.h"
#include "Terminal.h"
#include <list>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
using namespace std;

int main(){
	//Arbol* nuevoarbol = new Arbol();
	//nuevoarbol->addChild("documentos", true);
	//nuevoarbol->addChild("prueba", false);
	//nuevoarbol->removeChild("documentos");
	/*for (list<Nodo*>::iterator it=nuevoarbol->directorioActual->hijos->begin(); it != nuevoarbol->directorioActual->hijos->end(); ++it)
    cout << ' ' << (*it)->nombre;*/
	/*
	Terminal* terminal = new Terminal();
	terminal->ls(nuevoarbol);
	terminal->pwd(nuevoarbol);
	terminal->cd(nuevoarbol,"hola");
	terminal->mkdir("hola",nuevoarbol);
	terminal->ls(nuevoarbol);
	terminal->rmdir("hola",nuevoarbol);
	terminal->ls(nuevoarbol);
	//terminal->rm("prueba",nuevoarbol);
	terminal->ls(nuevoarbol);
	terminal->exit(nuevoarbol);
	*/
	Disco* disco = new Disco();
	Terminal* terminal = new Terminal();
	Arbol* nuevoArbol = terminal->cargar();
	terminal->ls(nuevoArbol);
	terminal->format(32000);
	terminal->upload(nuevoArbol,"hola.txt",disco);


	return 0;


}
