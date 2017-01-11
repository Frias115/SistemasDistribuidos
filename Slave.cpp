#include "Slave.h"
#include "Nodo.h"

// 1000 BYTES
#define BLOQUE 1000


void Slave::format(int numeroDisco,int size){

	char inicializar = '0';
	string nombre = "disco"+to_string(numeroDisco)+".dat";

	FILE* disco=fopen(nombre.c_str(), "w");
	fseek(disco,size,SEEK_SET);
	fwrite(&inicializar,sizeof(char),1,disco);
	fclose(disco);

}

void Slave::readBlock(int numeroDisco, int cantidad,int numeroBloque){

	char* datos = (char*) calloc(BLOQUE, sizeof(char));

	string nombre = "disco"+to_string(numeroDisco)+".dat";

	FILE* miDisco = fopen(nombre.c_str(),"r+");
	fseek(miDisco,numeroBloque*BLOQUE,SEEK_SET);

	fread(datos,sizeof(char),cantidad,miDisco);
	fclose(miDisco);

	MPI_Send(datos, sizeof(char) * BLOQUE, MPI_BYTE , 0, 0, MPI_COMM_WORLD);
	free(datos);

}


void Slave::writeBlock(int numeroDisco, int cantidad,int numeroBloque, char* datos) {

	string nombre = "disco"+to_string(numeroDisco)+".dat";

	FILE* miDisco = fopen(nombre.c_str(),"r+");
	fseek(miDisco,numeroBloque*BLOQUE,SEEK_SET);

	fwrite(datos,sizeof(char),cantidad,miDisco);

	fclose(miDisco);
}
