CXX = g++
CXXFLAGS = -Wall -std=c++11 -I./include -pthread

all: servidor cliente


servidor:
	$(CXX) $(CXXFLAGS) server/server.cpp server/server_menus.cpp server/server_socket.cpp server/server_service.cpp server/ordenes/ordenService.cpp server/productos/productoService.cpp server/mesas/mesaService.cpp server/utils/Auxiliares.cpp -o build/servidor

cliente:
	$(CXX) $(CXXFLAGS) client/cliente.cpp client/cliente_menus.cpp client/cliente_service.cpp client/cliente_socket.cpp -o build/cliente

clean:
	rm -f build/servidor build/cliente 