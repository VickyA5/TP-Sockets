
#include "server_servidor.h"

#include <cstring>
#include <utility>

#include <arpa/inet.h>

#include "common_liberror.h"
#include "server_protocolo.h"

Servidor::Servidor(const char* nombre_aceptador): aceptador(nombre_aceptador) {
    this->cantAcciones = 0;
}

int Servidor::establecer_conexion() {
    Socket peer = aceptador.accept();
    aceptador = std::move(peer);
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
    bool was_closed_tamanio = false;
    uint8_t tamanio = 0;
    // Primero recibo el tamaño del mensaje que contiene a las acciones
    aceptador.recvall(&tamanio, sizeof(tamanio), &was_closed_tamanio);
    if (was_closed_tamanio) {
        *conectado = false;
        return;
    }
    bool was_closed_mensaje = false;
    std::vector<uint8_t> buffer(tamanio);
    aceptador.recvall(buffer.data(), tamanio, &was_closed_mensaje);
    if (was_closed_mensaje) {
        *conectado = false;
        return;
    }
    ServidorProtocolo protocolo;
    // Almaceno en un vector de uint16_t ya que el protocolo pide que el header
    // sea de dos bytes sin signo, aunque los caracteres solo necesitarían un byte cada uno.
    acciones = protocolo.interpretar_acciones(buffer, cantAcciones);
}

void Servidor::enviar_mensaje() {
    std::vector<uint16_t > acciones_serializadas = serializar_acciones();
    bool was_closed = false;
    aceptador.sendall(acciones_serializadas.data(),
                      acciones_serializadas.size() * sizeof(uint16_t),
                      &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error: se cerro el socket del cliente.");
    }
}
//No estoy del tod0 segura si es necesario
std::vector<uint16_t> Servidor::serializar_acciones() {
    std::vector<uint16_t> buffer_serializado(acciones.size() * sizeof(std::uint16_t));

    for (std::size_t i = 0; i < acciones.size(); ++i) {
        uint16_t elemento_serializado = htons(acciones[i]);  // Convertir a big-endian
        buffer_serializado.push_back(elemento_serializado);
    }

    return buffer_serializado;
}

void Servidor::imprimir_cant_acciones() { std::cout << "Actions: " << cantAcciones << std::endl; }
