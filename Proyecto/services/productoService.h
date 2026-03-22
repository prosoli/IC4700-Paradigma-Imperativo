#pragma once

#include "../models/producto.h"
#include "../models/operacionesstructs.h"

void* crearProducto(void);

void actualizarProducto(void* informacion);

void leerProducto(void* informacion);

void eliminarProducto(void* informacion);

void mostrarProductos(void);

extern OperacionesStructs OperacionesProductos;