
#ifndef SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H
#define SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "client_mapa_acciones.h"
#include "common_socket.h"

#define BYTES_HEADER 2

class ClientProtocolo {

private:
    Socket socket;
    MapaAcciones mapaAcciones;

public:
    ClientProtocolo(const char* hostname, const char* servicio);

    /*
     * Envía al socket las acciones serializadas con un NOP al final.
     */
    void enviar_acciones(const std::string& linea);

    /*
     * Recibe la respuesta del servidor en un vector de chars y la devuelve.
     * */
    std::vector<char> recibir_respuesta();
};


#endif  // SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H
