#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <sys/socket.h>

#include "../models/elementolista.h"
#include "server.h"
#include "server_menus.h"
#include "server_socket.h"
#include "server_service.h"

using namespace std;

PtrElemento ListaProductos = NULL;
PtrElemento ListaOrdenes = NULL;

void atenderCliente(int clientSocket) {
    std::string mensaje = leerSolicitudCliente(clientSocket);
    std::string respuesta = procesarMensajeServidor(mensaje);
    enviarRespuestaCliente(clientSocket, respuesta);
    cerrarSocketServidor(clientSocket);
}

void escucharClientes(int serverSocket, std::atomic<bool>& servidorActivo) {
    while (servidorActivo) {
        int clientSocket = aceptarCliente(serverSocket);
        if (clientSocket < 0) {
            if (!servidorActivo) {
                break;
            }
            continue;
        }

        atenderCliente(clientSocket);
    }
}

int main() {
    int serverSocket = crearSocketServidor(8080);
    if (serverSocket < 0) {
        return 1;
    }

    std::atomic<bool> servidorActivo(true);
    std::thread hiloServidor(escucharClientes, serverSocket, std::ref(servidorActivo));

    cout << "Servidor escuchando clientes en el puerto 8080..." << endl;
    cout << "Mostrando menu principal del servidor:" << endl;

    menuListas();

    servidorActivo = false;
    cerrarSocketServidor(serverSocket);
    hiloServidor.join();

    cout << "Servidor detenido." << endl;
    return 0;
}

