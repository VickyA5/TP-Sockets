
#include "client.h"
#include <iostream>
#include <cstring>

int main(int argc, const char* argv[]) {
    try {
        if (argc != 3)
            return -1;
        std::string linea;
        while (std::getline(std::cin, linea)) {

        }
    } catch (const std::exception& err) {
        std::cerr
                << "Algo salió mal: "
                << err.what()
                << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Algo salió mal y se interceptó un error desconocido.\n";
        return -1;
    }

};
