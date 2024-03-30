
#include "servidor.h"

Servidor::Servidor(const char *nombre_aceptador) :
        aceptador(nombre_aceptador) {}

int Servidor::establecer_conexion() {
    Socket peer = aceptador.accept();
    aceptador = std::move(peer);
    recibir_acciones();
    return 0;
}

std::string Servidor::recibir_acciones() {
    std::vector<unsigned char> datos_recibidos;
    bool conexion_cerrada = false;
    std::string acciones_realizadas;

    while (!seRecibioNOP(datos_recibidos)) {
        int bytes_recibidos = socket.recvall(datos_recibidos, &conexion_cerrada);

        if (conexion_cerrada || bytes_recibidos == -1) {
            if (conexion_cerrada) {
                std::cerr << "Conexión cerrada por el cliente." << std::endl;
            } else {
                std::cerr << "Error al recibir datos del cliente." << std::endl;
            }
            break;
        }

        if (bytes_recibidos > 0) {
            std::string acciones = interpretarAcciones(datos_recibidos, bytes_recibidos);
            acciones_realizadas += acciones;
        }
    }

    return acciones_realizadas;
}

bool seRecibioNOP(const std::vector<unsigned char>& datos) {
    // Verificar si se recibió la instrucción NOP
    std::string accion_actual = interpretarAcciones(datos, datos.size());
    return (accion_actual.find("NOP") != std::string::npos);
}
