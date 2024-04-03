
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
    void enviar_accion(const std::string& linea);

    /*
     *
     * */
    void recibir_respuesta();

    /*
     *
     * */
    void imprimir_respuesta(const std::vector<char>& buffer);

    /*
     *
     * */
    std::vector<char> convertir_endianness(std::vector<char> vector);
};


#endif  // SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H
