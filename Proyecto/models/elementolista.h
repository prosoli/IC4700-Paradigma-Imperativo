#pragma once
#include <iostream>
#include "../models/operacionesstructs.h"

typedef struct ElementoLista{
    void* Informacion;
    OperacionesStructs Operaciones;
    ElementoLista* Siguiente = NULL;
}*PtrElemento;