#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "../utils/Auxiliares.h"
#include "../../models/producto.h"
using namespace std;

PtrElemento buscarElemento(PtrElemento& lista, int indice){
    PtrElemento Actual = lista;
    int contador = 1;
    bool encontrado = false;
    while (!encontrado == true && Actual != NULL){
        if (contador == indice){
            encontrado = true;
        } else {
            Actual = Actual->Siguiente;
            contador++;
        }
    }
    return Actual;
}

PtrElemento buscarElementoNombre(PtrElemento& lista, const std::string& nombre){
    PtrElemento actual = lista;
    while (actual != NULL){
        PtrProducto producto = static_cast<PtrProducto>(actual->Informacion);
        if (producto != NULL && std::strcmp(producto->Nombre, nombre.c_str()) == 0){
            return actual;
        }
        actual = actual->Siguiente;
    }
    return NULL;
}

//Operaciones del CRUD

//Crear (C)
void insertarElemento(PtrElemento& lista, OperacionesStructs operaciones, void** datos){
    //Crear elemento
    PtrElemento elemento = new(ElementoLista);
    elemento->Operaciones = operaciones;
    elemento->Informacion = operaciones.creacion(datos);
    //Insertar elemento en la lista
    PtrElemento Auxiliar = lista;
    if (Auxiliar != NULL)
    {
        while (Auxiliar->Siguiente != NULL)
        {
            Auxiliar = Auxiliar->Siguiente;
        }
        Auxiliar->Siguiente = elemento;
    }
    else
    {
        lista = elemento;
    }
}

//Leer (R)
void leerElementos(PtrElemento& lista){
    if (lista == NULL){
        cout<<"No hay elementos que mostrar."<<endl;
    } else {
        int indice = 1;
        PtrElemento Actual = lista;
        while (Actual != NULL){
            cout<<indice<<". ";
            Actual->Operaciones.listado(Actual->Informacion);
            Actual = Actual->Siguiente;
            indice++;
        }
        cout << endl;
    }
}

//Actualizar (U)
void actualizarElemento(PtrElemento& elemento, void** datos){
    elemento->Operaciones.actualizacion(elemento->Informacion, datos);
}

//Eliminar (D)
void eliminarElemento(PtrElemento& lista, int indiceElemento){
    PtrElemento elemento = NULL;
    PtrElemento elementoAnterior = NULL;
    
    if (indiceElemento != 1){
        elementoAnterior = buscarElemento(lista, (indiceElemento - 1));
        if  (elementoAnterior != NULL){
            elemento = elementoAnterior->Siguiente;
        }
    } else {
        elemento = lista;
    }
    if (elemento == NULL){
        cout<<"Elemento no encontrado."<<endl;
    } else {
        if (elemento == lista) {
            lista = elemento->Siguiente;
            elemento->Operaciones.eliminacion(elemento->Informacion);
            delete(elemento);
            elemento = NULL;
        } else {
            elementoAnterior->Siguiente = elemento->Siguiente;
            elemento->Operaciones.eliminacion(elemento->Informacion);
            delete(elemento);
            elemento = NULL;
        }
    }
}
//

//Función para eliminar una lista por completo
void eliminarLista(PtrElemento& lista){
    PtrElemento Auxiliar = lista;
    while (Auxiliar != NULL){
        lista = lista->Siguiente;
        Auxiliar->Operaciones.eliminacion(Auxiliar->Informacion);
        delete(Auxiliar);
        Auxiliar = lista;
    }
}

