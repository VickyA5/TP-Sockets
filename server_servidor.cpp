
#include "server_servidor.h"

#include <cstring>
#include <utility>

#include <arpa/inet.h>

#include "common_liberror.h"
#include "server_protocolo.h"

Servidor::Servidor(const char* nombre_aceptador): aceptador(nombre_aceptador) {
    this->cantAcciones = 0;
    Socket peer = aceptador.accept();
    aceptador = std::move(peer);
}

int Servidor::establecer_conexion() {
    bool conectado = true;
    while (conectado) {
        recibir_acciones(&conectado);
        if (!conectado)
            break;
        enviar_mensaje();
    }
    return 0;
}

void Servidor::recibir_acciones(bool* conectado) {
    bool was_closed = false;
    char accion_actual = -1;
    std::vector<uint8_t> acciones_recibidas;
    while (accion_actual != 0x00) {
        aceptador.recvall(&accion_actual, sizeof(char), &was_closed);
        if (was_closed) {
            *conectado = false;
            return;
        }
        acciones_recibidas.push_back(accion_actual);
    }
    ServidorProtocolo protocolo;
    acciones = protocolo.interpretar_acciones(acciones_recibidas, cantAcciones);
}

void Servidor::enviar_mensaje() {
    bool was_closed = false;
    uint16_t header = acciones.size();
    //header = ntohs(header);
    aceptador.sendall(&header, sizeof(uint16_t), &was_closed);
    aceptador.sendall(acciones.data(),
                      acciones.size() * sizeof(char),
                      &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error: se cerro el socket del cliente.");
    }
}


void Servidor::imprimir_cant_acciones() { std::cout << "Actions: " << cantAcciones << std::endl; }
