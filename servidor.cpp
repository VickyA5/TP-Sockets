
#include "servidor.h"

Servidor::Servidor(const char *nombre_aceptador) :
        aceptador(nombre_aceptador) {}

int Servidor::establecer_conexion() {
    Socket peer = aceptador.accept();
    aceptador = std::move(peer);
    recibir_acciones();
    return 0;
}

std::vector<uint16_t> Servidor::recibir_acciones() {
    unsigned int tamano_buffer = 1024;
    std::vector<uint8_t> buffer(tamano_buffer);
    bool conexion_cerrada = false;
    int bytes_recibidos = aceptador.recvall(buffer.data(), tamano_buffer, &conexion_cerrada);
    //Ya puse en el buffer las acciones serializadas.
    if (conexion_cerrada || bytes_recibidos == -1) {
        if (conexion_cerrada) {
            std::cerr << "Conexión cerrada por el cliente." << std::endl;
        } else {
            std::cerr << "Error al recibir datos del cliente." << std::endl;
        }
    }
    std::vector<uint16_t> acciones_realizadas = interpretar_acciones(buffer);

    return acciones_realizadas;
}


//Interpreta una sola serie de acciones o todo?
std::vector<uint16_t> Servidor::interpretar_acciones(const std::vector<uint8_t>& buffer) {
    std::vector<uint16_t> acciones_interpretadas;
    size_t i = 0;
    while (i < buffer.size()) {
        uint8_t accion_actual = buffer[i];
        switch (accion_actual) {
            case 0x00: // NOP
                avanzar_buffer(i, 1);
                break;
            case 0x01: // JUMP
                interpretar_jump(buffer, i, acciones_interpretadas);
                break;
            case 0x03: // LEFT
                interpretar_left(buffer, i, acciones_interpretadas);
                break;
            case 0x04: // DUCK
                agregar_accion(DUCK, acciones_interpretadas);
                avanzar_buffer(i, 1);
                break;
            case 0x05: // HIT
                interpretar_hit(buffer, i, acciones_interpretadas);
                break;
            default:
                avanzar_buffer(i, 1); //NO DEBERÍA PASAR
                break;
        }
    }
    //acciones_interpretadas.push_front(); EL TAMAÑO SIN CONTAR NOP
    return acciones_interpretadas;
}

void Servidor::avanzar_buffer(size_t& index, size_t cantidad) {
    index += cantidad;
}
//HACER QUE DEVUELVAN COMO LO PIDE EL ENUNCIADO
void Servidor::interpretar_jump(const std::vector<uint8_t>& buffer, size_t& index, std::vector<uint16_t>& acciones_interpretadas) {
    if (index + 2 < buffer.size() && buffer[index + 1] == 0x01 && buffer[index + 2] == 0x05) {
        agregar_accion(UPPERCUT, acciones_interpretadas);
        avanzar_buffer(index, 3);
    } else {
        agregar_accion(JUMP, acciones_interpretadas);
        avanzar_buffer(index, 1);
    }
}

void Servidor::interpretar_left(const std::vector<uint8_t>& buffer, size_t& index, std::vector<uint16_t>& acciones_interpretadas) {
    if (index + 3 < buffer.size() && buffer[index + 1] == 0x02 && buffer[index + 2] == 0x01 && buffer[index + 3] == 0x05) {
        agregar_accion(HIGHKICK, acciones_interpretadas);
        avanzar_buffer(index, 4);
    } else {
        agregar_accion(LEFT, acciones_interpretadas);
        avanzar_buffer(index, 1);
    }
}

void Servidor::interpretar_hit(const std::vector<uint8_t>& buffer, size_t& index, std::vector<uint16_t>& acciones_interpretadas) {
    if (index + 2 < buffer.size() && buffer[index + 1] == 0x04 && buffer[index + 2] == 0x03) {
        agregar_accion(SIDEKICK, acciones_interpretadas);
        avanzar_buffer(index, 3);
    } else {
        agregar_accion(HIT, acciones_interpretadas);
        avanzar_buffer(index, 1);
    }
}

void Servidor::agregar_accion(const std::string& accion, std::vector<uint16_t>& datos) {
    for (char c : accion) {
        uint16_t ascii_hex = static_cast<uint16_t>(c);
        datos.push_back(ascii_hex);
    }
}