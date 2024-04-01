
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

class Servidor {

private:
    Socket aceptador;
    //Devuelve true si se recibió la instrucción NOP
    bool seRecibioNOP(const std::vector<unsigned char>& datos);
    int cantAcciones;

public:
    Servidor(const char *nombre_aceptador);

    /*
     *
     *
     * */
    int establecer_conexion();

    /*
     *
     *
     * */
    std::vector<uint16_t> recibir_acciones(bool& was_closed);

    /*
     * Envía las acciones ya con los combos correspondientes al socket del cliente
     * de forma serializada.
     * */
    void enviar_mensaje(std::vector<uint16_t>& acciones_interpretadas);

    /*
     *
     * */
    std::vector<char> serializar_acciones(const std::vector<std::uint16_t>& acciones);
};


#endif  // SOCKETS_2024C1_VICKYA5_SERVIDOR_H
