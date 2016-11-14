#include "Nodo.h"


Nodo::Nodo() {

    hijos = new list<Nodo*>();
    bloquesUsados = new list<int>();
    sizeNodo = 0;
}
