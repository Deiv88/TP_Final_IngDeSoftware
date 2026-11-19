#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include "FechaHora.h"
#include <string>

/**
 * @brief Utilitario para ingreso seguro y blindado por teclado (std::cin).
 * Evita bloqueos y bucles infinitos ante datos no validos.
 */
class InputHelper {
public:
    static int leerEntero(const std::string& prompt, int minVal = -2147483647, int maxVal = 2147483647);
    static std::string leerTextoNoVacio(const std::string& prompt);
    static FechaHora leerFechaHora();
    static void pausar();
    static void limpiarPantalla();
};

#endif // INPUTHELPER_H
