#include "../include/FechaHora.h"
#include "../include/Excepciones.h"
#include <iomanip>
#include <sstream>

bool FechaHora::esBisiesto(int a) {
    return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
}

int FechaHora::diasDelMes(int m, int a) {
    if (m < 1 || m > 12) return 0;
    switch (m) {
        case 2: return esBisiesto(a) ? 29 : 28;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}

bool FechaHora::esValida(int d, int m, int a, int h, int min) {
    if (a < 2000 || a > 2100) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > diasDelMes(m, a)) return false;
    if (h < 0 || h > 23) return false;
    if (min < 0 || min > 59) return false;
    return true;
}

FechaHora::FechaHora() : dia(1), mes(1), anio(2026), hora(0), minuto(0) {}

FechaHora::FechaHora(int d, int m, int a, int h, int min) {
    if (!esValida(d, m, a, h, min)) {
        throw DatoInvalidoException("Fecha u hora invalida");
    }
    dia = d;
    mes = m;
    anio = a;
    hora = h;
    minuto = min;
}

std::string FechaHora::toString() const {
    std::ostringstream ss;
    ss << std::setfill('0')
       << std::setw(2) << dia << "/"
       << std::setw(2) << mes << "/"
       << anio << " "
       << std::setw(2) << hora << ":"
       << std::setw(2) << minuto;
    return ss.str();
}

bool FechaHora::operator==(const FechaHora& otra) const {
    return dia == otra.dia &&
           mes == otra.mes &&
           anio == otra.anio &&
           hora == otra.hora &&
           minuto == otra.minuto;
}

bool FechaHora::operator!=(const FechaHora& otra) const {
    return !(*this == otra);
}

bool FechaHora::operator<(const FechaHora& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    if (dia != otra.dia) return dia < otra.dia;
    if (hora != otra.hora) return hora < otra.hora;
    return minuto < otra.minuto;
}

std::ostream& operator<<(std::ostream& os, const FechaHora& fh) {
    os << fh.toString();
    return os;
}
