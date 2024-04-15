
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
