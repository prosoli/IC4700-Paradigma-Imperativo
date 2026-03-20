#pragma once

#include <iostream>
#include <stdlib.h>
#include "../models/producto.h"
#include "../models/orden.h"
#include "../utils/Auxiliares.h"
using namespace std;

//Operaciones para los productos

void* crearProducto(void){
    PtrProducto producto = new(Producto);
    cout<<"Ingrese el nombre del producto:"<<endl;
    cin>>producto->Nombre;
    cout<<"Ingrese el precio del producto:"<<endl;
    cin>>producto->Precio;
    return (void*)producto;
}

void actualizarProducto(void* informacion){
    PtrProducto producto = static_cast<PtrProducto>(informacion);
    cout<<"-Modificar el producto-"<<endl;
    cout<<"Ingrese el nuevo nombre:"<<endl;
    cin>>producto->Nombre;
    cout<<"Ingrese el nuevo precio:"<<endl;
    cin>>producto->Precio;
}

void leerProducto(void* informacion){
    PtrProducto producto = static_cast<PtrProducto>(informacion);
    cout<<producto->Nombre<<", CR"<<producto->Precio<<endl;
    producto = NULL;
}

void eliminarProducto(void* informacion){
    PtrProducto producto = static_cast<PtrProducto>(informacion);
    delete(producto);
}

//Operaciones para las ordenes

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