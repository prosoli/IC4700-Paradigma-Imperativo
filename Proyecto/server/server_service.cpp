#include "server_service.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>

#include "../models/messageCode.h"
#include "ordenes/ordenService.h"


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
			case ViewOrders:
			case ModifyOrder:
			case ViewProducts:
				return nlohmann::json({
					{"ok", false},
					{"Type", type_code},
					{"error", "En procesoo."}
				}).dump();
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
