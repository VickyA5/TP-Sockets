
#ifndef SOCKETS_2024C1_VICKYA5_SERVERCOMBOS_H
#define SOCKETS_2024C1_VICKYA5_SERVERCOMBOS_H

#include <iostream>
#include <string>
#include <vector>

#define JUMP_S "JUMP"
#define UPPERCUT_S "UPPERCUT"
#define DUCK_S "DUCK"
#define HIT_S "HIT"
#define LEFT_S "LEFT"
#define RIGHT_S "RIGHT"
#define SIDEKICK_S "SIDEKICK"
#define HIGHKICK_S "HIGHKICK"

#define NOP_P 0x00
#define JUMP_P 0x01
#define RIGHT_P 0x02
#define LEFT_P 0x03
#define DUCK_P 0x04
#define HIT_P 0x05

class ServidorCombos {

private:
    /*
     * Avanza el iterador del buffer en la cantidad indicada.
     * */
    void avanzar_buffer(size_t& index, size_t cantidad);

    /*
     * Interpreta las acciones próximas a un jump. Si hay un combo que comienza en el jump,
     * concatena el combo al vector de acciones interpretadas. En caso contrario, solamente
     * concatena el jump.
     * */
    void interpretar_jump(const std::vector<uint8_t>& buffer, size_t& index,
                          std::vector<char>& acciones_interpretadas, int& cantAcciones);

    /*
     * Interpreta las acciones próximas a un left. Si hay un combo que comienza en el left,
     * concatena el combo al vector de acciones interpretadas. En caso contrario, solamente
     * concatena el left.
     * */
    void interpretar_left(const std::vector<uint8_t>& buffer, size_t& index,
                          std::vector<char>& acciones_interpretadas, int& cantAcciones);

    /*
     * Interpreta las acciones próximas a un hit. Si hay un combo que comienza en el hit,
     * concatena el combo al vector de acciones interpretadas. En caso contrario, solamente
     * concatena el hit.
     * */
    void interpretar_hit(const std::vector<uint8_t>& buffer, size_t& index,
                         std::vector<char>& acciones_interpretadas, int& cantAcciones);

    /*
     * Agrega la accion recibida al vector de datos en formato ascii, y si corresponde agrega
     * previamente un caracter de espacio también en ascii. Incrementa cantAcciones en uno.
     * */
    void agregar_accion(const std::string& accion, std::vector<char>& datos, int& cantAcciones,
                        size_t index_actual);


public:
    /*
     * Dada la serie de acciones, identifica los combos y devuelve la serie de acciones
     * con los combos correspondientes. Debe recibir una serie de acciones válida que
     * finalice con NOP (00).
     * Además, actualiza la cantidad de acciones realizadas. cantAcciones debe estar
     * previamente inicializado.
     * */
    std::vector<char> interpretar_acciones(const std::vector<uint8_t>& buffer, int& cantAcciones);
};

#endif  // SOCKETS_2024C1_VICKYA5_SERVERCOMBOS_H
