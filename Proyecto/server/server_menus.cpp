#include <iostream>
#include <cstdlib>
#include <limits>
#include <vector>
#include <sstream>
#include "server_menus.h"
#include "../server/utils/Auxiliares.h"
#include "../server/productos/productoService.h"
#include "../server/ordenes/ordenService.h"
#include "../server/mesas/mesaService.h"
using namespace std;

namespace {
const char* RESET = "\033[0m";
const char* BOLD = "\033[1m";
const char* CYAN = "\033[36m";
const char* BLUE = "\033[34m";
const char* GREEN = "\033[32m";
const char* YELLOW = "\033[33m";
const char* RED = "\033[31m";
const char* MAGENTA = "\033[35m";

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrarTitulo(const string& titulo) {
    cout << BOLD << CYAN;
    cout << "╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║               PANEL DEL RESTAURANTE                  ║" << endl;
    cout << "╠══════════════════════════════════════════════════════╣" << endl;
    cout << "   " << titulo;
    for (size_t i = titulo.size(); i < 48; i++) {
        cout << ' ';
    }
    cout  << endl << "╚══════════════════════════════════════════════════════╝" << endl;
    cout << RESET;
}

void mostrarSeparador() {
    cout << BLUE << "────────────────────────────────────────────────────────" << RESET << endl;
}

void imprimirOpcion(const char* color, int numero, const string& texto) {
    cout << color << "  [" << numero << "] " << RESET << texto << endl;
}

void limpiarEntradaInvalida() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int leerOpcion(const string& etiqueta) {
    int opcion = -1;
    while (true) {
        cout << BOLD << YELLOW << etiqueta << RESET;
        if (cin >> opcion) {
            return opcion;
        }

        limpiarEntradaInvalida();
        cout << RED << "Entrada invalida. Debe ingresar un numero." << RESET << endl;
    }
}

void pausarConsola() {
    cout << BOLD << YELLOW << "\nPresione Enter para continuar..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
}


void menuProductos(){
    int opcion = -1;
    while (opcion != 0){
        limpiarPantalla();
        mostrarTitulo("Gestion de Productos");
        mostrarSeparador();
        imprimirOpcion(GREEN, 1, "Listar productos");
        imprimirOpcion(GREEN, 2, "Agregar un producto");
        imprimirOpcion(GREEN, 3, "Actualizar un producto");
        imprimirOpcion(GREEN, 4, "Eliminar un producto");
        imprimirOpcion(GREEN, 5, "Eliminar todos los productos");
        imprimirOpcion(MAGENTA, 0, "Volver al menu principal");
        mostrarSeparador();
        opcion = leerOpcion("Seleccione una opcion: ");
        cout<<endl;

        switch (opcion){
            case 1: {
                mostrarProductos();
                leerElementos(ListaProductos);
                break;
            }
            case 2: {
                cout << YELLOW << "--Agregar un producto--" << RESET <<endl;
                char Nombre[50];
                float Precio;

                cout<<"Ingrese el nombre del producto:"<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.getline(Nombre, 50);

                bool precioValido = false;
                while (!precioValido) {
                    cout << BOLD << YELLOW << "Ingrese el precio del producto: " << RESET;
                    if (cin >> Precio) {
                        precioValido = true;
                    } else {
                        limpiarEntradaInvalida();
                        cout << RED << "Entrada invalida. Debe ingresar un numero." << RESET << endl;
                    }
                }
                void* datosProducto[2];
                datosProducto[0] = (void*)Nombre;
                datosProducto[1] = (void*)&Precio;
                insertarElemento(ListaProductos, OperacionesProductos, datosProducto);
                break;
            }
            case 3: {
                cout << YELLOW << "--Actualizar un producto--" << RESET <<endl;
                int indiceProducto = leerOpcion("Ingrese el indice del producto a actualizar: ");
                PtrElemento producto = buscarElemento(ListaProductos, indiceProducto);
                if (producto == NULL){
                    cout<<"Elemento no encontrado."<<endl;
                } else {
                    char Nombre[50];
                    float Precio;

                    cout<<"Ingrese el nuevo nombre del producto:"<<endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.getline(Nombre, 50);

                    bool precioValido = false;
                    while (!precioValido) {
                        cout << BOLD << YELLOW << "Ingrese el nuevo precio del producto: " << RESET;
                        if (cin >> Precio) {
                            precioValido = true;
                        } else {
                            limpiarEntradaInvalida();
                            cout << RED << "Entrada invalida. Debe ingresar un numero." << RESET << endl;
                        }
                    }
                    void* datosProducto[2];
                    datosProducto[0] = (void*)Nombre;
                    datosProducto[1] = (void*)&Precio;
                    actualizarElemento(producto, datosProducto);
                }
                break;
            }
            case 4: {
                cout << YELLOW << "--Eliminar un producto--" << RESET <<endl;
                int indiceProducto = leerOpcion("Ingrese el indice del producto a eliminar: ");
                eliminarElemento(ListaProductos, indiceProducto);
                break;
            }
            case 5: {
                eliminarLista(ListaProductos);
                cout << YELLOW << "--Lista eliminada--" << RESET <<endl;
                break;
            }
            case 0: {
                cout << MAGENTA << "Ha salido del gestionador de productos." << RESET << endl;
                break;
            }
            default: {
                cout << RED << "Por favor ingrese una opcion valida." << RESET << endl;
                break;
            }
        }

        if (opcion != 0) {
            pausarConsola();
        }
    }
}



void menuOrdenes(){

    int opcion = -1;
    while (opcion != 0){
        limpiarPantalla();
        mostrarTitulo("Gestion de Ordenes");
        mostrarSeparador();
        imprimirOpcion(GREEN, 1, "Visualizar ordenes");
        imprimirOpcion(GREEN, 2, "Visualizar ordenes pendientes");
        imprimirOpcion(GREEN, 3, "Modificar ordenes");
        imprimirOpcion(MAGENTA, 0, "Volver al menu principal");
        mostrarSeparador();
        opcion = leerOpcion("Seleccione una opcion: ");
        cout<<endl;

        switch (opcion){
            case 1:
                mostrarOrdenes();
                break;
            case 2:
                mostrarOrdenesPendientes();
                break;
            case 3:
                cout << YELLOW << "Modificando ordenes - AUN NO" << RESET << endl;
                break;
            case 0:
                cout << MAGENTA << "Ha salido del gestionador de ordenes." << RESET << endl;
                break;
            default:
                cout << RED << "Por favor ingrese una opcion valida." << RESET << endl;
                break;
        }

        if (opcion != 0) {
            pausarConsola();
        }
    }
    
}


void menuListas(){
    int opcion = -1;
    while (opcion != 0){
        limpiarPantalla();
        mostrarTitulo("Gestion del Restaurante");
        mostrarSeparador();
        imprimirOpcion(GREEN, 1, "Productos");
        imprimirOpcion(GREEN, 2, "Ordenes");
        imprimirOpcion(GREEN, 3, "Mesas");
        imprimirOpcion(MAGENTA, 0, "Salir");
        mostrarSeparador();
        opcion = leerOpcion("Seleccione una opcion: ");
        cout<<endl;

        switch (opcion){
            case 1:
                menuProductos();
                break;
            case 2:
                menuOrdenes();
                break;
            case 3:
                menuMesas();
                break;
            case 0:
                cout << MAGENTA << "Ha salido del gestionador de listas." << RESET << endl;
                break;
            default:
                cout << RED << "Por favor ingrese una opcion valida." << RESET << endl;
                break;
        }

        if (opcion != 0) {
            pausarConsola();
        }
    }
}
