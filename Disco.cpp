#include "Disco.h"
#include "Nodo.h"

//MODIFICAR EL SECTORESLIBRES PONIENDO A FALSE LOS SECTORES YA OCUPADOS
void Disco::buscarSectoresLibres(int numeroBloquesNecesarios,Nodo* nodo) {

    bool bloqueValido;
    int counter = 0;
    FILE* sectoresLibres = fopen("sectoreslibres1.dat","r");
    for(int i=0;i<32000;i++){

        fread(&bloqueValido,sizeof(bool),1,sectoresLibres);
        if(bloqueValido){
            nodo->bloquesUsados->push_back(i);
            counter++;
            if(counter==numeroBloquesNecesarios)return;
        }
    }
}

void Disco::writeFile(string archivo, Nodo *nodo) {


    char* buffer[nodo->sizeNodo];
    FILE* miArchivo = fopen(archivo.c_str(),"r");
    fread(&buffer,sizeof(char),nodo->sizeNodo,miArchivo);
    fclose(miArchivo);
    int j=0;
    for(list<int>::iterator i = nodo->bloquesUsados->begin(); i != nodo->bloquesUsados->end(); i++,j+=1000){

        writeBlock(buffer[j],(*i));

    }

}
//QUEDA RELLENAR CON 0 EL RESTO DEL BLOQUE SI NO SE COMPLETA
void Disco::writeBlock(char* datos, int idBloque) {

    FILE* miDisco = fopen("disco1.dat","w");
    fseek(miDisco,idBloque*1000-1,SEEK_SET);
    fwrite(datos,sizeof(char),1000,miDisco);
    fclose(miDisco);
}