CXX = g++
CXXFLAGS = -Wall -I./include

all: servidor cliente interfaces

interfaces:
	$(CXX) $(CXXFLAGS) models/interfaces.cpp server/productos/productoService.cpp server/utils/Auxiliares.cpp -o build/interfaces

servidor:
	$(CXX) $(CXXFLAGS) server/server.cpp server/server_socket.cpp server/server_service.cpp -o build/servidor

cliente:
	$(CXX) $(CXXFLAGS) client/cliente.cpp client/cliente_menus.cpp client/cliente_service.cpp client/cliente_socket.cpp -o build/cliente

clean:
	rm -f build/servidor build/cliente build/interfaces