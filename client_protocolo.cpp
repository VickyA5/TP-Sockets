
#include "client_protocolo.h"

#include <netinet/in.h>

ClientProtocolo::ClientProtocolo(const char* hostname, const char* servicio):
        socket(hostname, servicio) {}


void ClientProtocolo::enviar_acciones(const std::string& linea) {
    std::vector<uint8_t> serializado = mapaAcciones.serializar(linea);
    bool fue_cerrado = false;
    uint8_t tamanio = sizeof(uint8_t) * serializado.size();
    socket.sendall(serializado.data(), tamanio, &fue_cerrado);
    if (fue_cerrado) {
        throw std::runtime_error("Error: no se pudo enviar el mensaje del cliente, "
                                 "el socket del server se cerro");
    }
}

std::vector<char> ClientProtocolo::recibir_respuesta() {
    uint16_t tamanio_respuesta = 0;
    bool was_closed_tamanio = false;
    socket.recvall(&tamanio_respuesta, BYTES_HEADER, &was_closed_tamanio);
    if (was_closed_tamanio) {
        throw std::runtime_error("No se pudo recibir la respuesta del servidor\n");
    }
    tamanio_respuesta = htons(tamanio_respuesta);
    uint16_t bytes_recibir = tamanio_respuesta * sizeof(char);
    std::vector<char> respuesta(bytes_recibir);
    bool was_closed_mensaje = false;
    socket.recvall(respuesta.data(), bytes_recibir, &was_closed_mensaje);
    if (was_closed_mensaje) {
        throw std::runtime_error("No se pudo recibir la respuesta del servidor\n");
    }
    return respuesta;
}
