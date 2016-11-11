#include "Disco.h"
#include "Nodo.h"

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


    char* buffer = (char*) calloc(nodo->sizeNodo, sizeof(char));

    FILE* miArchivo = fopen(archivo.c_str(),"r");
    fread(buffer,sizeof(char),nodo->sizeNodo,miArchivo);
    fclose(miArchivo);
    int cantidad = 0, counter = 0;
    for(list<int>::iterator i = nodo->bloquesUsados->begin(); i != nodo->bloquesUsados->end(); i++, counter++){

    	//El archivo ocupa un bloque o menos
    	if(nodo->sizeNodo <= 1000){
    		cantidad = nodo->sizeNodo;
    		writeBlock(buffer,cantidad,(*i));
    		free(buffer);
    		return;
    	}

    	//El archivo ocupa mas de un bloque
    	if(nodo->sizeNodo - (1000 * counter) > 1000){
    		writeBlock(buffer,1000,(*i));
    	} else {
    		cantidad = nodo->sizeNodo - (1000 * counter);
    		writeBlock(buffer,cantidad,(*i));
    	}

    }
    free(buffer);
}

void Disco::writeBlock(char* datos, int cantidad, int idBloque) {

    FILE* miDisco = fopen("disco1.dat","r+");
    fseek(miDisco,idBloque*1000,SEEK_SET);

    char* aux = (char*) calloc(cantidad, sizeof(char));

    for(int i = 0; i < cantidad; i++){
    	aux[i] = datos[idBloque*1000+i];
    }

    fwrite(aux,sizeof(char),cantidad,miDisco);

    fclose(miDisco);
    free(aux);
}

































