#ifndef LISTA_H
#define LISTA_H

#include "Excepciones.h"
#include <cstddef>

/**
 * @brief Nodo generico para la lista enlazada.
 */
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    explicit Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}
};

/**
 * @brief Estructura de datos dinamica propia: Lista Enlazada Simple Template.
 * Implementada con punteros manuales (new/delete) conforme al programa de la materia.
 */
template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    int cantidad;

    void copiarDesde(const Lista<T>& otra) {
        cabeza = nullptr;
        cantidad = 0;
        Nodo<T>* actual = otra.cabeza;
        while (actual != nullptr) {
            agregar(actual->dato);
            actual = actual->siguiente;
        }
    }

public:
    Lista() : cabeza(nullptr), cantidad(0) {}

    // Constructor de copia (Manejo seguro de memoria dinamica)
    Lista(const Lista<T>& otra) : cabeza(nullptr), cantidad(0) {
        copiarDesde(otra);
    }

    // Sobrecarga del operador de asignacion
    Lista<T>& operator=(const Lista<T>& otra) {
        if (this != &otra) {
            limpiar();
            copiarDesde(otra);
        }
        return *this;
    }

    // Destructor: libera todos los nodos creados dinamicamente
    ~Lista() {
        limpiar();
    }

    void agregar(const T& dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo<T>* aux = cabeza;
            while (aux->siguiente != nullptr) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevo;
        }
        cantidad++;
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }

    int getTamanio() const {
        return cantidad;
    }

    T& obtener(int indice) {
        if (indice < 0 || indice >= cantidad) {
            throw DatoInvalidoException("Indice fuera de los limites de la lista");
        }
        Nodo<T>* aux = cabeza;
        for (int i = 0; i < indice; ++i) {
            aux = aux->siguiente;
        }
        return aux->dato;
    }

    const T& obtener(int indice) const {
        if (indice < 0 || indice >= cantidad) {
            throw DatoInvalidoException("Indice fuera de los limites de la lista");
        }
        Nodo<T>* aux = cabeza;
        for (int i = 0; i < indice; ++i) {
            aux = aux->siguiente;
        }
        return aux->dato;
    }

    T& operator[](int indice) {
        return obtener(indice);
    }

    const T& operator[](int indice) const {
        return obtener(indice);
    }

    bool eliminar(int indice) {
        if (indice < 0 || indice >= cantidad || cabeza == nullptr) {
            return false;
        }
        Nodo<T>* aEliminar = nullptr;
        if (indice == 0) {
            aEliminar = cabeza;
            cabeza = cabeza->siguiente;
        } else {
            Nodo<T>* aux = cabeza;
            for (int i = 0; i < indice - 1; ++i) {
                aux = aux->siguiente;
            }
            aEliminar = aux->siguiente;
            aux->siguiente = aEliminar->siguiente;
        }
        delete aEliminar;
        cantidad--;
        return true;
    }

    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
        cabeza = nullptr;
        cantidad = 0;
    }
};

#endif // LISTA_H
