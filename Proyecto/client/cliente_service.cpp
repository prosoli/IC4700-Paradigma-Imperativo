#include <iostream>
#include <stdlib.h>
#include "cliente_socket.h"
#include "../models/elementolista.h"

using namespace std;

void mostrarOrdenes(PtrElemento ordenes){
    cout << endl;
    cout << "======= Órdenes registradas =======" << endl;
    enviarSolicitudAlServidor("Solicitud: Mostrar ordenes\n");
    cout << endl;
}

void crearOrden(PtrElemento& ordenes, PtrElemento productos){
    cout << "Creando orden..." << endl;
    cin>>ws; // Limpiar el buffer de entrada
    // --- Comunicación con el servidor ---
    enviarSolicitudAlServidor("Solicitud: Crear orden\n");
}

void modificarOrden(PtrElemento& ordenes, PtrElemento productos){
    cout << "Modificando orden..." << endl;
    cin>>ws; // Limpiar el buffer de entrada
    // --- Comunicación con el servidor ---
    enviarSolicitudAlServidor("Solicitud: Modificar orden\n");
}