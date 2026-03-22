CXX = g++
CXXFLAGS = -Wall

all: servidor cliente interfaces

interfaces:
	$(CXX) $(CXXFLAGS) models/interfaces.cpp services/productoService.cpp utils/Auxiliares.cpp -o build/interfaces

servidor:
	$(CXX) $(CXXFLAGS) server/server.cpp -o build/servidor

cliente:
	$(CXX) $(CXXFLAGS) client/cliente.cpp -o build/cliente

clean:
	rm -f build/servidor build/cliente build/interfaces