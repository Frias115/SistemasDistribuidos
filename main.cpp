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
	Arbol* nuevoArbol = new Arbol();
	nuevoArbol->addChild("documentos", true);
	nuevoArbol->addChild("prueba", false);
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
	Disco* disco = new Disco(4);
	Terminal* terminal = new Terminal();
	disco->format(4,32000);
	//Arbol* nuevoArbol = terminal->cargar();
	terminal->ls(nuevoArbol);
	//terminal->download(nuevoArbol,"adiosBleh.txt",disco);
	terminal->ls(nuevoArbol);
	//terminal->format(32000);
	//terminal->upload(nuevoArbol,"holaBleh.txt",disco);
	terminal->upload(nuevoArbol,"adiosBleh.txt",disco);
	terminal->cd(nuevoArbol,"documentos");
	terminal->upload(nuevoArbol,"adiosBleh.txt",disco);
	terminal->cd(nuevoArbol,"..");
	terminal->rm("adiosBleh.txt",nuevoArbol);
	//terminal->upload(nuevoArbol,"prueba1.txt",disco);
	//terminal->upload(nuevoArbol,"prueba2.txt",disco);

	terminal->exit(nuevoArbol);
	terminal->ls(nuevoArbol);

	return 0;


}
