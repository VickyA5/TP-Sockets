
#ifndef SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H
#define SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "socket.h"

class ClientProtocolo {

private:
    const std::unordered_map<std::string, unsigned char> acciones;
    Socket socket;
    //Recibe una serie de acciones, toma cada una por separado y la serializa
    //de acuerdo con el protocolo del juego. Luego las devuelve en un vector.
    std::vector<unsigned char> serializar(const std::string& acciones);

public:
    ClientProtocolo(const char *hostname, const char *linea);

    //Envía al socket las acciones serializadas sin modificarlas.
    void enviarAccion(const std::string& linea);


};



#endif  // SOCKETS_2024C1_VICKYA5_CLIENT_PROTOCOLO_H
