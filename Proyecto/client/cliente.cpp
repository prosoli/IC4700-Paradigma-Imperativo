#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

int main() {

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //esta funcion es llamada por el cliento para establecer una conexion con el servidor, tiene 3 argumetnos el socket, la direccion de servidor y el tamano de la direccion del servidor, si la conexion es exitosa, la funcion devuelve 0, si hay un error devuelve -1
    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

    char message[] = "Hola servidor";

    write(sock, message, sizeof(message));

    close(sock);

    return 0;
}