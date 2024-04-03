
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

void ClientProtocolo::enviar_accion(const std::string& linea) {
    std::vector<uint8_t> serializado = serializar(linea);
    bool fue_cerrado = false;
    uint8_t tamanio = sizeof(uint8_t) * serializado.size();
    // Ya que por protocolo no se envía un header, debo enviar primero el tamaño
    // para que el server sepa cuánto va a recibir.
    socket.sendall(&tamanio, sizeof(tamanio), &fue_cerrado);
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

void ClientProtocolo::recibir_respuesta() {
    uint16_t tamanio_respuesta = 0;
    bool was_closed_tamanio = false;
    // Recivo el header primero ya que me indica el tamaño.
    socket.recvall(&tamanio_respuesta, 2, &was_closed_tamanio);
    if (was_closed_tamanio) {
        throw LibError(errno, "No se pudo recibir la respuesta del servidor\n");
    }
    tamanio_respuesta = ntohs(tamanio_respuesta);
    // El tamaño recibido no incluye al header el cual ocupa 2 bytes.
    // Además, los caracteres están almacenados en uint_16
    int bytes_recibir = (tamanio_respuesta * sizeof(uint16_t)) + 2;
    std::vector<uint16_t> respuesta(bytes_recibir);
    bool was_closed_mensaje = false;
    socket.recvall(respuesta.data(), bytes_recibir, &was_closed_mensaje);
    if (was_closed_mensaje) {
        throw LibError(errno, "No se pudo recibir la respuesta del servidor\n");
    }
    std::vector<char> buffer_convertido = convertir_endianness(respuesta);
    imprimir_respuesta(buffer_convertido);
}


std::vector<char> ClientProtocolo::convertir_endianness(const std::vector<uint16_t> buffer) {

    size_t tam_buffer_convertido = buffer.size() - 1;
    std::vector<char> buffer_convertido(tam_buffer_convertido);
    // La primera posición es del header, las descarto
    for (size_t i = 1; i < tam_buffer_convertido; i++) {
        uint16_t convertido_dos_bytes = ntohs(buffer[i]);
        char convertido_byte_menos_significativo = (char) convertido_dos_bytes;
        buffer_convertido[i-1] = convertido_byte_menos_significativo;
    }

    return buffer_convertido;
}
void ClientProtocolo::imprimir_respuesta(const std::vector<char>& buffer) {
    for (const char& byte: buffer) {
        std::cout << byte << " ";
    }
    std::cout << std::endl;
}
