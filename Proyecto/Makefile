CXX = g++
CXXFLAGS = -Wall

all: servidor cliente

servidor:
	$(CXX) $(CXXFLAGS) server/server.cpp -o build/servidor

cliente:
	$(CXX) $(CXXFLAGS) client/cliente.cpp -o build/cliente

clean:
	rm -f build/servidor build/cliente