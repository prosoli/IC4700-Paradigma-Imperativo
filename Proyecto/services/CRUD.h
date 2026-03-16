#pragma once

#include <iostream>
#include "../utils/Auxiliares.h"

typedef struct ElementoLista{
    void* Informacion;
    OperacionesStructs Operaciones;
    ElementoLista* Siguiente = NULL;
}*PtrElemento;

PtrElemento buscarElemento(PtrElemento& lista, int indice);

//Operaciones del CRUD

//Crear (C)
void insertarElemento(PtrElemento& lista, OperacionesStructs operaciones);

//Leer (R)
void leerElementos(PtrElemento& lista);

//Actualizar (U)
void actualizarElemento(PtrElemento& lista);

//Eliminar (D)
void eliminarElemento(PtrElemento& lista);
//

//Función para eliminar una lista por completo
void eliminarLista(PtrElemento& lista);