
#ifndef SOCKETS_2024C1_VICKYA5_CLIENT_MAPA_ACCIONES_H
#define SOCKETS_2024C1_VICKYA5_CLIENT_MAPA_ACCIONES_H

#include <string>
#include <unordered_map>

class MapaAcciones {
private:
    std::unordered_map<std::string, int> mapaAcciones;

public:
    MapaAcciones();

    /*
     * Obtiene el código de una acción dado su nombre. Si la acción no existe, devuelve -1.
     * */
    int obtenerValor(const std::string& nombreAccion) const;
};

#endif  // SOCKETS_2024C1_VICKYA5_CLIENT_MAPA_ACCIONES_H
