#include <iostream>
#include <unistd.h>
#include "cstdlib"
#include <limits>
#include "cliente_service.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "cliente_service.h"

#include <nlohmann/json.hpp>
#include <fstream>


void mostrarMesasDisponible(){

    std::cout << "\033[36m" << "╔══════════════════════════════════════════════════════════════╗" << "\033[0m" << std::endl;
    std::cout << "\033[1;33m" << "                MESAS DISPONIBLES" << "\033[0m" << std::endl;
    std::cout << "\033[36m" << "╠══════════════════════════════════════════════════════════════╣" << "\033[0m" << std::endl;
    nlohmann::json json_respuesta = mostrarMesas();
    try {
        if(json_respuesta.contains("mesas")){
            std::cout << "\033[32mMesas disponibles:\033[0m" << std::endl;
            auto mesas = json_respuesta["mesas"];
            for(const auto& mesa : mesas){
                std::cout << "\033[1;36m[ " << mesa["numero"] << " ]\033[0m  ";
            }
        }
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "\033[31mError al parsear la respuesta JSON: " << e.what() << "\033[0m" << std::endl;
    }
    std::cout << "\033[36m" << "╚══════════════════════════════════════════════════════════════╝" << "\033[0m" << std::endl;
    std::cout << "\033[1;34mPresione Enter para continuar...\033[0m";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

//este metodo es utilizado apra confirar acciones que haga el usuario
bool confirmarAccion(){
    int confirmacion;
    std::cout << "\033[36m" << "╔══════════════════════════════════════════════════════════════╗" << "\033[0m" << std::endl;
    std::cout << "\033[1;33m¿Está seguro que desea realizar esta acción?\033[0m" << std::endl;
    std::cout << "\033[36m" << "╠══════════════════════════════════════════════════════════════╣" << "\033[0m" << std::endl;
    std::cout << "\033[32m1. Si\033[0m" << std::endl;
    std::cout << "\033[31m2. No\033[0m" << std::endl;
    std::cout << "\033[36m" << "╚══════════════════════════════════════════════════════════════╝" << "\033[0m" << std::endl;
    while (!(std::cin >> confirmacion) || (confirmacion != 1 && confirmacion != 2)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\033[31mOpción inválida. Intente de nuevo: \033[0m";
    }
    std::cin.ignore(); // Limpiar salto de línea
    if (confirmacion == 1) {
        return true;
    }
    else {
        std::cout << "\033[31mAcción cancelada. Volviendo al menú...\033[0m" << std::endl;
        std::cout << "\033[1;34mPresione Enter para continuar...\033[0m";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return false;
    }
}

void mostrarProductosMenu(){
    std::cout << "\033[35m" << "╔══════════════════════════════════════════════════════════════╗" << "\033[0m" << std::endl;
    std::cout << "\033[1;33m" << "                PRODUCTOS DISPONIBLES" << "\033[0m" << std::endl;
    std::cout << "\033[35m" << "╠══════════════════════════════════════════════════════════════╣" << "\033[0m" << std::endl;
    nlohmann::json json_respuesta = mostrarProductos();
    try {
        if (json_respuesta.contains("productos")) {
            auto productos_json = json_respuesta["productos"];
            std::cout << "\033[32mProductos disponibles:\033[0m" << std::endl;
            for (const auto& producto : productos_json) {
                std::cout << "\033[1;36mProducto: \033[0m" << producto["nombre"] << " | "
                          << "\033[1;33mPrecio: \033[0m" << producto["precio"] << std::endl;
            }
        } else {
            std::cout << "\033[31mNo se encontraron productos en la respuesta.\033[0m" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "\033[31mError al parsear la respuesta JSON: " << e.what() << "\033[0m" << std::endl;
    }
    std::cout << "\033[35m" << "╚══════════════════════════════════════════════════════════════╝" << "\033[0m" << std::endl;
    std::cout << "\033[1;34mPresione Enter para continuar...\033[0m";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
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

    std::cout << "\033[34m" << "╔══════════════════════════════════════════════════════════════╗" << "\033[0m" << std::endl;
    std::cout << "\033[1;33m" << "                ÓRDENES ACTUALES" << "\033[0m" << std::endl;
    std::cout << "\033[34m" << "╠══════════════════════════════════════════════════════════════╣" << "\033[0m" << std::endl;
    nlohmann::json json_respuesta = mostrarOrdenes(); //muestro las ordenes para que el usuario escoja el id de la orden a modificar
    try {
        if (json_respuesta.contains("ordenes")) {
            auto ordenes_json = json_respuesta["ordenes"];
            for (const auto& orden : ordenes_json) {
                std::cout << "\033[1;36mOrden ID: \033[0m" << orden["id"] << std::endl;
                std::cout << "\033[32mMesa: \033[0m" << orden["mesa"] << std::endl;
                std::cout << "\033[1;33mProductos:\033[0m" << std::endl;
                for (const auto& producto : orden["productos"].items()) {
                    std::cout << "  - \033[35m" << producto.key() << "\033[0m: \033[36m" << producto.value() << "\033[0m" << std::endl;
                }
                std::cout << "\033[34m" << "──────────────────────────────────────────────────────────────" << "\033[0m" << std::endl;
            }
        } else {
            std::cout << "\033[31mNo se encontraron órdenes en la respuesta.\033[0m" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "\033[31mError al parsear la respuesta JSON: " << e.what() << "\033[0m" << std::endl;
    }
    std::cout << "\033[34m" << "╚══════════════════════════════════════════════════════════════╝" << "\033[0m" << std::endl;
    std::cout << "\033[1;34mPresione Enter para continuar...\033[0m";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}


void mostrarCrearOrdenMenu(){

    int numero_mesa;
    vector<pair<string, int>> lista_productos; //productos que el usuario agregaa a la orden

    
    std::cout << "\033[35m" << "╔══════════════════════════════════════════════════════════════╗" << "\033[0m" << std::endl;
    std::cout << "\033[1;33m" << "                CREAR NUEVA ORDEN" << "\033[0m" << std::endl;
    std::cout << "\033[35m" << "╠══════════════════════════════════════════════════════════════╣" << "\033[0m" << std::endl;

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
    std::cout << "\033[36m" << "──────────────────────────────────────────────────────────────" << "\033[0m" << std::endl;
    std::cout << "\033[1;32mOrden creada:\033[0m\n\033[1;36mMesa: \033[0m" << numero_mesa << std::endl;
    for (const auto& p : lista_productos) {
        std::cout << "\033[1;35mProducto: \033[0m" << p.first << " | \033[1;33mCantidad: \033[0m" << p.second << std::endl;
    }
    std::cout << "\033[36m" << "──────────────────────────────────────────────────────────────" << "\033[0m" << std::endl;
    std::cout << "\033[1;34mPresione Enter para continuar...\033[0m";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    if(!confirmarAccion()) 
        return;
    else
        crearOrden(numero_mesa, lista_productos);
}


void mostrarModificarOrdenMenu(){

    int id_orden;
    vector<pair<string, int>> lista_productos;

    //muesto las ordenes existentes para que el usuario ingrese el id
    mostrarOrdenesMenu();
    std::cout << "\033[36m" << "╔══════════════════════════════════════════════════════════════╗" << "\033[0m" << std::endl;
    std::cout << "\033[1;33m" << "                MODIFICAR ORDEN" << "\033[0m" << std::endl;
    std::cout << "\033[36m" << "╠══════════════════════════════════════════════════════════════╣" << "\033[0m" << std::endl;
    
    cout << "Ingrese el ID de la orden a modificar: ";
    while (!(cin >> id_orden) || id_orden <= 0) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "ID inválido. Intente de nuevo: ";
    }
    cin.ignore(); // Limpiar salto de línea
    
    
    lista_productos = modificarProducto(); //pido los productos a modificar o agregar a la orden

    // muestra resumen de la modificación
    std::cout << "\033[36m" << "──────────────────────────────────────────────────────────────" << "\033[0m" << std::endl;
    std::cout << "\033[1;32mModificación a aplicar en la orden \033[0m" << id_orden << ":" << std::endl;
    for (const auto& p : lista_productos) {
        if (p.second == 0)
            std::cout << "\033[31mEliminar producto: \033[0m" << p.first << std::endl;
        else
            std::cout << "\033[1;35mProducto: \033[0m" << p.first << " | \033[1;33mNueva cantidad: \033[0m" << p.second << std::endl;
    }
    std::cout << "\033[36m" << "──────────────────────────────────────────────────────────────" << "\033[0m" << std::endl;
    std::cout << "\033[1;34mPresione Enter para continuar...\033[0m";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    if(!confirmarAccion()) 
        return;
    else
        modificarOrden(id_orden, lista_productos);

}


void mostrarMenu(){
    while (true)
    {
        system("clear");
        std::cout << "\033[36m" << "╔══════════════════════════════════════════════════════════════╗" << "\033[0m" << std::endl;
        std::cout << "\033[1;33m" << "              MENÚ PRINCIPAL DEL SISTEMA  " << "\033[0m" << std::endl;
        std::cout << "\033[36m" << "╠═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═◆═╣" << "\033[0m" << std::endl;
        int option;
        std::cout << "\033[32m-> 1.\033[0m Ver \033[1;36mÓrdenes\033[0m" << std::endl;
        std::cout << "\033[32m-> 2.\033[0m Crear \033[1;35mOrden\033[0m" << std::endl;
        std::cout << "\033[32m-> 3.\033[0m Modificar \033[1;33mOrden\033[0m" << std::endl;
        std::cout << "\033[31mX 4.\033[0m Salir" << std::endl;
        std::cout << "\033[36m" << "╚══════════════════════════════════════════════════════════════╝" << "\033[0m" << std::endl;
        std::cout << "\033[1;34mIngrese una opción: \033[0m";
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[31mEntrada inválida. Intente de nuevo.\033[0m" << std::endl;
            std::cout << "\033[36mPresione Enter para continuar...\033[0m";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            continue;
        }

        switch (option) {
            case 1:
                mostrarOrdenesMenu();
                break;
            case 2:
                mostrarCrearOrdenMenu();
                break;
            case 3:
                mostrarModificarOrdenMenu();
                break;
            case 4:
                std::cout << "\033[31mSaliendo...\033[0m" << std::endl;
                return;
            default:
                std::cout << "\033[31mOpción inválida\033[0m" << std::endl;
                std::cout << "\033[36mPresione Enter para continuar...\033[0m";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
        }
    }
}

void pantallaInicial(){
    system("clear");
    //imprime el ascci de inico
    std::ifstream asciiFile("../client/assets/ascii-art.txt");
    if (asciiFile.is_open()) {
        std::string line;
        cout << "\033[1;33m"; 
        while (std::getline(asciiFile, line)) {
            std::cout << line << std::endl;
        }
        cout << "\033[0m";
        asciiFile.close();
    } else {
        std::cout << "[No se pudo cargar el arte ASCII]" << std::endl;
    }
    std::cout << "\033[36m" << "╔══════════════════════════════════════════════════════════════╗" << "\033[0m" << std::endl;
    std::cout << "\033[1;33m" << "  Bienvenido al sistema de gestión de órdenes del restaurante" << "\033[0m" << std::endl;
    std::cout << "\033[36m" << "╚══════════════════════════════════════════════════════════════╝" << "\033[0m" << std::endl;
    std::cout << "\033[1;34mPresione Enter para continuar...\033[0m";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}