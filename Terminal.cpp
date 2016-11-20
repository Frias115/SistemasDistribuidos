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

	int sizeNodoLength=sizeof(int);
	int sizeNodoFile = elArbol->directorioActual->sizeNodo;

	int bloquesUsadosLength = elArbol->directorioActual->bloquesUsados->size();

	int bloqueUsadoLength = sizeof(int);
	int bloqueUsadoFile;

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

	//Size de sizeNodo y sizeNodo
	fwrite(&sizeNodoLength,sizeof(int),1,arbolBinario);
	fwrite((const void*)&sizeNodoFile,sizeof(char),sizeNodoLength,arbolBinario);

	//Size de bloquesUsados y bloquesUsados
	fwrite(&bloquesUsadosLength,sizeof(int),1,arbolBinario);
	if(bloquesUsadosLength>0){

		for(std::list<int>::iterator i = elArbol->directorioActual->bloquesUsados->begin(); i != elArbol->directorioActual->bloquesUsados->end(); i++){

			fwrite(&bloqueUsadoLength,sizeof(int),1,arbolBinario);
			bloqueUsadoFile = (*i);
			fwrite((const void*)&bloqueUsadoFile,sizeof(char),bloqueUsadoLength,arbolBinario);

		}
	}

	//Size de numero de hijos
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

	int sizeNodoLength=sizeof(int);
	int sizeNodoFile = nodo->sizeNodo;

	int bloquesUsadosLength = nodo->bloquesUsados->size();

	int bloqueUsadoLength = sizeof(int);
	int bloqueUsadoFile;

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

	//Size de sizeNodo y sizeNodo
	fwrite(&sizeNodoLength,sizeof(int),1,arbolBinario);
	fwrite((const void*)&sizeNodoFile,sizeof(char),sizeNodoLength,arbolBinario);

	//Size de bloquesUsados y bloquesUsados
	fwrite(&bloquesUsadosLength,sizeof(int),1,arbolBinario);
	if(bloquesUsadosLength>0){

		for(std::list<int>::iterator i = nodo->bloquesUsados->begin(); i != nodo->bloquesUsados->end(); i++){

			fwrite(&bloqueUsadoLength,sizeof(int),1,arbolBinario);
			bloqueUsadoFile = (*i);
			fwrite((const void*)&bloqueUsadoFile,sizeof(char),bloqueUsadoLength,arbolBinario);

		}
	}

	//Size de numero de hijos
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

	if(elArbol->findChild(nombreArchivo)!=NULL){

		Nodo* aux = elArbol->findChild(nombreArchivo);
		disco->readFile(aux);

	}


}

//Upload y download aplicar el disco, es la segunda parte e implemntar el disco, ver la hoja que nos hizo Marcos
























