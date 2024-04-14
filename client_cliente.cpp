
#include "client_cliente.h"

#include <fstream>
#include <string>
#include <vector>

Cliente::Cliente(const char* hostname, const char* servicio):
        clienteProtocolo(hostname, servicio) {}

/*int Cliente::ejecutar() {
    std::string linea;
    std::string nombre_archivo;
    std::cin >> nombre_archivo;
    std::ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        return ERROR;
    }
    while (std::getline(archivo, linea, '\n')) {
        if (!linea.empty()) {
            clienteProtocolo.enviar_acciones(linea);
            std::vector<char> respuesta = clienteProtocolo.recibir_respuesta();
            imprimir_acciones(respuesta);
        }
    }
    archivo.close();
    return 0;
}*/

void Cliente::ejecutar() {
    std::string linea;
    while (std::getline(std::cin, linea, '\n')) {
        if (!linea.empty()) {
            clienteProtocolo.enviar_acciones(linea);
            std::vector<char> respuesta = clienteProtocolo.recibir_respuesta();
            imprimir_acciones(respuesta);
        }
    }
}

void Cliente::imprimir_acciones(const std::vector<char>& buffer_acciones) {
    for (const char& byte: buffer_acciones) {
        std::cout << byte;
    }
    std::cout << std::endl;
}
