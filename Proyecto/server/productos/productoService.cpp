#include <iostream>
#include <cstring>
#include "../../models/producto.h"
#include "productoService.h"
// #include "../models/elementolista.h"
#include "../utils/Auxiliares.h"

using namespace std;

void* crearProducto(void** datos){
    PtrProducto producto = new(Producto);
    strcpy(producto->Nombre, (char*)datos[0]);
    producto->Precio = *(float*)datos[1];
    return (void*)producto;
}

void actualizarProducto(void* informacion, void** datos){
    PtrProducto producto = static_cast<PtrProducto>(informacion);
    strcpy(producto->Nombre, (char*)datos[0]);
    producto->Precio = *(float*)datos[1];
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

void mostrarProductos(void){
    cout << endl;
    cout << "======= Productos registrados =======" << endl;
}

//Operaciones para trabajar con productos
OperacionesStructs OperacionesProductos = {crearProducto, leerProducto, actualizarProducto, eliminarProducto};
