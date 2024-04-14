
#ifndef SOCKETS_2024C1_VICKYA5_SERVIDOR_PROTOCOLO_H
#define SOCKETS_2024C1_VICKYA5_SERVIDOR_PROTOCOLO_H

#include <iostream>
#include <utility>
#include <vector>

#include "common_socket.h"
#include "server_combos.h"

class ServidorProtocolo {


private:
    Socket aceptador;
    int cantAcciones;
    std::vector<char> acciones;
    ServidorCombos servidorCombos;

public:
    explicit ServidorProtocolo(const char* nombre_aceptador);

    /*
     * Recibe la serie de acciones serializadas del cliente y devuelve las acciones
     * con los combos correspondientes en ascii. La interpretación de los combos
     * se delega a ServidorProtocolo.
     * */
    void recibir_acciones(bool* conectado);

    /*
     * Envía las acciones ya con los combos correspondientes al socket del cliente
     * de forma serializada.
     * */
    void enviar_respuesta();

    int getCantidadAcciones() const;
};


#endif  // SOCKETS_2024C1_VICKYA5_SERVIDOR_PROTOCOLO_H
