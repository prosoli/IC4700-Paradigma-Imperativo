#pragma once

struct OperacionesStructs {
    void*  (*creacion)(void);
    void  (*listado)(void*);
    void  (*actualizacion)(void*);
    void (*eliminacion)(void*);
};