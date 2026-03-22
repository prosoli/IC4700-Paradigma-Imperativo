#include <iostream>
#include <unistd.h>
#include "cstdlib"
#include <limits>
#include "cliente_service.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "cliente_service.h"

void mostrarCrearOrdenMenu(PtrElemento& ordenes, PtrElemento& productos){
    cout << "Creando orden..." << endl;
    cin>>ws; // Limpiar el buffer de entrada
    crearOrden(ordenes, productos); 
}

void mostrarModificarOrdenMenu(PtrElemento& ordenes, PtrElemento& productos){
    cout << "Modificando orden..." << endl;
    cin>>ws; // Limpiar el buffer de entrada
    modificarOrden(ordenes, productos);  
}

void mostrarMenu(PtrElemento& ordenes, PtrElemento& productos){
    while (true)
    {
        system("clear");
        int option;
        cout << "1. Ver Ordenes" << endl;
        cout << "2. Crear Orden" << endl;
        cout << "3. Modificar Orden" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Entrada inválida. Intente de nuevo." << endl;
            continue;
        }

        switch (option) {
            case 1:
                mostrarOrdenes(ordenes);
                break;
            case 2:
                mostrarCrearOrdenMenu(ordenes, productos);
                break;
            case 3:
                mostrarModificarOrdenMenu(ordenes, productos);
                break;
            case 4:
                cout << "saliendo..." << endl;
                return;
            default:
                cout << "Opcion invalida" << endl;
                break;
        }
    }
}

