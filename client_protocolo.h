
#ifndef SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H
#define SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "common_socket.h"

#define BYTES_HEADER 2

class ClientProtocolo {

private:
    Socket socket;
    const std::unordered_map<std::string, unsigned char> acciones;

    /*
     * Recibe una serie de acciones, toma cada una por separado y la serializa
     * de acuerdo con el protocolo del juego. Luego las devuelve en un vector.
     */
    std::vector<uint8_t> serializar(const std::string& acciones);

public:
    ClientProtocolo(const char* hostname, const char* servicio);

    /*
     * Envía al socket las acciones serializadas sin modificarlas.
     */
    void enviar_acciones(const std::string& linea);

    /*
     *
     * */
    std::vector<char> recibir_respuesta();

    /*
     *
     * */
    std::vector<char> convertir_endianness(std::vector<uint16_t> vector);
};


#endif  // SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H
