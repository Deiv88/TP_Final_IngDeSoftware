#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include "Lista.h"
#include "Excepciones.h"
#include <fstream>
#include <string>

/**
 * @brief Clase Template para persistencia generica en archivos de texto estructurado.
 * Cumple con el requisito de reutilizacion de templates y manejo de archivos.
 */
template <typename T>
class GestorArchivos {
public:
    static void guardar(const std::string& ruta, const Lista<T>& lista) {
        std::ofstream archivo(ruta);
        if (!archivo.is_open()) {
            throw ArchivoException("No se pudo abrir el archivo para escritura: " + ruta);
        }
        for (int i = 0; i < lista.getTamanio(); ++i) {
            archivo << lista[i].toLineaArchivo() << "\n";
        }
        archivo.close();
    }

    static void cargar(const std::string& ruta, Lista<T>& lista) {
        lista.limpiar();
        std::ifstream archivo(ruta);
        if (!archivo.is_open()) {
            // Si el archivo no existe (primera ejecucion), la lista queda vacia
            return;
        }
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (!linea.empty()) {
                lista.agregar(T::fromLineaArchivo(linea));
            }
        }
        archivo.close();
    }
};

#endif // GESTORARCHIVOS_H
