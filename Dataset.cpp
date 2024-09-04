#include <fstream> 
#include <iostream>
#include <random>
using namespace std;

void Dataset(int num){
    ofstream outputFile("dataset.txt");
    if (outputFile.is_open()) {
        outputFile << "100000" << '\n';
        random_device rd;  // Utilizado para inicializar el generador
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, num);
        for (int i = 0; i < 100000; i++) {
            outputFile << distrib(gen) << '\n';
        }

        // Cerrar el archivo después de escribir
        outputFile.close();
        cout << "Archivo creado y datos escritos con éxito." << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
    }
}

int main() {
    Dataset(1000);
}