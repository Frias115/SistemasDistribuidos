#pragma once
#include "Arbol.h"
#include "Nodo.h"
#include <list>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

#ifndef TERMINAL
#define TERMINAL


class Terminal{
public:

    //Lista los hijos correspondientes al directorio actual
    void ls (Arbol* elArbol);


    //Muestra la ruta actual, desde root hasta el directorio actual
    void pwd (Arbol* elArbol);


    //Avanzamos de directorio actual al siguiente, o volvemos al anterior o a root
    void cd (Arbol* elArbol, string nombreNuevoDirectorio);


    //Cambia el nombre de un nodo
    void mv(string nuevoNombreNodo, string nombreNodo, Arbol* elArbol);


    //Copia el nodo pasado por parametro en la posicion indicada
    void cp(string origen, string destino, Arbol* elArbol);


    //Crea nuevo nodo de tipo directorio con el nombre pasado por parametro
    void mkdir(string nombreNuevoDirectorio, Arbol* elArbol);


    //Elimina un nodo directorio sin hijos
    void rmdir(string directorioAEliminar,Arbol* elArbol);


    //Elimina un nodo fichero
    void rm(string ficheroAEliminar,Arbol* elArbol);


    //Guarda el nodo root del arbol y llama a su metodo recursivo
    void exit(Arbol* elArbol);


    //Guarda los nodos del arbol de manera recusiva
    void escribeNodoRecursiva(Nodo* nodo);


    //Carga el nodo root al arbol y llamam a su metodo recursivo
    Arbol* cargar();


    //Carga los nodos al arbol de manera recursiva
    Nodo* cargarNodoRecursiva(Arbol* elArbol, FILE* arbolBinario);


};

#endif
