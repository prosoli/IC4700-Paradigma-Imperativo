#include <iostream>
#include "../utils/Auxiliares.h"

typedef struct ElementoLista{
    void* Informacion;
    OperacionesStructs Operaciones;
    ElementoLista* Siguiente = NULL;
}*PtrElemento;