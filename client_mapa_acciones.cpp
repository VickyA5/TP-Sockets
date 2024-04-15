
#include "client_mapa_acciones.h"

MapaAcciones::MapaAcciones():
        mapaAcciones({{"NOP", 0x00},
                      {"JUMP", 0x01},
                      {"RIGHT", 0x02},
                      {"LEFT", 0x03},
                      {"DUCK", 0x04},
                      {"HIT", 0x05}}) {}

int MapaAcciones::obtenerValor(const std::string& nombreAccion) const {
    auto it = mapaAcciones.find(nombreAccion);
    if (it != mapaAcciones.end()) {
        return it->second;
    } else {
        return -1;
    }
}

std::vector<uint8_t> MapaAcciones::serializar(const std::string& linea) {
    std::istringstream accion_stream(linea);
    std::string accion;
    std::vector<uint8_t> resultado;
    accion_stream >> std::ws;
    while (std::getline(accion_stream, accion, ' ')) {
        if (!accion.empty()) {
            auto it = mapaAcciones.find(accion);
            if (it != mapaAcciones.end()) {
                resultado.push_back(it->second);
            }
        }
    }
    resultado.push_back(mapaAcciones.at("NOP"));
    return resultado;
}
