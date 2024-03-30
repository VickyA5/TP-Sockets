
#ifndef SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#define SOCKETS_2024C1_VICKYA5_SERVIDOR_H
#include "socket.h"
#include <iostream>
#include <vector>

class Servidor {

private:
    Socket aceptador;
    //Devuelve true si se recibió la instrucción NOP
    bool seRecibioNOP(const std::vector<unsigned char>& datos);

public:
    Servidor(const char *nombre_aceptador);
    //Dada la serie de acciones, identifica los combos y devuelve la serie de acciones
    //con los combos correspondientes.
    std::string identificar_combo();
    //EL socket aceptador acepta la comunicación con el cliente y se delega ...
    int establecer_conexion();
    std::string recibir_acciones();
};


#endif  // SOCKETS_2024C1_VICKYA5_SERVIDOR_H
