#include "server_service.h"

#include <iostream>
#include <nlohmann/json.hpp>

#include "../models/messageCode.h"

using namespace std;

std::string procesarMensajeServidor(const std::string& mensaje) {
	if (mensaje.empty()) {
		cout << "No se recibio mensaje o error de lectura." << endl;
		return "hola recibido";
	}

	cout << "Mensaje recibido del cliente (raw):" << endl;
	cout << mensaje << endl;

	try {
		nlohmann::json json_msg = nlohmann::json::parse(mensaje);
		cout << "\nMensaje recibido (JSON parseado):" << endl;
		for (auto it = json_msg.begin(); it != json_msg.end(); ++it) {
			cout << it.key() << ": " << it.value() << endl;
		}

		if (json_msg.contains("Type")) {
			int type_code = json_msg["Type"].get<int>();
			MessageCode code = static_cast<MessageCode>(type_code);
			string comando;
			switch (code) {
				case ViewTables: comando = "ViewTables"; break;
				case CreateOrder: comando = "CreateOrder"; break;
				case ViewOrders: comando = "ViewOrders"; break;
				case ModifyOrder: comando = "ModifyOrder"; break;
				case ViewProducts: comando = "ViewProducts"; break;
				default: comando = "Desconocido"; break;
			}
			cout << "\nComando recibido (Type): " << comando << endl;

			if (code == ViewOrders) {
				nlohmann::json ordenes = {
					{"ordenes", {
						{{"id", 1}, {"mesa", 5}, {"productos", {{"Pizza", 2}, {"Refresco", 3}}}},
						{{"id", 2}, {"mesa", 3}, {"productos", {{"Hamburguesa", 1}, {"Papas", 2}}}}
					}}
				};
				return ordenes.dump();
			}

			if (code == ViewProducts) {
				nlohmann::json productos = {
					{"productos", {
						{{"nombre", "Pizza"}, {"precio", 10.99}},
						{{"nombre", "Hamburguesa"}, {"precio", 8.99}}
					}}
				};
				return productos.dump();
			}

			if (code == ViewTables) {
				nlohmann::json mesas = {
					{"mesas", {
						{{"numero", 1}},
						{{"numero", 2}}
					}}
				};
				return mesas.dump();
			}
		}
	} catch (const std::exception& e) {
		cout << "No se pudo parsear el mensaje como JSON: " << e.what() << endl;
	}

	return "hola recibido";
}
