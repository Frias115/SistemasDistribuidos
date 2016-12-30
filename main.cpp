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

void master(int numslaves)
{
	Arbol* nuevoArbol = new Arbol();
	Terminal* terminal = new Terminal();
	Disco* disco = new Disco(numslaves - 1);

	//nuevoArbol = terminal->cargar();

	//TODO: Terminal

	//tipomensaje msg;
	int salir = 0;
	int tam = 0;
	char* comando = new char[20]; // memoria dinamica, no estatica
	char* nombre = new char[20];

	disco->format(numslaves - 1, 32000);

	terminal->upload(nuevoArbol,"adiosBleh.txt",disco);

	/*
	while(!salir){
		scanf("%s",comando); //master

		switch(comando[0])
		{

			case 'l':
				//printf("pulsado l\n");
				msg = pulsadol;
				enviaMensaje(numSlaves, msg);
			break;

			case 'b':
				//printf("pulsado b\n");
				msg = pulsadob;
				enviaMensaje(numslaves, msg);
			break;

			case 'f':
				scanf("%s",&tam);
				msg = format;
				enviaMensajeFormat(numslaves,msg,tam);
			break;

			case 'm':
				scanf("%s",nombre);
				msg = mkdir;

				strlen();// completar
				enviaMensajeMkdir(numslaves,msg,nombre, tam);
			break;

			default:
				msg = pulsadoerror;
				salir = 1;
			break;
		};


	}
	*/
	delete nuevoArbol;
	delete disco;
	delete terminal;

}

void slave()
{
	Slave* slave = new Slave();

	char* datos = (char*) calloc(BLOQUE, sizeof(char));
	MPI_Status status;
	int salir = 0;
	//tipomensaje msg;
	int tam, bloque, numeroDisco;


	MPI_Recv(&tam, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
	MPI_Recv(&numeroDisco, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
	slave->format(numeroDisco,tam);
	printf("Recibido format: %d\n", tam);

	
	MPI_Recv(&numeroDisco, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
	MPI_Recv(&tam, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
	MPI_Recv(&bloque, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
	MPI_Recv(datos, sizeof(char) * BLOQUE, MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
	slave->writeBlock(numeroDisco,tam,bloque,datos);
	

	//TODO: Terminal
	/*
	while(!salir)
	{
		//recibir orden del master

		//MPI_Recv...

		MPI_Recv(&msg, sizeof(tipomensaje), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);

								// Que solo hago los printf un esclavo o el maestro
		// ejecutar orden
		switch(msg)
		{

			case pulsadol:
				printf("pulsado l\n");
			break;

			case pulsadob:
				printf("pulsado b\n");
			break;

			case format:
				MPI_Recv(&tam, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&numeroDisco, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				slave->format(numeroDisco,tam);
				printf("Recibido format: %d\n", tam);
			break;

			case read:
				MPI_Recv(&numeroDisco, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&tam, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&bloque, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				slave->readBlock(numeroDisco,tam,bloque);
			break;

			case write:
				MPI_Recv(&numeroDisco, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&tam, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&bloque, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				MPI_Recv(&datos, sizeof(BLOQUE), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				slave->writeBlock(numeroDisco,tam,bloque,datos);
			break;

			case mkdir:
			{
				MPI_Recv(&tam, sizeof(int), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				char* nombre = new char[tam];
				MPI_Recv(nombre, sizeof(char)*tam, MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
				printf("Recibido mkdir: %s\n", nombre);
			break;
			}

			default:
				printf("ERROR\n");
				salir = 1;
			break;
		};

	}
	*/
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