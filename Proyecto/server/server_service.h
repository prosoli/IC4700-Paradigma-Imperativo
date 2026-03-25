#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>
#include "../models/elementolista.h"

bool parseCreateOrder(const nlohmann::json& json_msg, int& mesa, std::vector<std::pair<std::string, int>>& productos, std::string& error);

nlohmann::json createOrderHandler(const nlohmann::json& json_msg);

nlohmann::json productoAJson(void* informacion);

nlohmann::json generarListaProductos(PtrElemento lista);

std::string procesarMensajeServidor(const std::string& mensaje);
