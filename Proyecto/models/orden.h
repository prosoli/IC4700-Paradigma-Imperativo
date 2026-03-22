#pragma once

#include "../models/elementolista.h"

typedef struct Orden   
{
    int id;
    PtrElemento productos = NULL; //Lista de productos en la orden
    int cantidad;
    int id_mesa;
    bool estado; // true: orden pendiente, false: orden lista
}*PtrOrden;


