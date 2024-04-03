
#ifndef SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#define SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#include <iostream>
#include <vector>

#include "common_socket.h"


class Servidor {

private:
    Socket aceptador;
    int cantAcciones;
    std::vector<uint16_t> acciones;

    /*
     * Devuelve true si se recibió la instrucción NOP
     * */
    bool seRecibioNOP(const std::vector<unsigned char>& datos);

public:
    explicit Servidor(const char* nombre_aceptador);

    /*
     * Acepta la conexión con un único cliente y realiza el ciclo de recibir mensajes
     * dicho clientes y responderle-
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
    void enviar_mensaje();

    /*
     * Devuelve las acciones serializadas teniendo en cuenta la conversión de
     * endiannes necesaria.
     * */
    std::vector<uint16_t> serializar_acciones();

    /*
     * Imprime por pantalla el numero de acciones realizadas.
     * */
    void imprimir_cant_acciones();
};


#endif  // SOCKETS_2024C1_VICKYA5_SERVIDOR_H
