#pragma once
#include <nlohmann/json.hpp>


void mostrarMenu(PtrElemento& ordenes, PtrElemento& productos);
void mostrarCrearOrdenMenu(PtrElemento& ordenes, PtrElemento& productos);
void mostrarModificarOrdenMenu(PtrElemento& ordenes, PtrElemento& productos);
void mostrarOrdenesMenu();
void mostrarProductosMenu();
void mistrarMesasDisponible();