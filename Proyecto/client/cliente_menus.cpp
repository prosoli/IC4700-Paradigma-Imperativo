#include <iostream>
#include <unistd.h>
#include "cstdlib"
#include <limits>
#include "cliente_service.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "cliente_service.h"
#include <nlohmann/json.hpp>


void mostrarMesasDisponible(){

    nlohmann::json json_respuesta = mostrarMesas(); //llamo a la funcion que solicta las mesas y retorna un json
    try {

        if(json_respuesta.contains("mesas")){
            cout << "Mesas disponibles:" << endl;
            auto mesas = json_respuesta["mesas"];
            for(const auto& mesa : mesas){
                cout << "Mesa: " << mesa["numero"] << "  ";
            }
        }   cout << endl;
    }
    catch (const std::exception& e) {
        cout << "Error al parsear la respuesta JSON: " << e.what() << endl;
    }

    // Espera a que el usuario presione enter para volver al menú
    cout << "Presione Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

//este metodo es utilizado apra confirar acciones que haga el usuario
bool confirmarAccion(){
    int confirmacion;
    cout << "¿Está seguro que desea realizar esta acción?" << endl;
    cout << "1. Si" << endl;
    cout << "2. No" << endl;
    
    while (!(cin >> confirmacion) || (confirmacion != 1 && confirmacion != 2)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Opción inválida. Intente de nuevo: ";
    }
    cin.ignore(); // Limpiar salto de línea
    if (confirmacion == 1) {
        return true;
    }
    else {
        cout << "Acción cancelada. Volviendo al menú..." << endl;
        // Esperar a que el usuario presione enter para volver al menú
        cout << "Presione Enter para continuar...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        return false;
    }
}

void mostrarProductosMenu(){
    nlohmann::json json_respuesta = mostrarProductos(); //llamo a la funcion que solicta los productos y retorna un json
    try {
        if (json_respuesta.contains("productos")) { //verifico que el json tenga el campo "productos"
            auto productos_json = json_respuesta["productos"]; //accedo al array de productos dentro del json
            cout << "Productos disponibles:" << endl;
            for (const auto& producto : productos_json) { //recorro el array de productos y muestro su nombre y precio
                cout << "Producto: " << producto["nombre"] << " | Precio: " << producto["precio"] << endl;
            }
        } else {
            cout << "No se encontraron productos en la respuesta." << endl;
        }
    } catch (const std::exception& e) {
        cout << "Error al parsear la respuesta JSON: " << e.what() << endl;
    }
    
    // Espera a que el usuario presione enter para volver al menú
    cout << "Presione Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

vector<pair<string, int>> agregarProducto(){
    vector<pair<string, int>> lista_productos;
    string producto;
    int cantidad;

    mostrarProductosMenu(); //muestro los productos para que escoja

    while (true) {
        cin.clear();
        cout << "Ingrese el producto o platillo a agregar: ";
        getline(cin, producto);
        while (producto.empty()) {
            cout << "El producto no puede estar vacío. Intente de nuevo: ";
            getline(cin, producto);
        }
        cout << "Ingrese la cantidad a agregar: ";
        while (!(cin >> cantidad) || cantidad <= 0) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Cantidad inválida. Intente de nuevo: ";
        }
        cin.ignore(); // Limpiar salto de línea
        lista_productos.push_back({producto, cantidad});

        char otra;
        cout << "¿Desea agregar otro producto? (s/n): ";
        cin >> otra;
        cin.ignore();
        if (otra != 's' && otra != 'S') break;
    }

    return lista_productos;
}

vector<pair<string, int>> modificarProducto(){
    vector<pair<string, int>> lista_productos;
    string producto;
    int cantidad;

    mostrarProductosMenu(); //muestro los productos para que escoja

    while (true) {
        cin.clear();
        cout << "Ingrese el producto o platillo a modificar/agregar: ";
        getline(cin, producto);
        while (producto.empty()) {
            cout << "El producto no puede estar vacío. Intente de nuevo: ";
            getline(cin, producto);
        }
        cout << "Ingrese la nueva cantidad (0 para eliminar): ";
        while (!(cin >> cantidad) || cantidad < 0) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Cantidad inválida. Intente de nuevo: ";
        }
        cin.ignore(); // Limpiar salto de línea
        lista_productos.push_back({producto, cantidad});

        char otra;
        cout << "¿Desea modificar/agregar otro producto? (s/n): ";
        cin >> otra;
        cin.ignore();
        if (otra != 's' && otra != 'S') break;
    }

    return lista_productos;
}


void mostrarOrdenesMenu(){

    nlohmann::json json_respuesta = mostrarOrdenes();
    try {
        
        if (json_respuesta.contains("ordenes")) { //verifico que el json tenga el campo "ordenes"
            auto ordenes_json = json_respuesta["ordenes"]; //accedo al array de ordenes dentro del json
            for (const auto& orden : ordenes_json) { //recorro el array de ordenes y muestro su id, mesa y productos solicitados
                cout << "Orden ID: " << orden["id"] << endl;
                cout << "Mesa: " << orden["mesa"] << endl;
                cout << "Productos:" << endl;
                for (const auto& producto : orden["productos"].items()) { //recorro el objeto de productos dentro de cada orden y muestro el nombre del producto y la cantidad solicitada
                    cout << "  - " << producto.key() << ": " << producto.value() << endl;
                }
                cout << "-----------------------------" << endl;
            }
        } else {
            cout << "No se encontraron órdenes en la respuesta." << endl;
        }
    } catch (const std::exception& e) {
        cout << "Error al parsear la respuesta JSON: " << e.what() << endl;
    }
    // Esperar a que el usuario presione enter para volver al menú
    cout << "Presione Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}


void mostrarCrearOrdenMenu(PtrElemento& ordenes, PtrElemento& productos){

    int numero_mesa;
    vector<pair<string, int>> lista_productos; //productos que el usuario agregaa a la orden

    
    cout << "\n--- Crear Nueva Orden ---" << endl;

    mostrarMesasDisponible(); //muestro las mesas disponibles para que el usuario escoja

    //declaro variable para almacenar el numero de mesa ingresado por el usuario
    cout << "Ingrese el número de mesa: ";
    while (!(cin >> numero_mesa) || numero_mesa <= 0) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignora los entres anteriores del usuario para que l cin espere por otro enter
        cout << "Número de mesa inválido. Intente de nuevo: ";
    }
    cin.ignore(); // Limpiar salto de línea

    //ira ungresando porductos hasat que el usuario inque que no quiere agrgar mas
    lista_productos = agregarProducto();

    // Mostrar resumen de la orden
    cout << "\nOrden creada:\nMesa: " << numero_mesa << endl;
    for (const auto& p : lista_productos) {
        cout << "Producto: " << p.first << " | Cantidad: " << p.second << endl;
    }
    // Esperar a que el usuario presione enter para volver al menú
    cout << "Presione Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();

    if(!confirmarAccion()) 
        return;
    else
        crearOrden(numero_mesa, lista_productos);
}


void mostrarModificarOrdenMenu(PtrElemento& ordenes, PtrElemento& productos){

    int id_orden;
    vector<pair<string, int>> lista_productos;

    //muesto las ordenes existentes para que el usuario ingrese el id
    mostrarOrdenesMenu();
    cout << "\n--- Modificar Orden ---" << endl;
    
    cout << "Ingrese el ID de la orden a modificar: ";
    while (!(cin >> id_orden) || id_orden <= 0) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "ID inválido. Intente de nuevo: ";
    }
    cin.ignore(); // Limpiar salto de línea
    
    
    lista_productos = modificarProducto(); //pido los productos a modificar o agregar a la orden

    // Mostrar resumen de la modificación
    cout << "\nModificación a aplicar en la orden " << id_orden << ":" << endl;
    for (const auto& p : lista_productos) {
        if (p.second == 0)
            cout << "Eliminar producto: " << p.first << endl;
        else
            cout << "Producto: " << p.first << " | Nueva cantidad: " << p.second << endl;
    }
    // Esperar a que el usuario presione enter para volver al menú
    cout << "Presione Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();

    if(!confirmarAccion()) 
        return;
    else
        modificarOrden(id_orden, lista_productos);

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
            cout << "Presione Enter para continuar...";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            continue;
        }

        switch (option) {
            case 1:
                mostrarOrdenesMenu();
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
                cout << "Presione Enter para continuar...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
                break;
        }
    }
}

