#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

int main() {
    // Semilla para la generación de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Distribución uniforme en el rango [5, 10000]
    std::uniform_real_distribution<double> dist(5.0, 10000.0);

    // Abrir el archivo para escribir
    std::ofstream archivo("RankingPuntajes.txt");
    
    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    // Generar y escribir los puntajes
    const int num_puntajes = 100000;
    for (int i = 0; i < num_puntajes; ++i) {
        double puntaje = dist(gen);
        archivo << std::fixed << std::setprecision(2) << puntaje << std::endl;
    }

    // Cerrar el archivo
    archivo.close();

    std::cout << "Se han generado y guardado " << num_puntajes << " puntajes en el archivo Puntaje.txt." << std::endl;

    return 0;
}