#include <iostream>
#include <string>
#include <stdexcept>
#include "../../models/orden.h"
#include "ordenService.h"
#include "../../models/operacionesstructs.h"
#include "../utils/Auxiliares.h"

using namespace std;


PtrOrden crearOrden(int numeroMesa, const std::vector<std::pair<std::string, int>>& listaProductos){
    static int contadorOrdenes = 1;

    PtrOrden orden = new(Orden);
    orden->id = contadorOrdenes++;
    orden->id_mesa = numeroMesa;
    orden->estado = true; // pendiente

    for (size_t i = 0; i < listaProductos.size(); i++) {
        PtrElemento elementoProducto = buscarElementoNombre(ListaProductos, listaProductos[i].first);
        if (elementoProducto == NULL) {
            delete orden;
            throw std::runtime_error("El producto no está registrado: " + listaProductos[i].first); //Poner try catch en el handler
        }

        ProductoEscogido escogido;
        escogido.producto = static_cast<PtrProducto>(elementoProducto->Informacion);
        escogido.cantidad = listaProductos[i].second;
        orden->detalles.push_back(escogido);
    }

    return orden;
}

void* crearOrden(void){
    //pend
    return NULL;
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

bool marcarOrdenCompletada(int idOrden) {
    PtrElemento actual = ListaOrdenes;
    while (actual != NULL) {
        PtrOrden orden = static_cast<PtrOrden>(actual->Informacion);
        if (orden != NULL && orden->id == idOrden) {
            if (orden->estado) {
                orden->estado = false;  // completada
            }
            return true;
        }
        actual = actual->Siguiente;
    }
    return false;
}

void eliminarOrden(void* informacion){
    // pend
}

//ELIMINARRRRR
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
