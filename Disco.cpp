#include "Disco.h"
#include "Nodo.h"

// 1000 BYTES
#define BLOQUE 1000

void Disco::buscarSectoresLibres(int numeroBloquesNecesarios,Nodo* nodo) {

	bool bloqueValido;
	bool ocupate = false;
	int counter = 0;
	FILE* sectoresLibres = fopen("sectoreslibres1.dat","r+");
	for(int i=0;i<32000;i++){

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

	cout << archivo << endl;

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

	FILE* miDisco = fopen("disco1.dat","r+");
	fseek(miDisco,idBloque*BLOQUE,SEEK_SET);

	fwrite(datos,sizeof(char),cantidad,miDisco);

	fclose(miDisco);
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

	FILE* miDisco = fopen("disco1.dat","r+");
	fseek(miDisco,idBloque*BLOQUE,SEEK_SET);

	fread(datos,sizeof(char),cantidad,miDisco);
	fclose(miDisco);
}



































