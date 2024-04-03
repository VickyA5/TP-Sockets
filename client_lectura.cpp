
#include <fstream>
#include <iostream>

#include "client_protocolo.h"
#define ERROR -1

/*
 *Lee la entrada estándar correspondiente al cliente y delega el manejo de las acciones
 *recibidas a clientProtocolo.
 */
int main(int argc, const char* argv[]) {
    try {
        if (argc == 3) {
            ClientProtocolo clientProtocolo(argv[1], argv[2]);
            std::string linea;
            std::string nombre_archivo;
            std::ifstream archivo(nombre_archivo);
            if (!archivo.is_open()) {
                return ERROR;
            }
            while (std::getline(archivo, linea)) {
                if (!linea.empty()) {
                    clientProtocolo.enviar_accion(linea);
                    clientProtocolo.recibir_respuesta();
                }
            }
            archivo.close();
            return 0;
        } else {
            std::cerr << "Llamada inválida, se debe ingresar " << argv[0]
                      << " <hostname> <servername> \n";
            return ERROR;
        }
    } catch (const std::exception& err) {
        std::cerr << "Algo salió mal: " << err.what() << "\n";
        return ERROR;
    } catch (...) {
        std::cerr << "Algo salió mal y se interceptó un error desconocido.\n";
        return ERROR;
    }
}
