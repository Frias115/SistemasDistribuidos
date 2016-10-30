#include "Terminal.h"


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

    ofstream arbolBinario("arbolBinario.bin", ios::out | ios::binary | ios::app);
    arbolBinario.write(reinterpret_cast<const char*>(elArbol->directorioActual), sizeof (Nodo));
    arbolBinario.close();

}



























