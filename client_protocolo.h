
#ifndef SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H
#define SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "common_socket.h"

class ClientProtocolo {

private:
    const std::unordered_map<std::string, unsigned char> acciones;
    Socket socket;

    /*
     * Recibe una serie de acciones, toma cada una por separado y la serializa
     * de acuerdo con el protocolo del juego. Luego las devuelve en un vector.
     */
    std::vector<uint8_t> serializar(const std::string& acciones);

public:
    ClientProtocolo(const char *hostname, const char *linea);

    /*
     * Envía al socket las acciones serializadas sin modificarlas.
     */
    void enviar_accion(const std::string& linea);

    /*
     *
     * */
    void recibir_respuesta();
};



#endif  // SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H
