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

PtrOrden buscarOrdenPorId(int id) {
    PtrElemento actual = ListaOrdenes;
    while (actual != nullptr) {
        PtrOrden orden = static_cast<PtrOrden>(actual->Informacion);
        if (orden->id == id) return orden;
        actual = actual->Siguiente;
    }
    return nullptr;
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

void modificarOrden(int idOrden, const std::vector<std::pair<std::string, int>>& productosDelta) {
    // 1. Buscar la orden
    PtrOrden orden = buscarOrdenPorId(idOrden);
    // PtrOrden orden = buscarElemento(ListaOrdenes, idOrden);
    if (orden == nullptr) {
        throw std::runtime_error("No existe la orden con ID " + std::to_string(idOrden));
    }

    // 2. Validar los productos mencionados en la solicitud
    std::unordered_set<std::string> productosEnDelta;
    for (const auto& par : productosDelta) {
        const std::string& nombre = par.first;
        if (nombre.empty()) {
            throw std::runtime_error("Nombre de producto vacío en la solicitud.");
        }
        if (productosEnDelta.find(nombre) != productosEnDelta.end()) {
            throw std::runtime_error("Producto duplicado en la solicitud: " + nombre);
        }
        productosEnDelta.insert(nombre);

        // Verificar que exista en el catálogo
        if (buscarElementoNombre(ListaProductos, nombre) == nullptr) {
            throw std::runtime_error("El producto '" + nombre + "' no está registrado.");
        }
    }

    // 3. Construir un mapa de productos actuales (nombre -> índice en el vector)
    std::unordered_map<std::string, size_t> indiceActual;
    for (size_t i = 0; i < orden->detalles.size(); ++i) {
        if (orden->detalles[i].producto != nullptr) {
            indiceActual[orden->detalles[i].producto->Nombre] = i;
        }
    }

    // 4. Procesar cada producto delta
    for (const auto& par : productosDelta) {
        const std::string& nombre = par.first;
        int cantidad = par.second;
        auto it = indiceActual.find(nombre);
        if (cantidad == 0) {
            // Eliminar si existe
            if (it != indiceActual.end()) {
                orden->detalles[it->second].cantidad = 0;  // marcar para eliminar
            }
        } else {
            // cantidad > 0: agregar o actualizar
            if (it != indiceActual.end()) {
                // Actualizar existente
                orden->detalles[it->second].cantidad = cantidad;
            } else {
                // Agregar nuevo producto
                PtrElemento elem = buscarElementoNombre(ListaProductos, nombre);
                PtrProducto prod = static_cast<PtrProducto>(elem->Informacion);
                ProductoEscogido nuevo;
                nuevo.producto = prod;
                nuevo.cantidad = cantidad;
                orden->detalles.push_back(nuevo);
            }
        }
    }

    // 5. Eliminar todos los productos con cantidad 0
    std::vector<ProductoEscogido> nuevosDetalles;
    for (auto& detalle : orden->detalles) {
        if (detalle.cantidad > 0) {
            nuevosDetalles.push_back(detalle);
        }
    }
    orden->detalles = nuevosDetalles;
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
    cout << YELLOW << "Use CreateOrder desde el cliente para agregar ordenes." << RESET << endl;
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

void* crearOrdenCRUD(void** datos) {
    // Para órdenes, la creación requiere datos específicos del cliente (mesa y productos)
    // Se usa crearOrden(int numeroMesa, vector) en server_service.cpp
    // Este placeholder es para compatibilidad con el CRUD genérico
    (void)datos;
    return nullptr;
}

void actualizarOrdenCRUD(void* informacion, void** datos) {
    (void)datos;
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
