
#include "server_servidor.h"

Servidor::Servidor(const char* nombre_aceptador): servidorProtocolo(nombre_aceptador) {}

int Servidor::establecer_conexion() {
    bool conectado = true;
    while (conectado) {
        servidorProtocolo.recibir_acciones(&conectado);
        if (!conectado)
            break;
        servidorProtocolo.enviar_respuesta();
    }
    return 0;
}

void Servidor::imprimir_cant_acciones() {
    std::cout << "Actions: " << servidorProtocolo.getCantidadAcciones() << std::endl;
}
