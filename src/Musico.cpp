#include "../include/Musico.h"
#include <sstream>

Musico::Musico() : id(0), nombre(""), instrumento(""), nivel(""), activo(true) {}

Musico::Musico(int id, const std::string& nombre, const std::string& instrumento, const std::string& nivel, bool activo)
    : id(id), nombre(nombre), instrumento(instrumento), nivel(nivel), activo(activo) {}

Musico::~Musico() {}

bool Musico::operator==(const Musico& otro) const {
    return id == otro.id;
}

std::string Musico::toLineaArchivo() const {
    std::ostringstream ss;
    ss << id << ";" << nombre << ";" << instrumento << ";" << nivel << ";" << (activo ? 1 : 0);
    return ss.str();
}

Musico Musico::fromLineaArchivo(const std::string& linea) {
    std::istringstream ss(linea);
    std::string token;
    
    std::getline(ss, token, ';');
    int id = std::stoi(token);

    std::string nombre;
    std::getline(ss, nombre, ';');

    std::string instrumento;
    std::getline(ss, instrumento, ';');

    std::string nivel;
    std::getline(ss, nivel, ';');

    std::getline(ss, token, ';');
    bool activo = (token == "1");

    return Musico(id, nombre, instrumento, nivel, activo);
}

std::ostream& operator<<(std::ostream& os, const Musico& m) {
    os << "[ID: " << m.id << "] " << m.nombre 
       << " | Instrumento: " << m.instrumento 
       << " | Nivel: " << m.nivel 
       << " | Estado: " << (m.activo ? "Activo" : "Baja Logica");
    return os;
}
