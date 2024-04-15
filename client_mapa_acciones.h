
#ifndef SOCKETS_2024C1_VICKYA5_CLIENT_MAPA_ACCIONES_H
#define SOCKETS_2024C1_VICKYA5_CLIENT_MAPA_ACCIONES_H

#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class MapaAcciones {
private:
    std::unordered_map<std::string, int> mapaAcciones;

public:
    MapaAcciones();

    /*
     * Obtiene el código de una acción dado su nombre. Si la acción no existe, devuelve -1.
     * */
    int obtenerValor(const std::string& nombreAccion) const;

    /*
     * Recibe una serie de acciones, toma cada una y la serializa
     * de acuerdo con el protocolo del juego. Luego las devuelve en un vector.
     */
    std::vector<uint8_t> serializar(const std::string& acciones);
};

#endif  // SOCKETS_2024C1_VICKYA5_CLIENT_MAPA_ACCIONES_H
