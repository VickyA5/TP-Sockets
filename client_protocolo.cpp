
#include "client_protocolo.h"
#include <netinet/in.h>
#include "common_liberror.h"

ClientProtocolo::ClientProtocolo(const char* hostname, const char* servicio):
        socket(hostname, servicio),
        acciones({{"NOP", 0x00},
                  {"JUMP", 0x01},
                  {"RIGHT", 0x02},
                  {"LEFT", 0x03},
                  {"DUCK", 0x04},
                  {"HIT", 0x05}}) {}

// QUIZAS QUE EL DICCIONARIO SEA UNA CLASE PARA USARLO TAMB EN SERVER PROTOCOLO?

void ClientProtocolo::enviar_acciones(const std::string& linea) {
    std::vector<uint8_t> serializado = serializar(linea);
    bool fue_cerrado = false;
    uint8_t tamanio = sizeof(uint8_t) * serializado.size();
    socket.sendall(serializado.data(), tamanio, &fue_cerrado);
    if (fue_cerrado) {
        throw LibError(errno, "Error: no se pudo enviar el mensaje del cliente, "
                              "el socket del server se cerro");
    }
}

std::vector<uint8_t> ClientProtocolo::serializar(const std::string& linea) {
    std::istringstream accion_stream(linea);
    std::string accion;
    std::vector<uint8_t> resultado;
    accion_stream >> std::ws;
    while (std::getline(accion_stream, accion, ' ')) {
        if (!accion.empty()) {
            auto it = acciones.find(accion);
            if (it != acciones.end()) {
                resultado.push_back(it->second);
            }
        }
    }
    resultado.push_back(acciones.at("NOP"));
    return resultado;
}

std::vector<char> ClientProtocolo::recibir_respuesta() {
    uint16_t tamanio_respuesta = 0;
    bool was_closed_tamanio = false;
    socket.recvall(&tamanio_respuesta, BYTES_HEADER, &was_closed_tamanio);
    if (was_closed_tamanio) {
        throw std::runtime_error("No se pudo recibir la respuesta del servidor\n");
    }
    tamanio_respuesta = htons(tamanio_respuesta);
    int bytes_recibir = tamanio_respuesta * sizeof(char);
    std::vector<char> respuesta(bytes_recibir);
    bool was_closed_mensaje = false;
    socket.recvall(respuesta.data(), bytes_recibir, &was_closed_mensaje);
    if (was_closed_mensaje) {
        throw std::runtime_error("No se pudo recibir la respuesta del servidor\n");
    }
    return respuesta;
}
