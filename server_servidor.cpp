
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
    bool was_closed = false;
    std::vector<uint16_t> acciones_interpretadas;
    while (!was_closed) {
        acciones_interpretadas = recibir_acciones(was_closed);
        if (!was_closed)  // ACA SE ESTA CERRANDO
            break;
        enviar_mensaje(acciones_interpretadas);
        // imprimir
    }
    return 0;
}

std::vector<uint16_t> Servidor::recibir_acciones(bool& was_closed) {

    std::vector<uint8_t> buffer(20);
    // int bytes_recibidos = 0;
    while (not was_closed) {
        aceptador.recvsome(buffer.data(), 3, &was_closed);
    }
    ServidorProtocolo protocolo;
    std::vector<uint16_t> acciones_realizadas =
            protocolo.interpretar_acciones(buffer, cantAcciones);
    return acciones_realizadas;
}

void Servidor::enviar_mensaje(const std::vector<uint16_t>& acciones_interpretadas) {
    // serializar mensaje teniendo en cuenta el endianess y sendall
    std::vector<char> acciones_serializadas = serializar_acciones(acciones_interpretadas);
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
