#include "server_socket.h"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int crearSocketServidor(int puerto) {
    //creo el socket y tiene 3 argumentos el primero es la direccion del socket, el que uso AF_INET es para host en interner, el segundo es el tipo de socket,  el tercero es el protocolo si es 0 el so va a escoger el mas adecuado.
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		perror("Error al crear socket del servidor");
		return -1;
	}
    // estructura de tipo sockaddre y tiene 4 campos
	sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(puerto);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

    //une el socket con la direccion del servidor, tiene 3 argumentos,  el primero es el socker, el segundo es un puntero a la estructura que creamos y el ultimo es el tamano de la estructura, es decir, el tamanio de la direccion del servidor
	if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("Error en bind");
		close(serverSocket);
		return -1;
	}

	if (listen(serverSocket, 5) < 0) {
		perror("Error en listen");
		close(serverSocket);
		return -1;
	}

	return serverSocket;
}

//el accept es una funcion que se llama para aceptar una conexion entrante, tiene 3 argumentos el primero es el socket, el segundo es un puntero a una estructura que se va a llenar con la direccion del cliente y el tercero es un puntero a un entero que se va a llenar con el tamano de la direccion del cliente.
//si la conexion es exitosa, la funcion devuelve un nuevo socket que se va a usar para comunicarse con el cliente, 
//si hay un error devuelve -1
int aceptarCliente(int serverSocket) {
	int clientSocket = accept(serverSocket, NULL, NULL);
	if (clientSocket < 0) {
		perror("Error en accept");
	}
	return clientSocket;
}

std::string leerSolicitudCliente(int clientSocket) {
	char buffer[1024] = {0};
	ssize_t bytes_read = read(clientSocket, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0) {
		return "";
	}
	buffer[bytes_read] = '\0';
	return std::string(buffer);
}

void enviarRespuestaCliente(int clientSocket, const std::string& respuesta) {
	send(clientSocket, respuesta.c_str(), respuesta.size(), 0);
}

void cerrarSocketServidor(int socketFd) {
	close(socketFd);
}
