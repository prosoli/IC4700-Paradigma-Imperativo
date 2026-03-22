#include <nlohmann/json.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "cliente_socket.h"
#include "../models/elementolista.h"
#include "../models/messageCode.h"

using namespace std;

nlohmann::json mostrarOrdenes(){
    nlohmann::json json_msg = {
        {"Type", static_cast<unsigned char>(MessageCode::ViewOrders)}
    };
    std::string mensaje = json_msg.dump();
    std::string respuesta = enviarSolicitudAlServidor(mensaje.c_str());
    nlohmann::json json_respuesta = nlohmann::json::parse(respuesta);
    return json_respuesta;
}

nlohmann::json mostrarProductos(){
    nlohmann::json json_msg = {
        {"Type", static_cast<unsigned char>(MessageCode::ViewProducts)}
    };
    std::string mensaje = json_msg.dump();
    std::string respuesta = enviarSolicitudAlServidor(mensaje.c_str());
    nlohmann::json json_respuesta = nlohmann::json::parse(respuesta);
    return json_respuesta;
}

void crearOrden(int numero_mesa, const std::vector<std::pair<std::string, int>>& lista_productos){

    nlohmann::json json_msg = {
        {"Type", static_cast<unsigned char>(MessageCode::CreateOrder)},
        {"Mesa", numero_mesa},
        {"Productos", lista_productos}
    };

    std::string mensaje = json_msg.dump();
    // Envía 'mensaje' por el socket
    // --- Comunicación con el servidor ---
    enviarSolicitudAlServidor(mensaje.c_str());
}


void modificarOrden(int id_orden, const std::vector<std::pair<std::string, int>>& lista_productos){

    nlohmann::json json_msg = {
        {"Type", static_cast<unsigned char>(MessageCode::ModifyOrder)},
        {"IdOrden", id_orden},
        {"Productos", lista_productos}
    };

    std::string mensaje = json_msg.dump();
    // Envía 'mensaje' por el socket
    // --- Comunicación con el servidor ---
    enviarSolicitudAlServidor(mensaje.c_str());
}

