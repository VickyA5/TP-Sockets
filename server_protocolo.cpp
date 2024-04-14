
#include "server_protocolo.h"

ServidorProtocolo::ServidorProtocolo(const char* nombre_aceptador): aceptador(nombre_aceptador) {

    this->cantAcciones = 0;
    Socket peer = aceptador.accept();
    aceptador = std::move(peer);
}

void ServidorProtocolo::recibir_acciones(bool* conectado) {
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
    acciones = servidorCombos.interpretar_acciones(acciones_recibidas, cantAcciones);
}

void ServidorProtocolo::enviar_respuesta() {
    bool was_closed = false;
    uint16_t header = acciones.size();
    // header = htons(header);
    aceptador.sendall(&header, sizeof(uint16_t), &was_closed);
    aceptador.sendall(acciones.data(), acciones.size() * sizeof(char), &was_closed);
    if (was_closed) {
        throw std::runtime_error("Error: se cerro el socket del cliente.");
    }
}

int ServidorProtocolo::getCantidadAcciones() const { return cantAcciones; }
