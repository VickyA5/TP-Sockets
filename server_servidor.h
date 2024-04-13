
#ifndef SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#define SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#include <iostream>
#include <vector>

#include "common_socket.h"


class Servidor {

private:
    Socket aceptador;
    int cantAcciones;
    std::vector<char> acciones;

    /*
     * Devuelve true si se recibió la instrucción NOP
     *
    bool seRecibioNOP(const std::vector<unsigned char>& datos); */

public:
    explicit Servidor(const char* nombre_aceptador);

    /*
     * Realiza el ciclo de recibir mensajes del cliente y responderle.
     * */
    int establecer_conexion();

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

    /*
     * Imprime por pantalla el numero de acciones realizadas.
     * */
    void imprimir_cant_acciones();
};


#endif  // SOCKETS_2024C1_VICKYA5_SERVIDOR_H
