#include "mesaService.h"
#include <vector>
#include <algorithm>

static std::vector<int> mesas = {1,2,3,4,5,6,7,8,9,10};  // lista inicial

int obtenerNumeroMesas() {
    return mesas.size();
}

std::vector<int> obtenerListaMesas() {
    return mesas;
}

void agregarMesa(int id) {
    if (id <= 0) return;  // ID inválido
    if (std::find(mesas.begin(), mesas.end(), id) == mesas.end()) {
        mesas.push_back(id);
        std::sort(mesas.begin(), mesas.end());  // mantener orden
    }
}

void eliminarMesa(int id) {
    auto it = std::find(mesas.begin(), mesas.end(), id);
    if (it != mesas.end()) {
        mesas.erase(it);
    }
}

void actualizarListaMesas(const std::vector<int>& nuevaLista) {
    mesas = nuevaLista;
    std::sort(mesas.begin(), mesas.end());  // ordenar para presentación
    // Opcional: eliminar duplicados
    auto last = std::unique(mesas.begin(), mesas.end());
    mesas.erase(last, mesas.end());
}

bool existeMesa(int id) {
    return std::find(mesas.begin(), mesas.end(), id) != mesas.end();
}
