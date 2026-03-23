#include <iostream>
#include <unistd.h>
#include <string>

#include "../models/elementolista.h"
#include "server.h"
#include "server_socket.h"
#include "server_service.h"

using namespace std;

PtrElemento ListaProductos = NULL;
PtrElemento ListaOrdenes = NULL;

int main() {
    int serverSocket = crearSocketServidor(8080);
    if (serverSocket < 0) {
        return 1;
    }

    cout << "Servidor esperando clientes..." << endl;

    while(true) {
        int clientSocket = aceptarCliente(serverSocket);
        if (clientSocket < 0) {
            continue;
        }

        if(fork() == 0) { // proceso hijo
            cerrarSocketServidor(serverSocket);

            std::string mensaje = leerSolicitudCliente(clientSocket);
            std::string respuesta = procesarMensajeServidor(mensaje);
            enviarRespuestaCliente(clientSocket, respuesta);
            cerrarSocketServidor(clientSocket);
            return 0;
        }

        cerrarSocketServidor(clientSocket);
    }

    cerrarSocketServidor(serverSocket);
}

