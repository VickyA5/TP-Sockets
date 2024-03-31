
#ifndef SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#define SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#include "socket.h"
#include <iostream>
#include <vector>

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
    void avanzar_buffer(size_t& index, size_t cantidad);
    void interpretar_jump(const std::vector<uint8_t>& buffer, size_t& index, std::vector<uint16_t>& acciones_interpretadas);
    void interpretar_left(const std::vector<uint8_t>& buffer, size_t& index, std::vector<uint16_t>& acciones_interpretadas);
    void interpretar_hit(const std::vector<uint8_t>& buffer, size_t& index, std::vector<uint16_t>& acciones_interpretadas);
    void agregar_accion(const std::string& accion, std::vector<uint16_t>& datos);
public:
    Servidor(const char *nombre_aceptador);
    //Dada la serie de acciones, identifica los combos y devuelve la serie de acciones
    //con los combos correspondientes.
    std::vector<uint16_t> interpretar_acciones(const std::vector<uint8_t>& buffer);
    //EL socket aceptador acepta la comunicación con el cliente y se delega ...
    int establecer_conexion();
    //Recibe las acciones serializadas del cliente y delega su interpretación.
    std::vector<uint16_t> recibir_acciones();
};


#endif  // SOCKETS_2024C1_VICKYA5_SERVIDOR_H
