#include <iostream>
#include "../models/orden.h"
#include "ordenService.h"
#include "../models/operacionesstructs.h"
#include "../utils/Auxiliares.h"

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


void* crearOrden(void){
    PtrOrden orden = new(Orden);

    //Numero de orden
    static int contador = 1;
    orden->id = contador++;

    cout<<"Ingrese el producto a pedir:"<<endl;
    cin>>orden->producto;

    cout<<"Ingrese la cantidad:"<<endl;
    cin>>orden->cantidad;

    cout<<"Ingrese el numero de mesa:"<<endl;
    cin>>orden->id_mesa;

    orden->estado = true; //Orden con estadi pendiente al entrar

    return (void*)orden;
}

void leerOrden(void* informacion){
    PtrOrden orden = static_cast<PtrOrden>(informacion);
    cout<<"Numero de orden:"<< orden->id << endl;
    cout<<"Numero mesa:"<< orden->id_mesa << endl;
    cout<<"Producto solicitado:"<< orden->producto << endl;
    cout<<"Cantidad solicitada:"<< orden->cantidad << endl;
    cout<<"Estado de la orden:"<< (orden->estado ? "Pendiente" : "Completada") << endl;
}

void actualizarOrden(void* informacion){
    // pend
}

void eliminarOrden(void* informacion){
    // pend
}

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

