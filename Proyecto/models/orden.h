#pragma once

#include <vector>
#include "producto.h"

typedef struct ProductoEscogido {
    PtrProducto producto = NULL;
    int cantidad = 0;
} DetalleOrden;

typedef struct Orden   
{
    int id;
    std::vector<ProductoEscogido> detalles;
    int id_mesa;
    bool estado; // true: orden pendiente, false: orden lista
}*PtrOrden;


