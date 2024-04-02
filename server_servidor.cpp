
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

void Servidor::recibir_acciones(bool *conectado) {
    bool was_closed_tamanio = false;
    uint8_t tamanio = 0;
    //Primero recibo el tamaño del mensaje que contiene a las acciones
    aceptador.recvall(&tamanio, sizeof(tamanio), &was_closed_tamanio );
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
    acciones = protocolo.interpretar_acciones(buffer, cantAcciones);
}

void Servidor::enviar_mensaje() {
    // serializar mensaje teniendo en cuenta el endianess y sendall
    std::vector<char> acciones_serializadas = serializar_acciones(acciones);
    bool was_closed = false;
    aceptador.sendall(acciones_serializadas.data(), acciones_serializadas.size() * sizeof(char),
                      &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error: se cerro el socket del cliente.");
    }
}

// REVISAR
std::vector<char> Servidor::serializar_acciones(const std::vector<std::uint16_t>& acciones) {
    std::vector<char> buffer_serializado(acciones.size() * sizeof(std::uint16_t));

    for (std::size_t i = 0; i < acciones.size(); ++i) {
        uint16_t elemento_serializado = htons(acciones[i]);  // Convertir a big-endian

        // Copia los bytes de elemento_serializado al buffer_serializado
        std::memcpy(&buffer_serializado[i * sizeof(std::uint16_t)], &elemento_serializado,
                    sizeof(std::uint16_t));
    }

    return buffer_serializado;
}

void Servidor::imprimir_cant_acciones() { std::cout << "Actions: " << cantAcciones; }
