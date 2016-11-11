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


    char* buffer[nodo->sizeNodo];
    for(int i=0;i<nodo->sizeNodo;i++){
        buffer[i] = 0;
    }
    FILE* miArchivo = fopen(archivo.c_str(),"r");
    fread(&buffer,sizeof(char),nodo->sizeNodo,miArchivo);
    fclose(miArchivo);
    int j=0;
    for(list<int>::iterator i = nodo->bloquesUsados->begin(); i != nodo->bloquesUsados->end(); i++,j+=1000){

        writeBlock(buffer[j],(*i));

    }

}

void Disco::writeBlock(char* datos, int idBloque) {

    FILE* miDisco = fopen("disco1.dat","w");
    fseek(miDisco,idBloque*1000,SEEK_SET);
    fwrite(datos,sizeof(char),1000,miDisco);
    fclose(miDisco);
}

































