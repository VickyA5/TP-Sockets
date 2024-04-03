
#include "server_protocolo.h"

#include <algorithm>
#include <string>

// Interpreta de a una linea de acciones hasta encontrar un NOP.
std::vector<uint16_t> ServidorProtocolo::interpretar_acciones(const std::vector<uint8_t>& buffer,
                                                              int& cantAcciones) {
    std::vector<uint16_t> acciones_interpretadas;
    size_t i = 0;
    while (i < buffer.size()) {
        uint8_t accion_actual = buffer[i];
        switch (accion_actual) {
            case 0x00:  // NOP
                acciones_interpretadas.insert(acciones_interpretadas.begin(),
                                              acciones_interpretadas.size());
                return acciones_interpretadas;
                break;
            case 0x01:  // JUMP
                interpretar_jump(buffer, i, acciones_interpretadas, cantAcciones);
                break;
            case 0x02:  // RIGHT
                agregar_accion(RIGHT, acciones_interpretadas, cantAcciones);
                avanzar_buffer(i, 1);
                break;
            case 0x03:  // LEFT
                interpretar_left(buffer, i, acciones_interpretadas, cantAcciones);
                break;
            case 0x04:  // DUCK
                agregar_accion(DUCK, acciones_interpretadas, cantAcciones);
                avanzar_buffer(i, 1);
                break;
            case 0x05:  // HIT
                interpretar_hit(buffer, i, acciones_interpretadas, cantAcciones);
                break;
            default:
                avanzar_buffer(i, 1);  // NO DEBERÍA PASAR
                break;
        }
    }
    // Llega acá si el combo estaba al final de la serie de acciones
    return acciones_interpretadas;
}

void ServidorProtocolo::avanzar_buffer(size_t& index, size_t cantidad) { index += cantidad; }

void ServidorProtocolo::interpretar_jump(const std::vector<uint8_t>& buffer, size_t& index,
                                         std::vector<uint16_t>& acciones_interpretadas,
                                         int& cantAcciones) {

    if (index + 2 < buffer.size() && buffer[index + 1] == 0x01 && buffer[index + 2] == 0x05) {
        if (index == 0) {
            agregar_primer_accion(UPPERCUT, acciones_interpretadas, cantAcciones);
            avanzar_buffer(index, 3);
        } else {
            agregar_accion(UPPERCUT, acciones_interpretadas, cantAcciones);
            avanzar_buffer(index, 3);
        }
    } else {
        agregar_accion(JUMP, acciones_interpretadas, cantAcciones);
        avanzar_buffer(index, 1);
    }
}

void ServidorProtocolo::interpretar_left(const std::vector<uint8_t>& buffer, size_t& index,
                                         std::vector<uint16_t>& acciones_interpretadas,
                                         int& cantAcciones) {
    if (index + 3 < buffer.size() && buffer[index + 1] == 0x02 && buffer[index + 2] == 0x01 &&
        buffer[index + 3] == 0x05) {
        if (index == 0) {
            agregar_primer_accion(HIGHKICK, acciones_interpretadas, cantAcciones);
            avanzar_buffer(index, 4);
        } else {
            agregar_accion(HIGHKICK, acciones_interpretadas, cantAcciones);
            avanzar_buffer(index, 4);
        }
    } else {
        agregar_accion(LEFT, acciones_interpretadas, cantAcciones);
        avanzar_buffer(index, 1);
    }
}

void ServidorProtocolo::interpretar_hit(const std::vector<uint8_t>& buffer, size_t& index,
                                        std::vector<uint16_t>& acciones_interpretadas,
                                        int& cantAcciones) {
    if (index + 2 < buffer.size() && buffer[index + 1] == 0x04 && buffer[index + 2] == 0x03) {
        if (index == 0) {
            agregar_primer_accion(SIDEKICK, acciones_interpretadas, cantAcciones);
            avanzar_buffer(index, 3);
        } else {
            agregar_accion(SIDEKICK, acciones_interpretadas, cantAcciones);
            avanzar_buffer(index, 3);
        }
    } else {
        agregar_accion(HIT, acciones_interpretadas, cantAcciones);
        avanzar_buffer(index, 1);
    }
}

// Me guarda el ascii de la acción que se le pasa en el vector de datos.
void ServidorProtocolo::agregar_accion(const std::string& accion, std::vector<uint16_t>& datos,
                                       int& cantAcciones) {
    uint16_t espacio = 32;  // Espacio en ascii
    datos.push_back(espacio);

    std::vector<uint8_t> bytes_accion(accion.begin(), accion.end());
    std::transform(bytes_accion.begin(), bytes_accion.end(), std::back_inserter(datos),
                   [](uint8_t byte) { return static_cast<uint16_t>(byte); });

    cantAcciones += 1;
}

//Al estar almacenando ascii en uint_16, el byte más significativo será 0.
void ServidorProtocolo::agregar_primer_accion(const std::string& accion,
                                              std::vector<uint16_t>& datos, int& cantAcciones) {

    std::vector<uint8_t> bytes_accion(accion.begin(), accion.end());
    std::transform(bytes_accion.begin(), bytes_accion.end(), std::back_inserter(datos),
                   [](uint8_t byte) { return static_cast<uint16_t>(byte); });

    cantAcciones += 1;
}
