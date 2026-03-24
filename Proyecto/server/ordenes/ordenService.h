#pragma once
#include "../../models/orden.h"
#include "../../models/elementolista.h"
#include <string>
#include <utility>
#include <vector>

extern PtrElemento ListaProductos;
extern PtrElemento ListaOrdenes;

void* crearOrden(void);
PtrOrden crearOrden(int numeroMesa, const std::vector<std::pair<std::string, int>>& listaProductos);

void leerOrden(void* informacion);

void actualizarOrden(void* informacion);

void eliminarOrden(void* informacion);

void mostrarOrdenes();

void mostrarOrdenesPendientes();

void agregarOrden();

bool marcarOrdenCompletada(int idOrden);

extern OperacionesStructs OperacionesOrdenes;
