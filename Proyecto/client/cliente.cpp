#include <iostream>
#include <unistd.h>
#include "cstdlib"
#include "cliente_service.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "cliente_menus.h"

using namespace std;
//inicializo las listas de ordenes y productos
PtrElemento ordenes = NULL;
PtrElemento productos = NULL;


int main() {
    mostrarMenu(ordenes, productos);
    return 0;
}