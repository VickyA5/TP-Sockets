
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
    bool was_closed = false;
    socket.recvall(&tamanio_respuesta, 2, &was_closed);  // Recivo header primero
    if (was_closed) {
        throw LibError(errno, "No se pudo recibir la respuesta del servidor\n");
    }
    tamanio_respuesta = ntohs(tamanio_respuesta);
    std::vector<char> respuesta(tamanio_respuesta);
    socket.recvall(respuesta.data(), tamanio_respuesta, &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo recibir la respuesta del servidor\n");
    }
    std::vector<char> buffer_convertido = convertir_endianness(respuesta);
    imprimir_respuesta(buffer_convertido);
}

// Convierte de a dos bytes ya que dos bytes representan un caracter en ascii en hexa.
// Por ejemplo "J" = 0x4A
std::vector<char> ClientProtocolo::convertir_endianness(const std::vector<char> buffer) {

    size_t tam_buffer_convertido = buffer.size() - 2;
    std::vector<char> buffer_convertido(tam_buffer_convertido);
    // Las dos primeras posiciones son del header, las descarto.
    const char* ptr_original = &buffer[2];
    char* ptr_nuevo = &buffer_convertido[0];

    for (size_t i = 2; i < tam_buffer_convertido; i += sizeof(std::uint16_t)) {
        std::uint16_t valor_original = *(reinterpret_cast<const std::uint16_t*>(ptr_original));
        std::uint16_t valor_convertido = ntohs(valor_original);
        // Copio el valor convertido al nuevo buffer
        *(reinterpret_cast<std::uint16_t*>(ptr_nuevo)) = valor_convertido;

        // Avanzar punteros
        ptr_nuevo += sizeof(std::uint16_t);
        ptr_original += sizeof(std::uint16_t);
    }

    return buffer_convertido;
}

void ClientProtocolo::imprimir_respuesta(const std::vector<char>& buffer) {
    for (const char& byte: buffer) {
        std::cout << std::hex << (int)byte << " ";
    }
    std::cout << std::endl;
}
