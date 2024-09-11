#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

// Función que genera casos de prueba matrices
void generate_matrix(ofstream &file, int size, int caso) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(-100, 100);

    // Caso con tamaño size
    file << size << " " << caso <<endl;
}

int main() {
    // Abrir el archivo para escribir las matrices
    ofstream outfile("matrices_test.txt");

    // Verificar si el archivo se abrió correctamente
    if (!outfile.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }
    outfile << 8 << endl;
    // Generar matrices con tamaños 2^n, donde n está entre 4 y 7
    for (int i = 4; i <= 7; ++i) {
        int matrix_size = 1 << i; // Calcula 2^i
        generate_matrix(outfile, matrix_size, 1);
    }
    for (int i = 4; i <= 7; ++i) {
        int matrix_size = 1 << i; // Calcula 2^i
        generate_matrix(outfile, matrix_size, 2);
    }

    // Cerrar el archivo
    outfile.close();

    return 0;
}