
#ifndef SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#define SOCKETS_2024C1_VICKYA5_SERVIDOR_H

#include <iostream>
#include <vector>
#include "common_socket.h"
#include "server_protocolo.h"


class Servidor {

private:
    ServidorProtocolo servidorProtocolo;

public:
    explicit Servidor(const char* nombre_aceptador);

    /*
     * Realiza el ciclo de recibir mensajes del cliente y responderle.
     * */
    int establecer_conexion();

    /*
     * Imprime por pantalla el numero de acciones realizadas.
     * */
    void imprimir_cant_acciones();
};


#endif  // SOCKETS_2024C1_VICKYA5_SERVIDOR_H
