#include <iostream>
#include <unistd.h>
#include "cstdlib"
#include "cliente_service.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "cliente_menus.h"

using namespace std;


int main() {
    pantallaInicial();
    mostrarMenu();
    return 0;
}