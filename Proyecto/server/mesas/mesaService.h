#pragma once

#ifndef MESA_H
#define MESA_H

#include <vector>

int obtenerNumeroMesas();
std::vector<int> obtenerListaMesas();
void agregarMesa(int id);
void eliminarMesa(int id);
void actualizarListaMesas(const std::vector<int>& nuevaLista);
bool existeMesa(int id);

#endif
