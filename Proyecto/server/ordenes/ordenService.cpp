#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_set>
#include "../../models/orden.h"
#include "ordenService.h"
#include "../../models/operacionesstructs.h"
#include "../utils/Auxiliares.h"
#include "../mesas/mesaService.h"

using namespace std;

namespace {
const char* RESET = "\033[0m";
const char* BOLD = "\033[1m";
const char* CYAN = "\033[36m";
const char* GREEN = "\033[32m";
const char* YELLOW = "\033[33m";
const char* MAGENTA = "\033[35m";
const char* BLUE = "\033[34m";
}


PtrOrden crearOrden(int numeroMesa, const std::vector<std::pair<std::string, int>>& listaProductos){

    // Validar que la mesa exista antes de crear la orden
    if (!existeMesa(numeroMesa)) {
        throw std::runtime_error("La mesa " + std::to_string(numeroMesa) + " no existe.");
    }

    static int contadorOrdenes = 1;

    PtrOrden orden = new(Orden);
    orden->id = contadorOrdenes++;
    orden->id_mesa = numeroMesa;
    orden->estado = true; // pendiente

    unordered_set<string> productosEnOrden;

    for (size_t i = 0; i < listaProductos.size(); i++) {
        const string nombreOriginal = listaProductos[i].first;

        if (nombreOriginal.empty()) {
            delete orden;
            throw std::runtime_error("Hay un producto con nombre vacio en la orden.");
        }

        if (productosEnOrden.find(nombreOriginal) != productosEnOrden.end()) {
            delete orden;
            throw std::runtime_error("Producto repetido en la orden: " + nombreOriginal);
        }

        productosEnOrden.insert(nombreOriginal);

        PtrElemento elementoProducto = buscarElementoNombre(ListaProductos, listaProductos[i].first);
        if (elementoProducto == NULL) {
            delete orden;
            throw std::runtime_error("El producto no está registrado: " + listaProductos[i].first);
        }

        ProductoEscogido escogido;
        escogido.producto = static_cast<PtrProducto>(elementoProducto->Informacion);
        escogido.cantidad = listaProductos[i].second;
        orden->detalles.push_back(escogido);
    }
    
    // inserta la orden en ListaOrdenes automáticamente
    PtrElemento nuevoElemento = new(ElementoLista);
    nuevoElemento->Informacion = (void*)orden;
    nuevoElemento->Operaciones = OperacionesOrdenes;
    nuevoElemento->Siguiente = NULL;
    
    if (ListaOrdenes == NULL) {
        ListaOrdenes = nuevoElemento;
    } else {
        PtrElemento actual = ListaOrdenes;
        while (actual->Siguiente != NULL) {
            actual = actual->Siguiente;
        }
        actual->Siguiente = nuevoElemento;
    }
    
    return orden;
}


void leerOrden(void* informacion){
    PtrOrden orden = static_cast<PtrOrden>(informacion);
    cout << BLUE << "  ┌─ " << RESET << BOLD << CYAN << "Orden #" << orden->id << RESET << endl;
    cout << BLUE << "  ├─ " << RESET << GREEN << "Mesa: " << RESET << orden->id_mesa << endl;
    
    if (orden->detalles.empty()){
        cout << BLUE << "  ├─ " << RESET << YELLOW << "(sin productos)" << RESET << endl;
    } else {
        cout << BLUE << "  ├─ " << RESET << GREEN << "Productos:" << RESET << endl;
        for (size_t i = 0; i < orden->detalles.size(); i++){
            const ProductoEscogido& detalle = orden->detalles[i];
            if (detalle.producto != NULL){
                cout << BLUE << "  │   • " << RESET << MAGENTA << detalle.producto->Nombre << RESET 
                     << " " << CYAN << "(" << detalle.cantidad << " ud)" << RESET << endl;
            }
        }
    }
    
    const char* estadoColor = orden->estado ? YELLOW : GREEN;
    const char* estadoTexto = orden->estado ? "Pendiente" : "Completada";
    cout << BLUE << "  └─ " << RESET << "Estado: " << estadoColor << BOLD << estadoTexto << RESET << endl;
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
    cout << CYAN << BOLD << "╔════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << BOLD << "║       ÓRDENES REGISTRADAS EN SISTEMA       ║" << RESET << endl;
    cout << CYAN << BOLD << "╚════════════════════════════════════════════╝" << RESET << endl;
    if (ListaOrdenes == NULL) {
        cout << YELLOW << "  (No hay órdenes registradas)" << RESET << endl;
    } else {
        leerElementos(ListaOrdenes);
    }
    cout << endl;
}

//Ordnes filtradas
void mostrarOrdenesPendientes(){
    cout << endl;
    cout << CYAN << BOLD << "╔════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << BOLD << "║         ÓRDENES PENDIENTES POR ENTREGAR    ║" << RESET << endl;
    cout << CYAN << BOLD << "╚════════════════════════════════════════════╝" << RESET << endl;

    if (ListaOrdenes == NULL){
        cout << YELLOW << "  (No hay órdenes en el sistema)" << RESET << endl;
        cout << endl;
        return;
    }

    bool hayPendientes = false;
    int indice = 1;
    PtrElemento actual = ListaOrdenes;

    while (actual != NULL){
        PtrOrden orden = static_cast<PtrOrden>(actual->Informacion);
        if (orden != NULL && orden->estado){
            cout << "\n";
            leerOrden(actual->Informacion);
            hayPendientes = true;
        }
        actual = actual->Siguiente;
        indice++;
    }

    if (!hayPendientes){
        cout << YELLOW << "  ✓ Todas las órdenes han sido completadas" << RESET << endl;
    }

    cout << endl;
}

void modificarOrdenesPendientes() {
    int subOpcion = -1;
    while (subOpcion != 0) {
        cout << endl;
        cout << CYAN << BOLD << "╔════════════════════════════════════════════╗" << RESET << endl;
        cout << CYAN << BOLD << "║       MARCAR ORDEN COMO COMPLETADA         ║" << RESET << endl;
        cout << CYAN << BOLD << "╠════════════════════════════════════════════╣" << RESET << endl;
        cout << CYAN << BOLD << "║" << RESET << GREEN << "  [1] Marcar orden como completada         " << RESET << CYAN << BOLD << "║" << RESET << endl;
        cout << CYAN << BOLD << "║" << RESET << MAGENTA << "  [0] Volver                                 " << RESET << CYAN << BOLD << "║" << RESET << endl;
        cout << CYAN << BOLD << "╚════════════════════════════════════════════╝" << RESET << endl;
        cout << BOLD << YELLOW << "Opción: " << RESET;
        cin >> subOpcion;
        
        if (subOpcion == 1) {
            int idOrden;
            cout << "Ingrese el ID de la orden a completar: ";
            cin >> idOrden;
            bool completada = marcarOrdenCompletada(idOrden);
            if (completada) {
                cout << GREEN << BOLD << "✓ Orden " << idOrden << " marcada como completada." << RESET << endl;
            } else {
                cout << YELLOW << "✗ Orden " << idOrden << " no encontrada." << RESET << endl;
            }
        }
    }
}




// Nota: crearOrden(int, vector) arriba es la función correcta para crear órdenes
// Las siguientes son wrappers para el struct OperacionesOrdenes (CRUD genérico)

void* crearOrdenCRUD(void) {
    // Para órdenes, la creación requiere datos específicos del cliente (mesa y productos)
    // Se usa crearOrden(int numeroMesa, vector) en server_service.cpp
    // Este placeholder es para compatibilidad con el CRUD genérico
    return nullptr;
}

void actualizarOrdenCRUD(void* informacion) {
    PtrOrden orden = static_cast<PtrOrden>(informacion);
    if (orden != NULL) {
        cout << "Ingrese el nuevo ID de la mesa: ";
        cin >> orden->id_mesa;
    }
}

void eliminarOrdenCRUD(void* informacion) {
    PtrOrden orden = static_cast<PtrOrden>(informacion);
    if (orden != NULL) {
        delete(orden);
    }
}

//Operaciones para trabajar con ordenes en el CRUD
OperacionesStructs OperacionesOrdenes = {
    crearOrdenCRUD,
    leerOrden,
    actualizarOrdenCRUD,
    eliminarOrdenCRUD
};
