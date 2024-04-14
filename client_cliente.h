
#ifndef SOCKETS_2024C1_VICKYA5_CLIENT_CLIENTE_H
#define SOCKETS_2024C1_VICKYA5_CLIENT_CLIENTE_H

#include <vector>

#include "client_protocolo.h"
#define ERROR -1

class Cliente {
private:
    ClientProtocolo clienteProtocolo;

public:
    Cliente(const char* hostname, const char* servicio);

    /*
     * Ejecuta el ciclo necesario para el envío de mensajes al servidor y la obtención de
     * sus respuestas.
     * */
    void ejecutar();

    /*
     * Imprime por pantalla las acciones recibidas del servidor.
     * */
    void imprimir_acciones(const std::vector<char>& buffer_acciones);
};


#endif  // SOCKETS_2024C1_VICKYA5_CLIENT_CLIENTE_H
