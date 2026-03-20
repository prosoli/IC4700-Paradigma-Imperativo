#pragma once

typedef struct Orden   
{
    int id;
    char producto [50];
    int cantidad;
    int id_mesa;
    bool estado; // true: orden pendiente, false: orden lista
}*PtrOrden;


