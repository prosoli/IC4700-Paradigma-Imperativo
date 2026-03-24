#include "mesaService.h"

static int numeroMesas = 10;  // valor por defecto

int obtenerNumeroMesas() {
    return numeroMesas;
}

void actualizarNumeroMesas(int nuevoNumero) {
    if (nuevoNumero >= 0) {
        numeroMesas = nuevoNumero;
    }
}
