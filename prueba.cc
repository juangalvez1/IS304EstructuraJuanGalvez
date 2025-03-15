#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

int main() {
    std::fstream archivo("datos.txt", std::ios::app);  // Abre en modo append

    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        archivo << "Dato " << i << "\n";
        archivo.flush();  // Fuerza que los datos se guarden inmediatamente

        std::cout << "Escrito: Dato " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simula escritura gradual
    }

    return 0;
}
