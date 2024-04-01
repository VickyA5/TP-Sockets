
#ifndef SOCKETS_2024C1_VICKYA5_SERVIDOR_PROTOCOLO_H
#define SOCKETS_2024C1_VICKYA5_SERVIDOR_PROTOCOLO_H

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

class ServidorProtocolo {

private:
    /*
     * Avanza el iterador del buffer en la cantidad indicada.
     * */
    void avanzar_buffer(size_t& index, size_t cantidad);

    /*
     * Interpreta las acciones próximas a un jump. Si hay un combo que comienza en el jump,
     * concatena el combo al vector de acciones interpretadas. En caso contrario solamente
     * concatena el jump.
     * */
    void interpretar_jump(const std::vector<uint8_t>& buffer, size_t& index, std::vector<uint16_t>& acciones_interpretadas);

    /*
     * Interpreta las acciones próximas a un left. Si hay un combo que comienza en el left,
     * concatena el combo al vector de acciones interpretadas. En caso contrario solamente
     * concatena el left.
     * */
    void interpretar_left(const std::vector<uint8_t>& buffer, size_t& index, std::vector<uint16_t>& acciones_interpretadas);

    /*
     * Interpreta las acciones próximas a un hit. Si hay un combo que comienza en el hit,
     * concatena el combo al vector de acciones interpretadas. En caso contrario solamente
     * concatena el hit.
     * */
    void interpretar_hit(const std::vector<uint8_t>& buffer, size_t& index, std::vector<uint16_t>& acciones_interpretadas);

    /*
     * Agrega la accion recibida al vector de datos en formato ascii.
     * */
    void agregar_accion(const std::string& accion, std::vector<uint16_t>& datos);

public:

    /*
     * Dada la serie de acciones, identifica los combos y devuelve la serie de acciones
     * con los combos correspondientes. Debe recibir una serie de acciones válida que
     * finalice con NOP (00).
     * */
    std::vector<uint16_t> interpretar_acciones(const std::vector<uint8_t>& buffer);
};


#endif  // SOCKETS_2024C1_VICKYA5_SERVIDOR_PROTOCOLO_H
