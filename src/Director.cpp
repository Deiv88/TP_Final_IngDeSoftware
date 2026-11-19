#include "../include/Director.h"
#include <sstream>

Director::Director() : id(0), nombre(""), especialidad("") {}

Director::Director(int id, const std::string& nombre, const std::string& especialidad)
    : id(id), nombre(nombre), especialidad(especialidad) {}

Director::~Director() {}

bool Director::operator==(const Director& otro) const {
    return id == otro.id;
}

std::string Director::toLineaArchivo() const {
    std::ostringstream ss;
    ss << id << ";" << nombre << ";" << especialidad;
    return ss.str();
}

Director Director::fromLineaArchivo(const std::string& linea) {
    std::istringstream ss(linea);
    std::string token;

    std::getline(ss, token, ';');
    int id = std::stoi(token);

    std::string nombre;
    std::getline(ss, nombre, ';');

    std::string especialidad;
    std::getline(ss, especialidad, ';');

    return Director(id, nombre, especialidad);
}

std::ostream& operator<<(std::ostream& os, const Director& d) {
    os << "[ID: " << d.id << "] " << d.nombre 
       << " | Especialidad/Catedra: " << d.especialidad;
    return os;
}
