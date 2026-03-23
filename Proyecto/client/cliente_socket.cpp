#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int crearSocket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }
    return sock;
}

void conectarServidor(int sock, const char* ip, int puerto) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(puerto);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error al conectar al servidor");
        close(sock);
        exit(EXIT_FAILURE);
    }
}

std::string  enviarDatos(int sock, const char* mensaje) {
    ssize_t bytes = write(sock, mensaje, strlen(mensaje));
    //recibo la respuesta del servidor
    char buffer[1024];
    ssize_t bytesRecibidos = read(sock, buffer, sizeof(buffer));
    if (bytesRecibidos < 0) {
        perror("Error al recibir datos");
        return "";
    } else {
        return std::string(buffer, bytesRecibidos);
    }
}

void cerrarSocket(int sock) {
    close(sock);
}

void ConexionConFork() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Proceso hijo
        int sock = crearSocket();
        conectarServidor(sock, "127.0.0.1", 8080);
        enviarDatos(sock, "Hola desde el hijo\n");
        cerrarSocket(sock);
        exit(0);
    } else { // Proceso padre
        int sock = crearSocket();
        conectarServidor(sock, "127.0.0.1", 8080);
        enviarDatos(sock, "Hola desde el padre\n");
        cerrarSocket(sock);
        wait(NULL); // Espera a que termine el hijo
    }
}

// Envía una solicitud al servidor y cierra la conexión
std::string enviarSolicitudAlServidor(const char* mensaje) {
    int sock = crearSocket();
    conectarServidor(sock, "127.0.0.1", 8080);
    std::string respuesta = enviarDatos(sock, mensaje);
    cerrarSocket(sock);
    return respuesta;
}