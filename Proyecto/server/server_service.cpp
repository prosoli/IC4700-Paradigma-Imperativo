#include "server_service.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>

#include "../models/messageCode.h"
#include "ordenes/ordenService.h"
#include "server_menus.h" //Para que se pueda acceder a la lista de productos
#include "mesas/mesaService.h"


using namespace std;

bool parseCreateOrder(const nlohmann::json& json_msg, int& mesa, std::vector<std::pair<std::string, int>>& productos, std::string& error) {
	if (!json_msg.contains("Mesa") || !json_msg.contains("Productos")) {    //Verifica que existan los campos de mesa y productos
		error = "Se requiere Mesa y productos.";
		return false;
    }
	if (!json_msg["Mesa"].is_number_integer() || !json_msg["Productos"].is_array()) {
		error = "Formato invalido para mesa o productos.";
		return false;
	}

	mesa = json_msg["Mesa"].get<int>();
	const auto& productos_json = json_msg["Productos"];
	productos.clear();

	for (size_t i = 0; i < productos_json.size(); i++) {
		const auto& item = productos_json[i];
		if (!item.is_array() || item.size() != 2 || !item[0].is_string() || !item[1].is_number_integer()) {
			error = "Formato invalido en la lsita de productos.";
			return false;
		}
		productos.push_back({item[0].get<std::string>(), item[1].get<int>()});
	}

	error.clear();
	return true;
}


nlohmann::json createOrderHandler(const nlohmann::json& json_msg) {
	int mesa = 0;
	std::vector<std::pair<std::string, int>> productos;
	std::string error;
	if (!parseCreateOrder(json_msg, mesa, productos, error)) {                                                                     
		return {
			{"ok", false},
			{"Type", static_cast<int>(CreateOrder)},
			{"error", error}
		};
	}

	try {
		PtrOrden ordenCreada = crearOrden(mesa, productos);
		return {
			{"ok", true},
			{"Type", static_cast<int>(CreateOrder)},
			{"message", "Orden creada correctamente."},
			{"idOrden", ordenCreada->id},
			{"mesa", ordenCreada->id_mesa},
			{"cantidadProductos", ordenCreada->detalles.size()}
		};
	} catch (const std::exception& e) {
		return {
			{"ok", false},
			{"Type", static_cast<int>(CreateOrder)},
			{"error", e.what()}
		};
	}
}

//Productos
nlohmann::json productoAJson(void* informacion){
	PtrProducto producto = static_cast<PtrProducto>(informacion);
	nlohmann::json productoJSON;
	productoJSON["nombre"] = producto->Nombre;
	productoJSON["precio"] = producto->Precio;
	return productoJSON;
}

nlohmann::json generarListaProductos(PtrElemento lista){
	nlohmann::json arregloJSON = nlohmann::json::array();
	PtrElemento actual = lista;
	while (actual != NULL){
		arregloJSON.push_back(productoAJson(actual->Informacion));
		actual = actual->Siguiente;
	}
	nlohmann::json listaJSON;
	listaJSON["productos"] = arregloJSON;
	return listaJSON;
}
//

nlohmann::json viewTablesHandler(const nlohmann::json& json_msg) {
    // Obtener la lista de IDs de mesas desde el servicio
    std::vector<int> mesas = obtenerListaMesas();
    // Construir el arreglo JSON en el formato esperado por el cliente
    nlohmann::json mesas_array = nlohmann::json::array();
    for (int id : mesas) {
        mesas_array.push_back({{"numero", id}});
    }
    // Retornar respuesta exitosa
    return nlohmann::json({
        {"ok", true},
        {"Type", json_msg["Type"]},
        {"mesas", mesas_array}
    });
}

nlohmann::json viewOrdersHandler(const nlohmann::json& json_msg) {
	nlohmann::json ordenes_json = nlohmann::json::array();
	PtrElemento actual = ListaOrdenes;

	while (actual != NULL) {
		PtrOrden orden = static_cast<PtrOrden>(actual->Informacion);
		if (orden != NULL) {
			nlohmann::json productos_json = nlohmann::json::object();
			for (size_t i = 0; i < orden->detalles.size(); i++) {
				const ProductoEscogido& detalle = orden->detalles[i];
				if (detalle.producto == NULL) {
					continue;
				}

				std::string nombre = detalle.producto->Nombre;
				if (!productos_json.contains(nombre)) {
					productos_json[nombre] = 0;
				}
				productos_json[nombre] = productos_json[nombre].get<int>() + detalle.cantidad;
			}

			ordenes_json.push_back({
				{"id", orden->id},
				{"mesa", orden->id_mesa},
				{"estado", orden->estado ? "Pendiente" : "Completada"},
				{"productos", productos_json}
			});
		}

		actual = actual->Siguiente;
	}

	return nlohmann::json({
		{"ok", true},
		{"Type", json_msg["Type"]},
		{"ordenes", ordenes_json}
	});
}

nlohmann::json modifyOrderHandler(const nlohmann::json& json_msg) {
    // Validar campos
    if (!json_msg.contains("IdOrden") || !json_msg.contains("Productos")) {
        return {
            {"ok", false},
            {"Type", json_msg["Type"]},
            {"error", "Se requiere IdOrden y Productos."}
        };
    }
    if (!json_msg["IdOrden"].is_number_integer() || !json_msg["Productos"].is_array()) {
        return {
            {"ok", false},
            {"Type", json_msg["Type"]},
            {"error", "Formato inválido para IdOrden o Productos."}
        };
    }

    int idOrden = json_msg["IdOrden"].get<int>();
    const auto& productos_json = json_msg["Productos"];
    std::vector<std::pair<std::string, int>> productos;

    // Parsear productos
    for (const auto& item : productos_json) {
        if (!item.is_array() || item.size() != 2 || !item[0].is_string() || !item[1].is_number_integer()) {
            return {
                {"ok", false},
                {"Type", json_msg["Type"]},
                {"error", "Formato inválido en la lista de productos. Se espera [\"nombre\", cantidad]."}
            };
        }
        productos.push_back({item[0].get<std::string>(), item[1].get<int>()});
    }

    try {
        modificarOrden(idOrden, productos);
        return {
            {"ok", true},
            {"Type", json_msg["Type"]},
            {"message", "Orden modificada correctamente."},
            {"idOrden", idOrden}
        };
    } catch (const std::exception& e) {
        return {
            {"ok", false},
            {"Type", json_msg["Type"]},
            {"error", e.what()}
        };
    }
}

std::string procesarMensajeServidor(const std::string& mensaje) {
	if (mensaje.empty()) {
		cout << "No se recibio mensaje o error de lectura." << endl;
		return nlohmann::json({
			{"ok", false},
			{"error", "Mensaje vacio."}
		}).dump();
	}

	cout << "Mensaje recibido del cliente (raw):" << endl;
	cout << mensaje << endl;

	try {
		nlohmann::json json_msg = nlohmann::json::parse(mensaje);
		for (auto it = json_msg.begin(); it != json_msg.end(); ++it) {
			cout << it.key() << ": " << it.value() << endl;
		}

		if (!json_msg.contains("Type") || !json_msg["Type"].is_number_integer()) {
			return nlohmann::json({
				{"ok", false},
				{"error", "El campo Type es requerido y debe ser entero."}
			}).dump();
		}

		int type_code = json_msg["Type"].get<int>();
		MessageCode code = static_cast<MessageCode>(type_code);

		switch (code) {
			case CreateOrder:
				return createOrderHandler(json_msg).dump();
			case ViewTables:
				return viewTablesHandler(json_msg).dump();
			case ViewOrders:
				return viewOrdersHandler(json_msg).dump();
			case ModifyOrder:
			case ViewProducts:
				return generarListaProductos(ListaProductos).dump();
			default:
				return nlohmann::json({
					{"ok", false},
					{"Type", type_code},
					{"error", "Codigo Type desconocido."}
				}).dump();
		}
	} catch (const std::exception& e) {
		cout << "No se pudo parsear el mensaje como JSON: " << e.what() << endl;
		return nlohmann::json({
			{"ok", false},
			{"error", "JSON invalido."}
		}).dump();
	}
}
