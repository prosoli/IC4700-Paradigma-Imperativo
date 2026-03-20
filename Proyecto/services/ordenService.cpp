
#include <iostream>
#include "../models/orden.h"
#include "ordenService.h"
#include "../utils/Auxiliares.h"
#include "../services/CRUD.h"

using namespace std;

//lista de ordenes
PtrElemento ListaOrdenes = NULL;

//Operaciones para trabajar con ordenes
OperacionesStructs OperacionesOrdenes = {
    crearOrden,
    leerOrden,
    actualizarOrden,
    eliminarOrden
};

//Agrega nueva orden usando el CRUD
void agregarOrden(){
    insertarElemento(ListaOrdenes, OperacionesOrdenes);
}

//Muestra las órdenes usando el CRUD
void mostrarOrdenes(){
    cout << endl;
    cout << "======= Órdenes registradas =======" << endl;
    leerElementos(ListaOrdenes);
    cout << endl;
}

