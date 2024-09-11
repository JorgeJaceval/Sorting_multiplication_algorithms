#include <fstream> 
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void Dataset(int num_max, int cant, string name, int caso) {
    vector <int> vec;
    ofstream outputFile(name);
    random_device rd;  // Utilizado para inicializar el generador
    mt19937 gen(rd());
    if (outputFile.is_open()) { 
        outputFile << cant << " " << '\n';
        if (caso == 1) { //Unordered
        uniform_int_distribution<> distrib(-num_max, num_max);
        for (int i = 0; i < cant; i++) {
            outputFile << distrib(gen) << '\n';
            } 
        } else if (caso == 2) { // 50% ordered case
            uniform_int_distribution<> distrib(-num_max, num_max);
            for (int i = 0; i < cant * 0.5; i++) { //First half random
            outputFile << distrib(gen) << '\n';
            } 
            uniform_int_distribution<> binary(0, 1);
             // rest ascendente 
            for (int i = 0; i < cant * 0.5; i++) { 
                    vec.push_back(distrib(gen));
                }
            if (binary(gen) == 0) {
                sort(vec.begin(), vec.end());
            } else { 
                sort(vec.begin(), vec.end(), greater<int>());
            }
            for (int i = 0; i < cant * 0.5; i++) { 
                    outputFile << vec[i] << endl;
            }
         
        } else if (caso == 3) { // 10% ordered case
            uniform_int_distribution<> distrib(-num_max, num_max);
            for (int i = 0; i < cant * 0.9; i++) { //90% random
            outputFile << distrib(gen) << '\n';
            }
            uniform_int_distribution<> binary(0, 1);
            for (int i = 0; i < cant * 0.1; i++) { //10% se manda a un vector 
                    vec.push_back(distrib(gen));
            }
            if (binary(gen) == 0) { // Se ordena el vector
                sort(vec.begin(), vec.end()); //Ascendente
            } else { 
                sort(vec.begin(), vec.end(), greater<int>()); //Descendente
            }
            for (int i = 0; i < cant * 0.1; i++) {  // Se escribe en el archivo el vector ordenado
                    outputFile << vec[i] << '\n';
            } 
        }

        // Cerrar el archivo después de escribir
        outputFile.close();
        cout << "Archivo creado y datos escritos con éxito." << endl;

    } else {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
    }      
}
// 1 Unordered 
// 2 50% ordered
// 3 10% ordered

int main() {
    // Dataset(10000, 10000, "unordered_10000.txt", 1); Ejemplo
}
