#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <exception>
#include <string>

/**
 * @brief Excepcion base para errores del sistema de orquesta.
 * Hereda de std::exception respetando los contenidos de la catedra.
 */
class ExcepcionOrquesta : public std::exception {
protected:
    std::string mensaje;
public:
    explicit ExcepcionOrquesta(const std::string& msg) : mensaje(msg) {}
    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

class EntidadNoEncontradaException : public ExcepcionOrquesta {
public:
    explicit EntidadNoEncontradaException(const std::string& msg = "Entidad no encontrada")
        : ExcepcionOrquesta(msg) {}
};

class TurnoOcupadoException : public ExcepcionOrquesta {
public:
    explicit TurnoOcupadoException(const std::string& msg = "El horario ya se encuentra ocupado")
        : ExcepcionOrquesta(msg) {}
};

class DatoInvalidoException : public ExcepcionOrquesta {
public:
    explicit DatoInvalidoException(const std::string& msg = "El dato ingresado es invalido")
        : ExcepcionOrquesta(msg) {}
};

class ArchivoException : public ExcepcionOrquesta {
public:
    explicit ArchivoException(const std::string& msg = "Error al operar con el archivo")
        : ExcepcionOrquesta(msg) {}
};

class ReglaNegocioException : public ExcepcionOrquesta {
public:
    explicit ReglaNegocioException(const std::string& msg = "Violacion de regla de negocio")
        : ExcepcionOrquesta(msg) {}
};

#endif // EXCEPCIONES_H
