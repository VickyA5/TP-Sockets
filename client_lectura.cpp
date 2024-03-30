
#include <iostream>
#include "client_protocolo.h"
#define ERROR  -1

//Lee la entrada estándar correspondiente al cliente y delega el manejo de las acciones
//recibidas a clientProtocolo.
int main(int argc, const char* argv[]) {
    try {
        if (argc != 3)
            return ERROR;
        ClientProtocolo clientProtocolo(argv[1],argv[2]);
        std::string linea;
        while (std::getline(std::cin, linea)) {
            clientProtocolo.enviarAccion(linea);
        }
    } catch (const std::exception& err) {
        std::cerr
                << "Algo salió mal: "
                << err.what()
                << "\n";
        return ERROR;
    } catch (...) {
        std::cerr << "Algo salió mal y se interceptó un error desconocido.\n";
        return ERROR;
    }

};
