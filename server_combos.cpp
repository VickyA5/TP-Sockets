
#include "server_combos.h"

#include <algorithm>
#include <string>

// Interpreta de a una linea de acciones hasta encontrar un NOP.
std::vector<char> ServidorCombos::interpretar_acciones(const std::vector<uint8_t>& buffer,
                                                       int& cantAcciones) {
    std::vector<char> acciones_interpretadas;
    size_t i = 0;
    while (i < buffer.size()) {
        uint8_t accion_actual = buffer[i];
        switch (accion_actual) {
            case NOP_P:  // "P" de protocolo (el valor hexadecimal)
                return acciones_interpretadas;
            case JUMP_P:
                interpretar_jump(buffer, i, acciones_interpretadas, cantAcciones);
                break;
            case RIGHT_P:
                agregar_accion(RIGHT_S, acciones_interpretadas, cantAcciones, i);
                avanzar_buffer(i, 1);
                break;
            case LEFT_P:
                interpretar_left(buffer, i, acciones_interpretadas, cantAcciones);
                break;
            case DUCK_P:
                agregar_accion(DUCK_S, acciones_interpretadas, cantAcciones, i);
                avanzar_buffer(i, 1);
                break;
            case HIT_P:
                interpretar_hit(buffer, i, acciones_interpretadas, cantAcciones);
                break;
            default:
                throw std::runtime_error("Error: se detectó una acción inválida.\n");
        }
    }
    return acciones_interpretadas;
}

void ServidorCombos::avanzar_buffer(size_t& index, size_t cantidad) { index += cantidad; }

void ServidorCombos::interpretar_jump(const std::vector<uint8_t>& buffer, size_t& index,
                                      std::vector<char>& acciones_interpretadas,
                                      int& cantAcciones) {

    if (index + 2 < buffer.size() && buffer[index + 1] == 0x01 && buffer[index + 2] == 0x05) {

        agregar_accion(UPPERCUT_S, acciones_interpretadas, cantAcciones, index);
        avanzar_buffer(index, 3);
    } else {
        agregar_accion(JUMP_S, acciones_interpretadas, cantAcciones, index);
        avanzar_buffer(index, 1);
    }
}

void ServidorCombos::interpretar_left(const std::vector<uint8_t>& buffer, size_t& index,
                                      std::vector<char>& acciones_interpretadas,
                                      int& cantAcciones) {
    if (index + 3 < buffer.size() && buffer[index + 1] == 0x02 && buffer[index + 2] == 0x01 &&
        buffer[index + 3] == 0x05) {
        agregar_accion(HIGHKICK_S, acciones_interpretadas, cantAcciones, index);
        avanzar_buffer(index, 4);
    } else {
        agregar_accion(LEFT_S, acciones_interpretadas, cantAcciones, index);
        avanzar_buffer(index, 1);
    }
}

void ServidorCombos::interpretar_hit(const std::vector<uint8_t>& buffer, size_t& index,
                                     std::vector<char>& acciones_interpretadas, int& cantAcciones) {
    if (index + 2 < buffer.size() && buffer[index + 1] == 0x04 && buffer[index + 2] == 0x03) {
        agregar_accion(SIDEKICK_S, acciones_interpretadas, cantAcciones, index);
        avanzar_buffer(index, 3);

    } else {
        agregar_accion(HIT_S, acciones_interpretadas, cantAcciones, index);
        avanzar_buffer(index, 1);
    }
}

void ServidorCombos::agregar_accion(const std::string& accion, std::vector<char>& datos,
                                    int& cantAcciones, size_t index_actual) {
    if (index_actual != 0) {
        char espacio = 32;  // Espacio en ascii
        datos.push_back(espacio);
    }
    /*
        for (char c: accion) {
            datos.push_back(c);
        }*/
    std::copy(accion.begin(), accion.end(), std::back_inserter(datos));

    cantAcciones += 1;
}
