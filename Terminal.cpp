#include "Terminal.h"
#include <fstream>


void Terminal::ls(Arbol* elArbol){

    if(!elArbol->directorioActual->hijos->empty()){
        for(std::list<Nodo*>::iterator i = elArbol->directorioActual->hijos->begin(); i != elArbol->directorioActual->hijos->end(); i++){

            cout<<(*i)->nombre;
            if((*i)->esDirectorio) cout<<"/";
            cout<<"      ";

        }
        cout<<endl;
    }

}

void Terminal::pwd(Arbol* elArbol) {

    list<string> *ruta = new list<string>();
    Nodo* aux = elArbol->directorioActual;
    while(elArbol->directorioActual!=NULL){
        ruta->push_front(elArbol->directorioActual->nombre);
        elArbol->directorioActual = elArbol->directorioActual->padre;
    }


    for(std::list<string>::iterator i = ruta->begin(); i != ruta->end(); i++) {

        cout<<(*i)<<"/";

    }

    cout<<endl;

    elArbol->directorioActual = aux;


}

void Terminal::cd(Arbol* elArbol, string nombreNuevoDirectorio){

    if(elArbol->directorioActual->nombre.compare("root")!=0){

        if(nombreNuevoDirectorio.compare("..")==0){
            elArbol->directorioActual = elArbol->directorioActual->padre;
            return;
        }

        if(nombreNuevoDirectorio.compare("/")==0){

            elArbol->directorioActual = elArbol->root;
            return;
        }

    }


    if(elArbol->findChild(nombreNuevoDirectorio) !=NULL && elArbol->findChild(nombreNuevoDirectorio)->esDirectorio){
        Nodo* aux = elArbol->findChild(nombreNuevoDirectorio);
        elArbol->directorioActual = aux;
        return;

    }else if(elArbol->findChild(nombreNuevoDirectorio) !=NULL && !elArbol->findChild(nombreNuevoDirectorio)->esDirectorio){

        cout<<"cd: "<<nombreNuevoDirectorio<<": Not a directory"<<endl;
        return;

    }else if(elArbol->findChild(nombreNuevoDirectorio) ==NULL){

        cout<<"cd: "<<nombreNuevoDirectorio<<": No such file or directory"<<endl;
        return;

    }





}

void Terminal::mv(string nuevoNombreNodo, string nombreNodo, Arbol* elArbol) {


    if(elArbol->findChild(nombreNodo) != NULL){

        elArbol->updateChild(nombreNodo,nuevoNombreNodo);

    }else{
        cout<<"El nodo a modificar no existe."<<endl;
    }


}

void Terminal::cp(string origen, string destino,Arbol* elArbol) {

    //Caso directorio - directorio
    /*if(elArbol->findChild(origen)!=NULL && elArbol->findChild(destino)!=NULL && elArbol->findChild(origen)->esDirectorio && elArbol->findChild(destino)->esDirectorio){

        Nodo* aux = elArbol->findChild(origen);
        aux->padre = elArbol->findChild(destino);
        elArbol->findChild(destino)->hijos->push_back(aux);

    }*/

}

void Terminal::mkdir(string nombreNuevoDirectorio,Arbol* elArbol) {

    if(elArbol->findChild(nombreNuevoDirectorio) == NULL || (elArbol->findChild(nombreNuevoDirectorio) !=NULL && !elArbol->findChild(nombreNuevoDirectorio)->esDirectorio)){

        elArbol->addChild(nombreNuevoDirectorio,true);

    }

}

void Terminal::rmdir(string directorioAEliminar, Arbol *elArbol) {

    if(elArbol->findChild(directorioAEliminar) !=NULL && elArbol->findChild(directorioAEliminar)->esDirectorio && elArbol->findChild(directorioAEliminar)->hijos->empty()){
        elArbol->removeChild(directorioAEliminar);
    }
}

void Terminal::rm(string ficheroAEliminar, Arbol *elArbol) {

    if(elArbol->findChild(ficheroAEliminar) !=NULL && !elArbol->findChild(ficheroAEliminar)->esDirectorio){
        elArbol->removeChild(ficheroAEliminar);
    }
}

void Terminal::exit(Arbol *elArbol) {

    //ofstream arbolBinario("arbolBinario.bin", ios::out | ios::binary | ios::app);
    // arbolBinario.write(reinterpret_cast<const char*>(elArbol->directorioActual), sizeof (Nodo));
	/*
    int nameLength=elArbol->directorioActual->nombre.size();
    arbolBinario.write((char*)&(nameLength), sizeof (int));
    arbolBinario.write((char*)(elArbol->directorioActual->nombre.c_str()), elArbol->directorioActual->nombre.size());

    arbolBinario.close();*/
    elArbol->directorioActual = elArbol->root;
    int nameLength=elArbol->directorioActual->nombre.size();
    const char* filename=elArbol->directorioActual->nombre.c_str();

    int idLength=sizeof(int);
    int idFile= elArbol->directorioActual->id;

    int nivelLength = sizeof(int);
    int nivelFile = elArbol->directorioActual->nivel;

    int esDirectorioLength = sizeof(bool);
    bool esDirectorioFile = elArbol->directorioActual->esDirectorio;

    int nhijos=elArbol->directorioActual->hijos->size();

    FILE* arbolBinario=fopen("arbolBinario.bin", "w");

    //Size del nombre y nombre
    fwrite(&nameLength,sizeof(int),1,arbolBinario);
    fwrite(filename,sizeof(char),nameLength,arbolBinario);

    //Size de id e id
    fwrite(&idLength,sizeof(int),1,arbolBinario);
    fwrite((const void*)&idFile,sizeof(char),idLength,arbolBinario);

    //Size de nivel y nivel
    fwrite(&nivelLength,sizeof(int),1,arbolBinario);
    fwrite((const void*)&nivelFile,sizeof(char),nivelLength,arbolBinario);

    //Size de esDirectorio y esDirectorio
    fwrite(&esDirectorioLength,sizeof(int),1,arbolBinario);
    fwrite((const void*)&esDirectorioFile,sizeof(char),esDirectorioLength,arbolBinario);

    fwrite(&nhijos,sizeof(int),1,arbolBinario);
    fclose(arbolBinario);
    for(std::list<Nodo*>::iterator i = elArbol->directorioActual->hijos->begin(); i != elArbol->directorioActual->hijos->end(); i++){

        escribeNodoRecursiva((*i));

    }



}

void Terminal::escribeNodoRecursiva(Nodo* nodo) {

    int nameLength=nodo->nombre.size();
    const char* filename=nodo->nombre.c_str();

    int idLength=sizeof(int);
    int idFile= nodo->id;

    int nivelLength = sizeof(int);
    int nivelFile = nodo->nivel;

    int esDirectorioLength = sizeof(bool);
    bool esDirectorioFile = nodo->esDirectorio;

    int nhijos=nodo->hijos->size();

    FILE* arbolBinario=fopen("arbolBinario.bin", "a");

    //Size del nombre y nombre
    fwrite(&nameLength,sizeof(int),1,arbolBinario);
    fwrite(filename,sizeof(char),nameLength,arbolBinario);

    //Size de id e id
    fwrite(&idLength,sizeof(int),1,arbolBinario);
    fwrite((const void*)&idFile,sizeof(char),idLength,arbolBinario);

    //Size de nivel y nivel
    fwrite(&nivelLength,sizeof(int),1,arbolBinario);
    fwrite((const void*)&nivelFile,sizeof(char),nivelLength,arbolBinario);

    //Size de esDirectorio y esDirectorio
    fwrite(&esDirectorioLength,sizeof(int),1,arbolBinario);
    fwrite((const void*)&esDirectorioFile,sizeof(char),esDirectorioLength,arbolBinario);

    fwrite(&nhijos,sizeof(int),1,arbolBinario);
    fclose(arbolBinario);

    for(list<Nodo*>::iterator i = nodo->hijos->begin(); i != nodo->hijos->end(); i++){

        escribeNodoRecursiva((*i));

    }

}

Arbol* Terminal::cargar() {


    FILE* arbolBinario=fopen("arbolBinario.bin", "r");
    Arbol* arbol = new Arbol();
    //Size del nombre y nombre
    int nameLength;
    fread(&nameLength,sizeof(int),1,arbolBinario);
    char nombre[nameLength + 1];
    nombre[nameLength] = '\0';
    fread(nombre,sizeof(char),nameLength,arbolBinario);
    arbol->directorioActual->nombre = nombre;
    //Size de id e id
    int idLength;
    fread(&idLength,sizeof(int),1,arbolBinario);
    fread(&arbol->directorioActual->id,sizeof(char),idLength,arbolBinario);

    //Size de nivel y nivel
    int nivelLength;
    fread(&nivelLength,sizeof(int),1,arbolBinario);
    fread(&arbol->directorioActual->nivel,sizeof(char),nivelLength,arbolBinario);

    //Size de esDirectorio y esDirectorio
    int esDirectorioLength;
    fread(&esDirectorioLength,sizeof(int),1,arbolBinario);
    fread(&arbol->directorioActual->esDirectorio,sizeof(char),esDirectorioLength,arbolBinario);

    int nhijos;
    fread(&nhijos,sizeof(int),1,arbolBinario);

    for(int i=0;i<nhijos; i++){

        arbol->directorioActual->hijos->push_back(cargarNodoRecursiva(arbol, arbolBinario));

    }
    fclose(arbolBinario);
    arbol->directorioActual = arbol->root;

    return arbol;

}

Nodo* Terminal::cargarNodoRecursiva(Arbol *arbol, FILE* arbolBinario) {

	arbol->ultimoID++;
	arbol->numeroNodos++;


    Nodo* nodo = new Nodo();
    Nodo* nodoAux = arbol->directorioActual;

    nodo->padre = arbol->directorioActual;

    //Size del nombre y nombre
    int nameLength;
    fread(&nameLength,sizeof(int),1,arbolBinario);
    char nom[nameLength + 1];
    nom[nameLength] = '\0';
    fread(nom,sizeof(char),nameLength,arbolBinario);
    nodo->nombre = nom;

    //Size de id e id
    int idLength;
    fread(&idLength,sizeof(int),1,arbolBinario);
    fread(&nodo->id,sizeof(char),idLength,arbolBinario);

    //Size de nivel y nivel
    int nivelLength;
    fread(&nivelLength,sizeof(int),1,arbolBinario);
    fread(&nodo->nivel,sizeof(char),nivelLength,arbolBinario);

    //Size de esDirectorio y esDirectorio
    int esDirectorioLength;
    fread(&esDirectorioLength,sizeof(int),1,arbolBinario);
    fread(&nodo->esDirectorio,sizeof(char),esDirectorioLength,arbolBinario);

    //Si el nodo es un directorio cambiamos el directorio actual del arbol
    if(nodo->esDirectorio) arbol->directorioActual = nodo;

    int nhijos;
    fread(&nhijos,sizeof(int),1,arbolBinario);
    for(int i=0;i<nhijos; i++){

        arbol->directorioActual->hijos->push_back(cargarNodoRecursiva(arbol, arbolBinario));

    }

    arbol->directorioActual = nodoAux;

    return nodo;

}

void Terminal::format(int size){

    char inicializar = '0';
    size = size*1000-1;
	FILE* disco1=fopen("disco1.dat", "w");
    fseek(disco1,size,SEEK_SET);
    fwrite(&inicializar,sizeof(char),1,disco1);
    fclose(disco1);

    FILE* sectoresLibres1 = fopen("sectoreslibres1.dat","w");
    bool booleano = true;
    for(int i=0;i<=size;i++) {
        fwrite(&booleano, sizeof(bool), 1, sectoresLibres1);
    }
    fclose(sectoresLibres1);
}

void Terminal::upload(Arbol* elArbol,string nombreArchivo,Disco* disco) {

	FILE* nuevoArchivo=fopen(nombreArchivo.c_str(), "r+");

    if(nuevoArchivo != NULL) {
        //Añadiendo nuevo nodo
        elArbol->addChild(nombreArchivo, false);
        Nodo *aux = elArbol->findChild(nombreArchivo);

        // get length of file:
        fseek (nuevoArchivo, 0, SEEK_END);
        int size = ftell (nuevoArchivo);
        fclose (nuevoArchivo);

        aux->sizeNodo = size;

        int numeroBloquesNecesarios;
        float auxBloques;
        //Calcular numero de bloques
        if(aux->sizeNodo >= 1000){
        	auxBloques = ceil(aux->sizeNodo / 1000.0f);
        	numeroBloquesNecesarios = auxBloques;
        } else {
        	numeroBloquesNecesarios = 1;
        }
        //Buscar los sectores libres
        disco->buscarSectoresLibres(numeroBloquesNecesarios, aux);

        disco->writeFile(nombreArchivo, aux);
    }

}

void Terminal::download(Arbol *elArbol, string nombreArchivo, Disco *disco) {









}

//Upload y download aplicar el disco, es la segunda parte e implemntar el disco, ver la hoja que nos hizo Marcos


//Ejemplo mpi

/* prueba1.c
	#include <stdio.h>
	#include <stdlib.h>

	int main()
	{

		char comando[20];
		scanf("%s",comando); //master
		printf("%s\n",comando); //slaver

		switch(comando[0])
		{

			case 'l':
				printf("pulsado l\n");
			break;

			case 'b':
				printf("pulsado b\n");
			break;

			default:

			break;
		};

		return 0;
	}
 */


/* mainMPI.cpp

 	#include <stdio.h>
	#include <stdlib.h>
	#include "mpi.h"

	typedef enum tipomensaje
	{
		pulsadol = 0,
		pulsadob,
		format,
		mkdir,
		pulsadoerror

	}tipomensaje;

	void enviaMensaje(int numslaves, tipomensaje msg)
	{

			for(int i=1; i < numslaves; i++)
			{
				//MPI_Send(const void *buf, int count, MPI_Datatype datatype, int des, int tag, MPI_Comm comm);
				MPI_Send(&msg, sizeof(tipomensaje), MPI_BYTE , i, 0, MPI_COMM_WORLD);

			}

	}

	void enviaMensajeFormat(int numslaves, tipomensaje msg, int formatSize)
	{
			for(int i=1; i < numslaves; i++)
			{
				//MPI_Send(const void *buf, int count, MPI_Datatype datatype, int des, int tag, MPI_Comm comm);
				MPI_Send(&msg, sizeof(tipomensaje), MPI_BYTE , i, 0, MPI_COMM_WORLD);
				MPI_Send(&formatSize, sizeof(int), MPI_BYTE , i, 0, MPI_COMM_WORLD);

			}

	}

	void enviaMensajeMkdir(int numslaves, tipomensaje msg, char* nombre, int tam)
	{
			for(int i=1; i < numslaves; i++)
			{
				//MPI_Send(const void *buf, int count, MPI_Datatype datatype, int des, int tag, MPI_Comm comm);
				MPI_Send(&msg, sizeof(tipomensaje), MPI_BYTE , i, 0, MPI_COMM_WORLD);
				MPI_Send(&tam, sizeof(int), MPI_BYTE , i, 0, MPI_COMM_WORLD);
				MPI_Send(nombre, sizeof(char)*tam, MPI_BYTE , i, 0, MPI_COMM_WORLD);
			}
	}


	void master(int numslaves)
	{
		tipomensaje msg;
		int salir = 0;
		int tam = 0;
		char* comando = new char[20]; // memoria dinamica, no estatica
		char* nombre = new char[20];
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


	}

	void slave()
	{

		MPI_Status status;
		int salir = 0;
		tipomensaje msg;
		int tam;

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
					printf("Recibido format: %d\n", tam);
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




	}

	int main(int argc, char** argv)
	{

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

 */





















