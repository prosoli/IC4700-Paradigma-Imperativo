#include <iostream>
#include "server_menus.h"
#include "../server/utils/Auxiliares.h"
#include "../server/productos/productoService.h"
#include "../server/ordenes/ordenService.h"
using namespace std;

//--------------------Menú Productos--------------------//
PtrElemento ListaProductos = NULL;
PtrElemento ListaOrdenes = NULL;

void menuProductos(){
    int opcion = -1;
    while (opcion != 0){
        cout<<endl;
        cout<<"----------- Gestion de Productos -----------"<<endl;
        cout<<"1. Listar productos."<<endl;
        cout<<"2. Agregar un producto."<<endl;
        cout<<"3. Actualizar un producto."<<endl;
        cout<<"4. Eliminar un producto."<<endl;
        cout<<"5. Eliminar todos los productos."<<endl;
        cout<<"0. Volver al menu principal."<<endl<<endl;
        cout<<"Ingrese el numero de la operación que desea realizar:"<<endl;
        cin>>opcion;
        cout<<endl;

        switch (opcion){
            case 1:
		mostrarProductos();
                leerElementos(ListaProductos);
                break;
            case 2:
                insertarElemento(ListaProductos, OperacionesProductos);
                break;
            case 3:
                actualizarElemento(ListaProductos);
                break;
            case 4:
                eliminarElemento(ListaProductos);
                break;
            case 5:
                eliminarLista(ListaProductos);
                break;
            case 0:
                cout<<"Ha salido del gestionador de productos."<<endl;
                break;
            default:
                cout<<"Por favor ingrese una opcion valida."<<endl;
                break;
        }
    }
}

void menuOrdenes(){

    int opcion = -1;
    while (opcion != 0){
        cout<<endl;
        cout<<"----------- Gestion de Ordenes -----------"<<endl;
        cout<<"1. Visualizar ordenes."<<endl;
        cout<<"2. Visualizar ordenes pendientes."<<endl;
        cout<<"3. Modificar Ordenes."<<endl;
        cout<<"0. Volver al menu principal."<<endl<<endl;
        cout<<"Ingrese el numero de la operación que desea realizar:"<<endl;
        cin>>opcion;
        cout<<endl;

        switch (opcion){
            case 1:
		    mostrarOrdenes();
                break;
            case 2:
                mostrarOrdenesPendientes();
                break;
            case 3:
                printf("Modificando ordenes - AUN NO\n");
                break;
            case 0:
                cout<<"Ha salido del gestionador de ordenes."<<endl;
                break;
            default:
                cout<<"Por favor ingrese una opcion valida."<<endl;
                break;
        }
    }
    
}

void menuListas(){
    int opcion = -1;
    while (opcion != 0){
        cout<<endl;
        cout<<"----------- Gestion del Restaurante -----------"<<endl;
        cout<<"1. Productos."<<endl;
        cout<<"2. Ordenes."<<endl;
        cout<<"0. Salir."<<endl<<endl;
        cout<<"Ingrese el número de la lista que desea manejear:"<<endl;
        cin>>opcion;
        cout<<endl;

        switch (opcion){
            case 1:
		mostrarProductos();
                menuProductos();
                break;
            case 2:
                menuOrdenes();
                //opcion = 3;
                break;
            case 0:
                cout<<"Ha salido del gestionador de listas."<<endl;
                break;
            default:
                cout<<"Por favor ingrese una opción válida."<<endl;
                break;
        }
    }
}
