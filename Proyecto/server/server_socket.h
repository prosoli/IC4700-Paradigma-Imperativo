#pragma once

#include <string>

int crearSocketServidor(int puerto);
int aceptarCliente(int serverSocket);
std::string leerSolicitudCliente(int clientSocket);
void enviarRespuestaCliente(int clientSocket, const std::string& respuesta);
void cerrarSocketServidor(int socketFd);
