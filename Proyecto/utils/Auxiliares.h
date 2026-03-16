#pragma once

typedef struct OperacionesStructs {
    void*  (*creacion)(void);
    void  (*listado)(void*);
    void  (*actualizacion)(void*);
    void (*eliminacion)(void*);
};

//Operaciones para los productos

void* crearProducto(void);

void actualizarProducto(void* informacion);

void leerProducto(void* informacion);

void eliminarProducto(void* informacion);

//