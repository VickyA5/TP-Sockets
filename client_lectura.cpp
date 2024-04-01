
#include <iostream>
#include <fstream>
#include "client_protocolo.h"
#define ERROR  -1

/*
 *Lee la entrada estándar correspondiente al cliente y delega el manejo de las acciones
 *recibidas a clientProtocolo.
 */
int main(int argc, const char* argv[]) {
    try {
        if (argc == 4){
            ClientProtocolo clientProtocolo(argv[1],argv[2]);
            std::string linea;
            std::ifstream archivo(argv[3]);
            if(!archivo.is_open()) {
                return ERROR;
            }
            while (std::getline(archivo, linea)) {
                if (!linea.empty() && linea[0] != '#') {
                    clientProtocolo.enviar_accion(linea);
                    clientProtocolo.recibir_mensaje();
                }
            }
            archivo.close();
            return 0;
        } else {
            std::cerr << "Llamada inválida, se debe ingresar "
                      << argv[0]
                      << " <hostname> <servername> <actions.txt>\n";
            return ERROR;
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
