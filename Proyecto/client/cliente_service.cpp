#include <nlohmann/json.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "cliente_socket.h"
#include "../models/elementolista.h"
#include "../models/messageCode.h"

using namespace std;

nlohmann::json mostrarMesas(){

    nlohmann::json json_msg = {
        {"Type", static_cast<unsigned char>(MessageCode::ViewTables)}
    };
    std::string mensaje = json_msg.dump(); // Convierte el objeto JSON a una cadena
    std::string respuesta = enviarSolicitudAlServidor(mensaje.c_str()); // Envía la cadena al servidor y recibe la respuesta
    nlohmann::json json_respuesta = nlohmann::json::parse(respuesta); // Parsea la respuesta del servidor de vuelta a un objeto JSON
    return json_respuesta; // Retorna el objeto JSON con la respuesta del servidor
}

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

nlohmann::json crearOrden(int numero_mesa, const std::vector<std::pair<std::string, int>>& lista_productos){

    nlohmann::json json_msg = {
        {"Type", static_cast<unsigned char>(MessageCode::CreateOrder)},
        {"Mesa", numero_mesa},
        {"Productos", lista_productos}
    };

    std::string mensaje = json_msg.dump();
    // --- Comunicación con el servidor ---
    std::string respuesta = enviarSolicitudAlServidor(mensaje.c_str());
    return nlohmann::json::parse(respuesta);
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

