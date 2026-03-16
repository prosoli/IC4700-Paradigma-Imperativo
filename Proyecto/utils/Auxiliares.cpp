#pragma once

#include <iostream>
#include <stdlib.h>
#include "../models/producto.h"
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

//