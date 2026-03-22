#pragma once

#include <iostream>
#include "../models/orden.h"
#include "../models/producto.h"
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;

nlohmann::json mostrarOrdenes();
void crearOrden(int numero_mesa, const std::vector<std::pair<std::string, int>>& lista_productos);
void modificarOrden(int id_orden, const std::vector<std::pair<std::string, int>>& lista_productos);
nlohmann::json mostrarProductos();