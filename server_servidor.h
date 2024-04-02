
#ifndef SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#define SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#include <iostream>
#include <vector>

#include "common_socket.h"

#define JUMP "JUMP"
#define UPPERCUT "UPPERCUT"
#define DUCK "DUCK"
#define HIT "HIT"
#define LEFT "LEFT"
#define RIGHT "RIGHT"
#define SIDEKICK "SIDEKICK"
#define HIGHKICK "HIGHKICK"
#define CANT_BYTES_MENSAJE 20

class Servidor {

private:
    Socket aceptador;
    int cantAcciones;

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
    std::vector<uint16_t> recibir_acciones(bool& was_closed);

    /*
     * Envía las acciones ya con los combos correspondientes al socket del cliente
     * de forma serializada.
     * */
    void enviar_mensaje(const std::vector<uint16_t>& acciones_interpretadas);

    /*
     * Devuelve las acciones serializadas teniendo en cuenta la conversión de
     * endiannes necesaria.
     * */
    std::vector<char> serializar_acciones(const std::vector<std::uint16_t>& acciones);

    /*
     * Imprime por pantalla el numero de acciones realizadas.
     * */
    void imprimir_cant_acciones();
};


#endif  // SOCKETS_2024C1_VICKYA5_SERVIDOR_H
