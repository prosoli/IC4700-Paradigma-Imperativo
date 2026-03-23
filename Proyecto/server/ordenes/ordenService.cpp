#include <iostream>
#include "../../models/orden.h"
#include "ordenService.h"
#include "../../models/operacionesstructs.h"
#include "../utils/Auxiliares.h"

using namespace std;

void* crearOrden(void){
    PtrOrden orden = new(Orden);

    //Numero de orden
    static int contador = 1;
    orden->id = contador++;

    cout<<"Ingrese el numero de mesa:"<<endl;
    cin>>orden->id_mesa;

    while (true){
        cout<<"\nProductos disponibles:"<<endl;
        leerElementos(ListaProductos);  //Muestra los productos disponibles para elegir 
        cout<<"Ingrese el numero del producto o elija 0 para terminar:"<<endl;

        int indiceProducto = 0;
        cin>>indiceProducto;

        if (indiceProducto == 0){   //Salir
            break;
        }

        PtrElemento elementoProducto = buscarElemento(ListaProductos, indiceProducto);  //Se busca el elemnto
        if (elementoProducto == NULL){
            cout<<"Producto no encontrado, intente de nuevo."<<endl;
            continue;
        }

        int cantidad = 0;
        cout<<"Ingrese la cantidad para este producto:"<<endl;
        cin>>cantidad;

        if (cantidad <= 0){
            cout<<"Cantidad invalida, intente de nuevo."<<endl;
            continue;
        }

        ProductoEscogido escogido;
        escogido.producto = static_cast<PtrProducto>(elementoProducto->Informacion);
        escogido.cantidad = cantidad;
        orden->detalles.push_back(escogido);
    }

    orden->estado = true; //Orden con estadi pendiente al entrar

    return (void*)orden;
}

void leerOrden(void* informacion){
    PtrOrden orden = static_cast<PtrOrden>(informacion);
    cout<<"Numero de orden: "<< orden->id << endl;
    cout<<"Numero mesa: "<< orden->id_mesa << endl;
    if (orden->detalles.empty()){
        cout<<"No hay productos en esta orden."<<endl;
    } else {
        cout<<"Productos solicitados: "<<endl;
        for (size_t i = 0; i < orden->detalles.size(); i++){
            const ProductoEscogido& detalle = orden->detalles[i];
            if (detalle.producto != NULL){
                cout<<"- "<<detalle.producto->Nombre<< ": "<<detalle.cantidad<<" unidades"<<endl;
            }
        }
    }
    cout<<"Estado de la orden: "<< (orden->estado ? "Pendiente" : "Completada") << endl;
}

void actualizarOrden(void* informacion){
    // pend
}

void eliminarOrden(void* informacion){
    // pend
}


//Agrega nueva orden usando el CRUD
void agregarOrden(){
    insertarElemento(ListaOrdenes, OperacionesOrdenes);
}

//Muestra las órdenes usando el CRUD
void mostrarOrdenes(){
    cout << endl;
    cout << "======= Órdenes registradas =======" << endl;
    leerElementos(ListaOrdenes);
    cout << endl;
}

//Ordnes filtradas
void mostrarOrdenesPendientes(){
    cout << endl;
    cout << "======= Órdenes pendientes =======" << endl;

    if (ListaOrdenes == NULL){
        cout << "No hay elementos que mostrar." << endl;
        cout << endl;
        return;
    }

    bool hayPendientes = false;
    int indice = 1;
    PtrElemento actual = ListaOrdenes;

    while (actual != NULL){
        PtrOrden orden = static_cast<PtrOrden>(actual->Informacion);
        if (orden != NULL && orden->estado){
            cout << indice << ". ";
            leerOrden(actual->Informacion);
            hayPendientes = true;
        }
        actual = actual->Siguiente;
        indice++;
    }

    if (!hayPendientes){
        cout << "No hay ordenes pendientes." << endl;
    }

    cout << endl;
}

//Operaciones para trabajar con ordenes
OperacionesStructs OperacionesOrdenes = {
    crearOrden,
    leerOrden,
    actualizarOrden,
    eliminarOrden
};