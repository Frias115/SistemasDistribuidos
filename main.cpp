#include "Arbol.h"
#include "Nodo.h"
#include "Terminal.h"
#include "mpi.h"
#include "Slave.h"
#include <list>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
using namespace std;

#define BLOQUE 1000

typedef enum tipoMensaje
{
	format = 0,
	upload,
	download,
	salida

}tipoMensaje;

void enviaMensaje(int numslaves, tipoMensaje msg)
{
	for(int i=1; i < numslaves; i++)
	{
		//MPI_Send(const void *buf, int count, MPI_Datatype datatype, int des, int tag, MPI_Comm comm);
		MPI_Send(&msg, sizeof(tipoMensaje), MPI_BYTE , i, 0, MPI_COMM_WORLD);
	}
}

void master(int numSlaves)
{
	cout << "Hola soy el master" << endl;
	Arbol* nuevoArbol = new Arbol();
	Terminal* terminal = new Terminal();
	Disco* disco = new Disco(numSlaves - 1);

	nuevoArbol = terminal->cargar();

	tipoMensaje msg;
	bool salir = false;
	int tam = 0;

	while(!salir){
		cout << "Introduce tu comando: " << endl;
		string comando;
		string nombre;
		cin >> comando;

		if(strcmp(comando.c_str(), "format") == 0)
		{
			int size = 0;
			while(size <= 0){
				cout << "Introduce size de disco: ";
				cin >> size;
			}
			msg = format;
			enviaMensaje(numSlaves,msg);
			disco->format(numSlaves - 1, size);
		} 
		else if (strcmp(comando.c_str(), "mkdir") == 0)
		{
			while(nombre.size() == 0){
				cout << "Introduce nombre del nuevo directorio: ";
				cin >> nombre;
			}
			terminal->mkdir(nombre, nuevoArbol);
		}
		else if (strcmp(comando.c_str(), "rmdir") == 0)
		{
			while(nombre.size() == 0){
				cout << "Introduce nombre del directorio a eliminar: ";
				cin >> nombre;
			}
			terminal->rmdir(nombre, nuevoArbol);
		}
		else if (strcmp(comando.c_str(), "rm") == 0)
		{
			while(nombre.size() == 0){
				cout << "Introduce nombre del archivo a eliminar: ";
				cin >> nombre;
			}
			terminal->rm(nombre, nuevoArbol);
		}
		else if (strcmp(comando.c_str(), "ls") == 0)
		{
			terminal->ls(nuevoArbol);
		}
		else if (strcmp(comando.c_str(), "pwd") == 0)
		{
			terminal->pwd(nuevoArbol);
		}
		else if (strcmp(comando.c_str(), "cd") == 0)
		{
			while(nombre.size() == 0){
				cout << "Introduce nombre del directorio: ";
				cin >> nombre;
			}
			terminal->cd(nuevoArbol, nombre);
		}
		else if (strcmp(comando.c_str(), "mv") == 0)
		{
			string nombreSustituir;
			while(nombreSustituir.size() == 0){
				cout << "Introduce nombre a sustituir: ";
				cin >> nombreSustituir;
			}

			while(nombre.size() == 0){
				cout << "Introduce nuevo nombre: ";
				cin >> nombre;
			}

			terminal->mv(nombre, nombreSustituir, nuevoArbol);
		}
		else if (strcmp(comando.c_str(), "upload") == 0)
		{
			while(nombre.size() == 0){
				cout << "Introduce nombre del archivo a subir: ";
				cin >> nombre;
			}

			terminal->upload(nuevoArbol, nombre, disco);
		}
		else if (strcmp(comando.c_str(), "download") == 0)
		{
			while(nombre.size() == 0){
				cout << "Introduce nombre del archivo a descargar: ";
				cin >> nombre;
			}
			
			terminal->download(nuevoArbol, nombre, disco);
		}
		else if (strcmp(comando.c_str(), "exit") == 0)
		{
			salir = true;

			msg = salida;
			enviaMensaje(numSlaves,msg);

			terminal->exit(nuevoArbol);
		}
		else if (strcmp(comando.c_str(), "help") == 0)
		{
			//TODO: Instrucciones
		}
		else
		{
			cout << "Ese comando no existe." << endl;
		}
	}
	
	
	delete nuevoArbol;
	delete disco;
	delete terminal;

}

void slave()
{
	cout << "Hola soy un esclavo" << endl;
	Slave* slave = new Slave();

	char* datos = (char*) calloc(BLOQUE, sizeof(char));
	MPI_Status status;
	bool salir = false;
	int tam, bloque, numeroDisco;

	while(!salir)
	{
		tipoMensaje msg;
		MPI_Recv(&msg, sizeof(tipoMensaje), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);

		switch(msg)
		{
			case format:
				MPI_Recv(&tam, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&numeroDisco, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				slave->format(numeroDisco,tam);
			break;

			case download:
				cout << "Recibido download" << endl;
				MPI_Recv(&numeroDisco, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&tam, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&bloque, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				slave->readBlock(numeroDisco,tam,bloque);
			break;

			case upload:
				MPI_Recv(&numeroDisco, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&tam, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&bloque, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(datos, sizeof(char) * BLOQUE, MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);

				slave->writeBlock(numeroDisco,tam,bloque,datos);
			break;

			case salida:
				salir = true;
			break;

			default:
				cout << "ERROR" << endl;
			break;
		};

	}

	free(datos);
}


int main(int argc, char** argv){
	
	int commSize;
	int mpiID;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiID);

	if(mpiID == 0)		// Gather scater, posible alternativa eficiente para esto, pero es mas avanzado
	{
		master(commSize);
	}
	else
	{
		slave();
	}

	MPI_Finalize();
	return 0;
}