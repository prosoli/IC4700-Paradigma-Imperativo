#pragma once
#include "../../models/orden.h"
#include "../../models/elementolista.h"
#include <string>
#include <utility>
#include <vector>

extern PtrElemento ListaProductos;
extern PtrElemento ListaOrdenes;

PtrOrden buscarOrdenPorId(int id);

PtrOrden crearOrden(int numeroMesa, const std::vector<std::pair<std::string, int>>& listaProductos);

void leerOrden(void* informacion);

void actualizarOrden(void* informacion);

void eliminarOrden(void* informacion);

void mostrarOrdenes();

void mostrarOrdenesPendientes();

void agregarOrden();

bool marcarOrdenCompletada(int idOrden);

void modificarOrdenesPendientes();

void modificarOrden(int idOrden, const std::vector<std::pair<std::string, int>>& productosDelta);

extern OperacionesStructs OperacionesOrdenes;
