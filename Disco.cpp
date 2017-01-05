#include "Disco.h"
#include "Nodo.h"

// 1000 BYTES
#define BLOQUE 1000

typedef enum tipoMensaje
{
	format = 0,
	upload,
	download,
	exit

}tipoMensaje;

Disco::Disco(int numeroDiscos){
	this->numeroDiscos = numeroDiscos;
}
void Disco::buscarSectoresLibres(int numeroBloquesNecesarios,Nodo* nodo) {

	bool bloqueValido;
	bool ocupate = false;
	int counter = 0;
	FILE* sectoresLibres = fopen("sectoreslibres.dat","r+");
	//tamano correcto de sectoresLibres
	for(int i=0;i<32000*numeroDiscos;i++){

		fread(&bloqueValido,sizeof(bool),1,sectoresLibres);
		if(bloqueValido){
			nodo->bloquesUsados->push_back(i);
			fseek(sectoresLibres,sizeof(bool)*i,SEEK_SET);
			fwrite(&ocupate,sizeof(bool),1,sectoresLibres);
			counter++;
			if(counter==numeroBloquesNecesarios){
				fclose(sectoresLibres);
				return;
			}
		}
	}
	fclose(sectoresLibres);
}

void Disco::writeFile(string archivo, Nodo* nodo) {

	char* buffer = (char*) calloc(BLOQUE, sizeof(char));

	//cout << archivo << endl;

	FILE* miArchivo;
	int cantidad = 0, counter = 0;

	for(list<int>::iterator i = nodo->bloquesUsados->begin(); i != nodo->bloquesUsados->end(); i++, counter++){

		miArchivo = fopen(archivo.c_str(),"r+");
		fseek(miArchivo,counter*BLOQUE, SEEK_SET);
		fread(buffer,sizeof(char),BLOQUE,miArchivo);
		fclose(miArchivo);

		//El archivo ocupa un bloque o menos
		if(nodo->sizeNodo <= BLOQUE){
			cantidad = nodo->sizeNodo;
			writeBlock(buffer,cantidad,(*i));
		}
		//El archivo ocupa mas de un bloque
		else if(nodo->sizeNodo - (BLOQUE * counter) > BLOQUE){
			writeBlock(buffer,BLOQUE,(*i));
		} else {
			cantidad = nodo->sizeNodo - (BLOQUE * counter);
			writeBlock(buffer,cantidad,(*i));
		}

	}
	free(buffer);
}

void Disco::writeBlock(char* datos, int cantidad, int idBloque) {

	int numeroDisco = findDisco(idBloque,numeroDiscos);
	int numeroBloque = findSectorDelDisco(idBloque,numeroDiscos);
	string nombre = "disco"+to_string(numeroDisco)+".dat";

	// Envio un msg para que el disco que necesito espere los datos

	tipoMensaje msg = upload;
	MPI_Send(&msg, sizeof(tipoMensaje), MPI_BYTE , numeroDisco +1, 0, MPI_COMM_WORLD);

	// Envio numeroDisco, cantidad, numeroBloque, datos

	MPI_Send(&numeroDisco,  sizeof(int) , MPI_BYTE , numeroDisco +1, 0, MPI_COMM_WORLD);
	MPI_Send(&cantidad, sizeof(int), MPI_BYTE , numeroDisco +1, 0, MPI_COMM_WORLD);
	MPI_Send(&numeroBloque, sizeof(int), MPI_BYTE , numeroDisco +1, 0, MPI_COMM_WORLD);
	MPI_Send(datos, sizeof(char) * BLOQUE, MPI_BYTE , numeroDisco +1, 0, MPI_COMM_WORLD);


}

void Disco::readFile(Nodo* nodo){

	FILE* nuevoArchivo = fopen(nodo->nombre.c_str(),"w");
	fclose(nuevoArchivo);
	char* datos = (char*) calloc(BLOQUE, sizeof(char));
	int cantidad = 0,counter = 0;

	for(std::list<int>::iterator i = nodo->bloquesUsados->begin(); i != nodo->bloquesUsados->end(); i++,counter++){

		//El archivo ocupa un bloque o menos
		if(nodo->sizeNodo <= BLOQUE){
			cantidad = nodo->sizeNodo;
			readBlock(datos, cantidad, (*i));
			nuevoArchivo = fopen(nodo->nombre.c_str(),"r+");
			fseek(nuevoArchivo,counter*BLOQUE, SEEK_SET);
			fwrite(datos,sizeof(char),cantidad,nuevoArchivo);
		}
		//El archivo ocupa mas de un bloque
		else if(nodo->sizeNodo - (BLOQUE * counter) > BLOQUE){
			readBlock(datos,BLOQUE,(*i));
			nuevoArchivo = fopen(nodo->nombre.c_str(),"r+");
			fseek(nuevoArchivo,counter*BLOQUE, SEEK_SET);
			fwrite(datos,sizeof(char),BLOQUE,nuevoArchivo);
		} else {
			cantidad = nodo->sizeNodo - (BLOQUE * counter);
			readBlock(datos, cantidad, (*i));
			nuevoArchivo = fopen(nodo->nombre.c_str(),"r+");
			fseek(nuevoArchivo,counter*BLOQUE, SEEK_SET);
			fwrite(datos,sizeof(char),cantidad,nuevoArchivo);
		}
		fclose(nuevoArchivo);

	}

	free(datos);
}

void Disco::readBlock(char* datos,int cantidad,int idBloque){

	int numeroDisco = findDisco(idBloque,numeroDiscos);
	int numeroBloque = findSectorDelDisco(idBloque,numeroBloque);

	// Envio un msg para que el disco que necesito espere los datos

	tipoMensaje msg = download;
	MPI_Send(&msg, sizeof(tipoMensaje), MPI_BYTE , numeroDisco +1, 0, MPI_COMM_WORLD);

	// Envio numeroDisco, cantidad, numeroBloque

	MPI_Send(&numeroDisco, sizeof(int), MPI_BYTE , numeroDisco +1, 0, MPI_COMM_WORLD);
	MPI_Send(&cantidad, sizeof(int), MPI_BYTE , numeroDisco +1, 0, MPI_COMM_WORLD);
	MPI_Send(&numeroBloque, sizeof(int), MPI_BYTE , numeroDisco +1, 0, MPI_COMM_WORLD);

	// Recibo datos

	MPI_Recv(datos, sizeof(char) * BLOQUE, MPI_BYTE, numeroDisco +1, MPI_ANY_TAG, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

}

int Disco::findDisco(int idBloque,int numeroDiscos){

	return idBloque%numeroDiscos;

}

int Disco::findSectorDelDisco(int idBloque,int numeroDiscos){

	return idBloque/numeroDiscos;
}

void Disco::format(int numeroDiscos,int size){

	cout << "Formateo los discos" << endl;

	this->numeroDiscos = numeroDiscos;

	size = size*1000-1;

	for(int i=0;i<numeroDiscos;i++){

		MPI_Send(&size, sizeof(int), MPI_BYTE , i+1, 0, MPI_COMM_WORLD);
		MPI_Send(&i, sizeof(int), MPI_BYTE , i+1, 0, MPI_COMM_WORLD);

	}

	FILE* sectoresLibres = fopen("sectoreslibres.dat","w");
	bool booleano = true;
	for(int i=0;i<=size*numeroDiscos;i++) {
		fwrite(&booleano, sizeof(bool), 1, sectoresLibres);
	}
	fclose(sectoresLibres);
}




































