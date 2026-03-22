#pragma once

#include <iostream>
#include "../models/orden.h"
#include "../models/producto.h"
#include <vector>

using namespace std;

void mostrarOrdenes(PtrElemento ordenes);
void crearOrden(PtrElemento& ordenes, PtrElemento productos);
void modificarOrden(PtrElemento& ordenes, PtrElemento productos);