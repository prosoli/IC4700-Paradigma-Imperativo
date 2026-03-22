#include <iostream>
#include <stdlib.h>
#include "../utils/Auxiliares.h"
using namespace std;

PtrElemento buscarElemento(PtrElemento& lista, int indice){
    PtrElemento Actual = lista;
    int contador = 1;
    bool encontrado = false;
    while (!encontrado == true && Actual != NULL){
        if (contador == indice){
            encontrado = true;
        } else {
            Actual = Actual->Siguiente;
            contador++;
        }
    }
    return Actual;
}

//Operaciones del CRUD

//Crear (C)
void insertarElemento(PtrElemento& lista, OperacionesStructs operaciones){
    //Crear elemento
    PtrElemento elemento = new(ElementoLista);
    elemento->Operaciones = operaciones;
    elemento->Informacion = operaciones.creacion();
    //Insertar elemento en la lista
    PtrElemento Auxiliar = lista;
    if (Auxiliar != NULL)
    {
        while (Auxiliar->Siguiente != NULL)
        {
            Auxiliar = Auxiliar->Siguiente;
        }
        Auxiliar->Siguiente = elemento;
    }
    else
    {
        lista = elemento;
    }
}

//Leer (R)
void leerElementos(PtrElemento& lista){
    if (lista == NULL){
        cout<<"No hay elementos que mostrar."<<endl;
    } else {
        int indice = 1;
        PtrElemento Actual = lista;
        while (Actual != NULL){
            cout<<indice<<". ";
            Actual->Operaciones.listado(Actual->Informacion);
            Actual = Actual->Siguiente;
            indice++;
        }
        cout << endl;
    }
}

//Actualizar (U)
void actualizarElemento(PtrElemento& lista){
    int indiceElemento = 0;
    cout<<"Ingrese el número del elemento a actualizar:"<<endl;
    cin>>indiceElemento;
    PtrElemento elemento = buscarElemento(lista, indiceElemento);
    if (elemento == NULL){
        cout<<"Elemento no encontrado."<<endl;
    } else {
        elemento->Operaciones.actualizacion(elemento->Informacion);
    }
}

//Eliminar (D)
void eliminarElemento(PtrElemento& lista){
    PtrElemento elemento = NULL;
    PtrElemento elementoAnterior = NULL;
    int indiceElemento = 0;
    cout<<"Ingrese el número del elemento a eliminar:"<<endl;
    cin>>indiceElemento;
    if (indiceElemento != 1){
        elementoAnterior = buscarElemento(lista, (indiceElemento - 1));
        if  (elementoAnterior != NULL){
            elemento = elementoAnterior->Siguiente;
        }
    } else {
        elemento = lista;
    }
    if (elemento == NULL){
        cout<<"Elemento no encontrado."<<endl;
    } else {
        if (elemento == lista) {
            lista = elemento->Siguiente;
            elemento->Operaciones.eliminacion(elemento->Informacion);
            delete(elemento);
            elemento = NULL;
        } else {
            elementoAnterior->Siguiente = elemento->Siguiente;
            elemento->Operaciones.eliminacion(elemento->Informacion);
            delete(elemento);
            elemento = NULL;
        }
    }
}
//

//Función para eliminar una lista por completo
void eliminarLista(PtrElemento& lista){
    PtrElemento Auxiliar = lista;
    while (Auxiliar != NULL){
        lista = lista->Siguiente;
        Auxiliar->Operaciones.eliminacion(Auxiliar->Informacion);
        delete(Auxiliar);
        Auxiliar = lista;
    }
}

