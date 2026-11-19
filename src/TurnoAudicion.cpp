#include "../include/TurnoAudicion.h"
#include <sstream>

TurnoAudicion::TurnoAudicion()
    : id(0), idMusico(0), idDirector(0), fechaHora(), salaVirtual("Sala-A"), estado("PROGRAMADA") {}

TurnoAudicion::TurnoAudicion(int id, int idMusico, int idDirector, const FechaHora& fechaHora, 
                             const std::string& salaVirtual, const std::string& estado)
    : id(id), idMusico(idMusico), idDirector(idDirector), fechaHora(fechaHora), 
      salaVirtual(salaVirtual), estado(estado) {}

TurnoAudicion::~TurnoAudicion() {}

void TurnoAudicion::cancelar() {
    estado = "CANCELADA";
}

void TurnoAudicion::reprogramar(const FechaHora& nuevaFecha) {
    fechaHora = nuevaFecha;
    estado = "REPROGRAMADA";
}

void TurnoAudicion::finalizar() {
    estado = "FINALIZADA";
}

bool TurnoAudicion::operator==(const TurnoAudicion& otro) const {
    return id == otro.id;
}

std::string TurnoAudicion::toLineaArchivo() const {
    std::ostringstream ss;
    ss << id << ";" 
       << idMusico << ";" 
       << idDirector << ";" 
       << fechaHora.getDia() << ";"
       << fechaHora.getMes() << ";"
       << fechaHora.getAnio() << ";"
       << fechaHora.getHora() << ";"
       << fechaHora.getMinuto() << ";"
       << salaVirtual << ";" 
       << estado;
    return ss.str();
}

TurnoAudicion TurnoAudicion::fromLineaArchivo(const std::string& linea) {
    std::istringstream ss(linea);
    std::string token;

    std::getline(ss, token, ';');
    int id = std::stoi(token);

    std::getline(ss, token, ';');
    int idMusico = std::stoi(token);

    std::getline(ss, token, ';');
    int idDirector = std::stoi(token);

    std::getline(ss, token, ';');
    int dia = std::stoi(token);

    std::getline(ss, token, ';');
    int mes = std::stoi(token);

    std::getline(ss, token, ';');
    int anio = std::stoi(token);

    std::getline(ss, token, ';');
    int hora = std::stoi(token);

    std::getline(ss, token, ';');
    int minuto = std::stoi(token);

    std::string sala;
    std::getline(ss, sala, ';');

    std::string estado;
    std::getline(ss, estado, ';');

    return TurnoAudicion(id, idMusico, idDirector, FechaHora(dia, mes, anio, hora, minuto), sala, estado);
}

std::ostream& operator<<(std::ostream& os, const TurnoAudicion& t) {
    os << "[Turno #" << t.id << "] "
       << "Musico ID: " << t.idMusico 
       << " | Director ID: " << t.idDirector
       << " | Fecha/Hora: " << t.fechaHora
       << " | Sala: " << t.salaVirtual
       << " | Estado: " << t.estado;
    return os;
}
