
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../models/messageCode.h"

using namespace std;

int main() {

    //cree un stream socket lo que hace es que se pueda enviar y recibir datos de forma ordenada, es decir, que los datos lleguen en el mismo orden en que se enviaron
    //a diferencia de un datagram socket que no garantiza el orden de los datos, es decir, que los datos pueden llegar en cualquier orden y pueden perderse en el camino
    //creo el socket y tiene 3 argumentos el primero es la direccion del socket, el que uso AF_INET es para host en interner, el segundo es el tipo de socket,  el tercero es el protocolo si es 0 el so va a escoger el mas adecuado.
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    //esta es una estructura de tipo sockaddre y tiene 4 campos
    sockaddr_in serverAddr;
    //el primero es la familia de direcciones
    serverAddr.sin_family = AF_INET;
    //este contiene el numero de puerto, se usa la funcion htons para convertir el numero de puerto a formato de red es decir a host bytes
    serverAddr.sin_port = htons(8080);
    //este campo es una estructura, tiene la IP del servidor, siempre es el ip de la maquina en que la que correo
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    //une el socket con la direccion del servidor, tiene 3 argumentos,  el primero es el socker, el segundo es un puntero a la estructura que creamos y el ultimo es el tamano de la estructura, es decir, el tamanio de la direccion del servidor
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    //pone a escuchar el socket por conexiones, el primero argumento es el socker y el segunos es el numero de conexxiones que se pueden poner en cola, es decir, el numero de clientes que pueden esperar a ser atendidos por el servidor, si se llega al limite de conexiones en cola, los clientes que intenten conectarse recibirán un error de conexión rechazada. En este caso, el servidor puede manejar hasta 5 conexiones en cola.
    listen(serverSocket, 5);

    cout << "Servidor esperando clientes..." << endl;

    while(true) {
        //el accept es una funcion que se llama para aceptar una conexion entrante, tiene 3 argumentos el primero es el socket, el segundo es un puntero a una estructura que se va a llenar con la direccion del cliente y el tercero es un puntero a un entero que se va a llenar con el tamano de la direccion del cliente, si la conexion es exitosa, la funcion devuelve un nuevo socket que se va a usar para comunicarse con el cliente, si hay un error devuelve -1
        int clientSocket = accept(serverSocket, NULL, NULL);

        if(fork() == 0) { // proceso hijo

            char buffer[1024] = {0};
            ssize_t bytes_read = read(clientSocket, buffer, sizeof(buffer) - 1);

            if (bytes_read > 0) {
                buffer[bytes_read] = '\0'; // asegurar fin de string
                cout << "Mensaje recibido del cliente (raw):" << endl;
                cout << buffer << endl;
                // Intentar deserializar como JSON
                try {
                    nlohmann::json json_msg = nlohmann::json::parse(buffer);
                    cout << "\nMensaje recibido (JSON parseado):" << endl;
                    for (auto it = json_msg.begin(); it != json_msg.end(); ++it) {
                        cout << it.key() << ": " << it.value() << endl;
                    }
                    // Mostrar el nombre del comando según el Type
                    if (json_msg.contains("Type")) {
                        int type_code = json_msg["Type"].get<int>();
                        MessageCode code = static_cast<MessageCode>(type_code);
                        string comando;
                        switch (code) {
                            case ViewTables:   comando = "ViewTables"; break;
                            case CreateOrder:  comando = "CreateOrder"; break;
                            case ViewOrders:   comando = "ViewOrders"; break;
                            case ModifyOrder:  comando = "ModifyOrder"; break;
                            case ViewProducts: comando = "ViewProducts"; break;
                            default:           comando = "Desconocido"; break;
                        }
                        cout << "\nComando recibido (Type): " << comando << endl;

                        // Si el comando es ViewOrders, responder con JSON de órdenes (datos quemados)
                        if (code == ViewOrders) {
                            nlohmann::json ordenes = {
                                {"ordenes", {
                                    { {"id", 1}, {"mesa", 5}, {"productos", { {"Pizza", 2}, {"Refresco", 3} } } },
                                    { {"id", 2}, {"mesa", 3}, {"productos", { {"Hamburguesa", 1}, {"Papas", 2} } } }
                                }}
                            };
                            std::string respuesta = ordenes.dump();
                            send(clientSocket, respuesta.c_str(), respuesta.size(), 0);
                            close(clientSocket);
                            return 0;
                        }

                        if (code == ViewProducts) {
                            nlohmann::json productos = {
                                {"productos", {
                                    { {"nombre", "Pizza"}, {"precio", 10.99} },
                                    { {"nombre", "Hamburguesa"}, {"precio", 8.99} }
                                }}
                            };
                            std::string respuesta = productos.dump();
                            send(clientSocket, respuesta.c_str(), respuesta.size(), 0);
                            close(clientSocket);
                            return 0;
                        }

                        if (code == ViewTables) {
                            nlohmann::json mesas = {
                                {"mesas", {
                                    { {"numero", 1}},
                                    { {"numero", 2}}
                                }}
                            };
                            std::string respuesta = mesas.dump();
                            send(clientSocket, respuesta.c_str(), respuesta.size(), 0);
                            close(clientSocket);
                            return 0;
                        }

                    }
                } catch (const std::exception& e) {
                    cout << "No se pudo parsear el mensaje como JSON: " << e.what() << endl;
                }
            } else {
                cout << "No se recibió mensaje o error de lectura." << endl;
            }

            send(clientSocket, "hola recibido", 17, 0);
            close(clientSocket);
            return 0;
        }
    }

    close(serverSocket);
}

