
#include <cstring>

#include <arpa/inet.h>

#include "common_liberror.h"
#include "server_protocolo.h"
#include "server_servidor.h"

Servidor::Servidor(const char *nombre_aceptador) :
        aceptador(nombre_aceptador) {}


//QUIZAS AGREGAR CHEQUEOS DE WAS CLOSED
int Servidor::establecer_conexion() {
    Socket peer = aceptador.accept();
    aceptador = std::move(peer);
    bool was_closed = false;
    std::vector<uint16_t> acciones_interpretadas;
    while (!was_closed) {
        acciones_interpretadas = recibir_acciones(was_closed);
        if (!was_closed) break;
        enviar_mensaje(acciones_interpretadas);
        //imprimir_estado_juego();
    }
    return 0;
}

std::vector<uint16_t> Servidor::recibir_acciones(bool& was_closed) {
    unsigned int tamano_buffer = 1024;
    std::vector<uint8_t> buffer(tamano_buffer); //No estoy segura si no deberia usar uint16
    int bytes_recibidos = aceptador.recvall(buffer.data(), tamano_buffer, &was_closed);
    //Ya puse en el buffer las acciones serializadas.
    if (was_closed || bytes_recibidos == -1) {
        if (was_closed) {
            throw LibError(errno, "Error: el socket del cliente se cerró");
        } else {
            throw LibError(errno, "Error al recibir datos del cliente");
        }
    }
    ServidorProtocolo protocolo;
    std::vector<uint16_t> acciones_realizadas = protocolo.interpretar_acciones(buffer);

    return acciones_realizadas;
}

void Servidor::enviar_mensaje(std::vector<uint16_t>& acciones_interpretadas) {
    //serializar mensaje teniendo en cuenta el endianess y sendall
    std::vector<char> acciones_serializadas = serializar_acciones(acciones_interpretadas);
    bool was_closed = false;
    aceptador.sendall(acciones_serializadas.data(), sizeof(acciones_serializadas),
                &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error: se cerro el socket del cliente.");
    }
}

//REVISAR
std::vector<char> Servidor::serializar_acciones(const std::vector<std::uint16_t>& acciones) {
    std::vector<char> buffer_serializado(acciones.size() * sizeof(std::uint16_t));

    for (std::size_t i = 0; i < acciones.size(); ++i) {
        uint16_t elemento_serializado = htons(acciones[i]); // Convertir a big-endian

        // Copia los bytes de elemento_serializado al buffer_serializado
        std::memcpy(&buffer_serializado[i * sizeof(std::uint16_t)], &elemento_serializado, sizeof(std::uint16_t));
    }

    return buffer_serializado;
}
