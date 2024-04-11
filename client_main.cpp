
#include <iostream>

#include "client_cliente.h"
#define ERROR -1

/*
 * Chequea errores e inicializa al cliente.
 */
int main(int argc, const char* argv[]) {
    try {
        if (argc == 3) {
            Cliente cliente(argv[1], argv[2]);
            cliente.ejecutar();
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
