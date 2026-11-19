#ifndef FECHAHORA_H
#define FECHAHORA_H

#include <iostream>
#include <string>

/**
 * @brief Modela una fecha y hora con validaciones de calendario gregoriano.
 * Incluye sobrecarga de operadores y funcion friend para salida formateada.
 */
class FechaHora {
private:
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;

    static bool esBisiesto(int a);
    static int diasDelMes(int m, int a);

public:
    FechaHora();
    FechaHora(int d, int m, int a, int h, int min);

    static bool esValida(int d, int m, int a, int h, int min);

    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAnio() const { return anio; }
    int getHora() const { return hora; }
    int getMinuto() const { return minuto; }

    std::string toString() const;

    // Sobrecargas de operadores
    bool operator==(const FechaHora& otra) const;
    bool operator!=(const FechaHora& otra) const;
    bool operator<(const FechaHora& otra) const;

    // Funcion friend justificada: permite serializar e imprimir de forma natural
    friend std::ostream& operator<<(std::ostream& os, const FechaHora& fh);
};

#endif // FECHAHORA_H
