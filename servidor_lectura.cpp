
#include <iostream>
#include <exception>
#include "servidor.h"
#define ERROR -1

int main(int argc, char *argv[]) { try {
        int ret = ERROR;
        if (argc == 2) {
            Servidor servidor(argv[1]);
            ret = servidor.establecer_conexion();
        } else {
            std::cerr << "Llamada al programa inválida. Se espera "
                      << argv[0]
                      << " <servname>\n";
            return ret;
        }
        return ret;
    } catch (const std::exception& err) {
        std::cerr
                << "Algo salió mal: "
                << err.what()
                << "\n";
        return ERROR;
    } catch (...) {
        std::cerr << "Algo salió mal y se interceptó un error desconocido.\n";
        return ERROR;
    } }
