#pragma once
#include "../../models/orden.h"
#include "../../models/elementolista.h"

extern PtrElemento ListaProductos;
extern PtrElemento ListaOrdenes;

void* crearOrden(void);

void leerOrden(void* informacion);

void actualizarOrden(void* informacion);

void eliminarOrden(void* informacion);

void mostrarOrdenes();

void mostrarOrdenesPendientes();

void agregarOrden();

extern OperacionesStructs OperacionesOrdenes;
