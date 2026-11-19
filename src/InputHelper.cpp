#include "../include/InputHelper.h"
#include <iostream>
#include <limits>
#include <cstdlib>

int InputHelper::leerEntero(const std::string& prompt, int minVal, int maxVal) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            if (valor >= minVal && valor <= maxVal) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return valor;
            } else {
                std::cout << "[Error] El valor debe estar entre " << minVal << " y " << maxVal << ".\n";
            }
        } else {
            std::cout << "[Error] Entrada invalida. Ingrese un numero entero.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string InputHelper::leerTextoNoVacio(const std::string& prompt) {
    std::string texto;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, texto);
        // Trim simple
        size_t primero = texto.find_first_not_of(" \t\r\n");
        if (primero != std::string::npos) {
            size_t ultimo = texto.find_last_not_of(" \t\r\n");
            return texto.substr(primero, (ultimo - primero + 1));
        }
        std::cout << "[Error] El campo no puede estar vacio.\n";
    }
}

FechaHora InputHelper::leerFechaHora() {
    while (true) {
        std::cout << "\n--- Ingreso de Fecha y Hora ---\n";
        int d = leerEntero("Dia (1-31): ", 1, 31);
        int m = leerEntero("Mes (1-12): ", 1, 12);
        int a = leerEntero("Anio (2026-2030): ", 2026, 2030);
        int h = leerEntero("Hora (0-23): ", 0, 23);
        int min = leerEntero("Minuto (0-59): ", 0, 59);

        if (FechaHora::esValida(d, m, a, h, min)) {
            return FechaHora(d, m, a, h, min);
        } else {
            std::cout << "[Error] La combinacion de fecha y hora no es valida en el calendario. Intente nuevamente.\n";
        }
    }
}

void InputHelper::pausar() {
    std::cout << "\nPresione ENTER para continuar...";
    std::cin.get();
}

void InputHelper::limpiarPantalla() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
