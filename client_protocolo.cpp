
#include "client_protocolo.h"

ClientProtocolo::ClientProtocolo(const char *hostname, const char *servicio)
        : socket(hostname, servicio),
        acciones({
                {"NOP", 0x00},
                {"JUMP", 0x01},
                {"RIGHT", 0x02},
                {"LEFT", 0x03},
                {"DUCK", 0x04},
                {"HIT", 0x05}
        }) {}

void ClientProtocolo::enviarAccion(const std::string& linea) {
    std::vector<unsigned char> serializado = serializar(linea);
    bool fue_cerrado = false;
    uint8_t tamanio = sizeof(uint8_t) * linea.size();
    socket.sendall(serializado.data(), tamanio,  &fue_cerrado);
}

std::vector<unsigned char> ClientProtocolo::serializar(const std::string& linea) {
    std::istringstream accion_stream(linea);
    std::string accion;
    std::vector<unsigned char> resultado;
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