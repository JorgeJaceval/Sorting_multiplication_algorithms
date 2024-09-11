#include <random>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;

// Función para generar datos aleatorios para las matrices.
void data_maker(int row, int col, vector<vector<int>>& matrix, int caso){
    random_device rd;  // Utilizado para inicializar el generador
    mt19937 gen(rd()); // Generador de números aleatorios Mersenne Twister. 
    uniform_int_distribution<> distrib(-10000,10000);
    if (caso == 1) {
        for (int i = 0; i < row; i++) { //Caso 1: Matriz asimetrica
            for (int j = 0; j < col; j++) {
                matrix[i][j] = (distrib(gen));
            }
        }
    } else { 
        for (int i = 0; i < row; i++) { // Caso 2: Matriz simetrica
            for (int j = 0; j < col; j++) {
                if (i <= j) { // Solo llena la matriz superior triangular y refleja el valor en la parte inferior.
                    matrix[i][j] = distrib(gen);
                    matrix[j][i] = matrix[i][j]; 
                }
        }
    }
    }
    return;
}

int tradicional(int num_row1, int num_col1, int num_row2, int num_col2, int caso) {
    vector<int> row1(num_col1, 0);
    vector<int> row2(num_col2, 0);
    vector<vector <int>> matrix1(num_row1, row1);
    vector<vector <int>> matrix2(num_row2, row2);
    vector<vector <int>> matrix_final(num_row2, row1); // La matriz resultante tiene dimensiones num_row1 x num_col2.

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;

    data_maker(num_row1, num_col1, matrix1, caso);
    data_maker(num_row2, num_col2, matrix2, caso);

    auto t1 = high_resolution_clock::now();
    for (int i = 0; i < num_col1; i++) { //Recorre las filas
        for(int j = 0; j < num_row2; j++) { //Recorre las columnas
            for (int r = 0; r < num_row2; r++) { //Calcula la suma del producto de la matriz 1 con la matriz 2 para cada valor de r con respecto a i, j.
                matrix_final[i][j] += matrix1[i][r] * matrix2[r][j];
            }
        }
    }
    auto t2 = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(t2 - t1); // Calcula el tiempo transcurrido
    return time.count(); // Retorna el tiempo en milisegundos

}

void transponer_matriz(const vector<vector<int>>& matrix, vector<vector<int>>& matrix_transpuesta) {
    int num_row = matrix.size();
    int num_col = matrix[0].size();

    // Transponer la matriz
    for (int i = 0; i < num_row; ++i) {
        for (int j = 0; j < num_col; ++j) {
            matrix_transpuesta[j][i] = matrix[i][j]; // Intercambia filas por columnas.
        }
    }
}

int optimizado(int num_row1, int num_col1, int num_row2, int num_col2, int caso) {
    vector<int> row1(num_col1, 0);
    vector<int> row2(num_col2, 0);
    vector<vector<int>> matrix1(num_row1, row1);
    vector<vector<int>> matrix2(num_row2, row2);
    vector<vector<int>> matrix_final(num_row1, row2);  // Ajustado para coincidir con num_row1 x num_col2

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;
    
    data_maker(num_row1, num_col1, matrix1, caso);
    data_maker(num_row2, num_col2, matrix2, caso);

    auto t1 = high_resolution_clock::now();
    // Transponer matrix2
    vector<vector<int>> matrix2_transpuesta(num_col2, row2);
    transponer_matriz(matrix2, matrix2_transpuesta);

    // Multiplicación de matrices
    for (int i = 0; i < num_row1; ++i) {
        for (int j = 0; j < num_col2; ++j) {
            int sum = 0;
            for (int r = 0; r < num_col1; ++r) {
                sum += matrix1[i][r] * matrix2_transpuesta[j][r];
            }
            matrix_final[i][j] = sum;
        }
    }
    auto t2 = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(t2 - t1);
    return time.count();
}



// Función para sumar dos matrices con un factor de escala.
vector<vector<int>>add_matrix(vector<vector<int>> matrix_A, vector<vector<int>> matrix_B, int split_index, int multiplier = 1) {
    for (auto i = 0; i < split_index; i++)
        for (auto j = 0; j < split_index; j++)
            matrix_A[i][j]
                = matrix_A[i][j]
                  + (multiplier * matrix_B[i][j]);
    return matrix_A;
}
// Función para multiplicar matrices usando el algoritmo de Strassen.
vector<vector<int>> multiply_matrix(vector<vector<int> > matrix_A, vector<vector<int> > matrix_B) {
    
    int col_1 = matrix_A[0].size();
    int row_1 = matrix_A.size();
    int col_2 = matrix_B[0].size();
    int row_2 = matrix_B.size();
 
    if (col_1 != row_2) {
        cout << "\n Las dimensiones no coinciden!\n";
        return {};
    }
 
    vector<int> result_matrix_row(col_2, 0);
    vector<vector<int> > result_matrix(row_1,
                                       result_matrix_row);
 
    if (col_1 == 1)
        result_matrix[0][0]
            = matrix_A[0][0] * matrix_B[0][0]; // Caso base: matrices 1x1.
    else {
        int split_index = col_1 / 2;
 
        vector<int> row_vector(split_index, 0);
 
        vector<vector<int> > a00(split_index, row_vector);
        vector<vector<int> > a01(split_index, row_vector);
        vector<vector<int> > a10(split_index, row_vector);
        vector<vector<int> > a11(split_index, row_vector);
        vector<vector<int> > b00(split_index, row_vector);
        vector<vector<int> > b01(split_index, row_vector);
        vector<vector<int> > b10(split_index, row_vector);
        vector<vector<int> > b11(split_index, row_vector);
 
        for (auto i = 0; i < split_index; i++)
            for (auto j = 0; j < split_index; j++) {
                a00[i][j] = matrix_A[i][j];
                a01[i][j] = matrix_A[i][j + split_index];
                a10[i][j] = matrix_A[split_index + i][j];
                a11[i][j] = matrix_A[i + split_index]
                                    [j + split_index];
                b00[i][j] = matrix_B[i][j];
                b01[i][j] = matrix_B[i][j + split_index];
                b10[i][j] = matrix_B[split_index + i][j];
                b11[i][j] = matrix_B[i + split_index]
                                    [j + split_index];
            }
 
        vector<vector<int> > p(multiply_matrix(
            a00, add_matrix(b01, b11, split_index, -1)));
        vector<vector<int> > q(multiply_matrix(
            add_matrix(a00, a01, split_index), b11));
        vector<vector<int> > r(multiply_matrix(
            add_matrix(a10, a11, split_index), b00));
        vector<vector<int> > s(multiply_matrix(
            a11, add_matrix(b10, b00, split_index, -1)));
        vector<vector<int> > t(multiply_matrix(
            add_matrix(a00, a11, split_index),
            add_matrix(b00, b11, split_index)));
        vector<vector<int> > u(multiply_matrix(
            add_matrix(a01, a11, split_index, -1),
            add_matrix(b10, b11, split_index)));
        vector<vector<int> > v(multiply_matrix(
            add_matrix(a00, a10, split_index, -1),
            add_matrix(b00, b01, split_index)));
 
        vector<vector<int> > result_matrix_00(add_matrix(
            add_matrix(add_matrix(t, s, split_index), u,
                       split_index),
            q, split_index, -1));
        vector<vector<int> > result_matrix_01(
            add_matrix(p, q, split_index));
        vector<vector<int> > result_matrix_10(
            add_matrix(r, s, split_index));
        vector<vector<int> > result_matrix_11(add_matrix(
            add_matrix(add_matrix(t, p, split_index), r,
                       split_index, -1),
            v, split_index, -1));
 
        for (auto i = 0; i < split_index; i++)
            for (auto j = 0; j < split_index; j++) {
                result_matrix[i][j]
                    = result_matrix_00[i][j];
                result_matrix[i][j + split_index]
                    = result_matrix_01[i][j];
                result_matrix[split_index + i][j]
                    = result_matrix_10[i][j];
                result_matrix[i + split_index]
                             [j + split_index]
                    = result_matrix_11[i][j];
            }
        // Limpieza de matrices temporales.
        a00.clear();
        a01.clear();
        a10.clear();
        a11.clear();
        b00.clear();
        b01.clear();
        b10.clear();
        b11.clear();
        p.clear();
        q.clear();
        r.clear();
        s.clear();
        t.clear();
        u.clear();
        v.clear();
        result_matrix_00.clear();
        result_matrix_01.clear();
        result_matrix_10.clear();
        result_matrix_11.clear();
    }
    return result_matrix;
}

void print(string display, vector<vector<int> > matrix,
           int start_row, int start_column, int end_row,
           int end_column)
{
    cout << endl << display << " =>" << endl;
    for (int i = start_row; i <= end_row; i++) {
        for (int j = start_column; j <= end_column; j++) {
            cout << setw(10);
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
    return;
}

// Función auxiliar de strassen
int strassen(int num_row1, int num_col1, int num_row2, int num_col2, int caso) {
    vector<int> row1(num_col1, 0);
    vector<int> row2(num_col2, 0);
    vector<vector <int>> matrix1(num_row1, row1);
    vector<vector <int>> matrix2(num_row2, row2);

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;

    data_maker(num_row1, num_col1, matrix1, caso);
    data_maker(num_row2, num_col2, matrix2, caso);
    
    auto t1 = high_resolution_clock::now();
    vector<vector<int> > result_matrix(multiply_matrix(matrix1, matrix2));
    auto t2 = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(t2 - t1);
    return time.count();
}

// Función para ejecutar pruebas de tiempo para diferentes algoritmos de multiplicación de matrices.
int testing(int row1, int col1, int row2, int col2, int caso, int algoritmo) {
    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;
    int tiempo;
    if (algoritmo == 1) {
        tiempo = tradicional(row1, col1, row2, col2, caso);
    } else if (algoritmo == 2) {
        tiempo = optimizado(row1, col1, row2, col2, caso);
    } else if (algoritmo == 3) {
        tiempo = strassen(row1, col1, row2, col2, caso);
    }
    return tiempo;
}
main() {    
    string line;
    string size;
    string caso;
    int num_alg = 3; // Número de algoritmos a probar.
    int ms;
    std::ifstream inputFile("Tests/matrices_test.txt"); // Abre el archivo para lectura
    if (!inputFile.is_open()) { // Verifica si el archivo se abrió correctamente
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1; // Salida con error
    }
    getline(inputFile, line);
    for (int i = 0; i < stoi(line); i++) {
            inputFile >> size >> caso;
            ms = testing(stoi(size), stoi(size), stoi(size), stoi(size), stoi(caso), 1);
            cout << "para el tamaño " << size << " caso " << caso << " algoritmo tradicional, el tiempo es " << ms << endl;
            ms = testing(stoi(size), stoi(size), stoi(size), stoi(size), stoi(caso), 2);
            cout << "para el tamaño " << size << " caso " << caso << " algoritmo optimizado, el tiempo es "<< ms << endl;
            ms = testing(stoi(size), stoi(size), stoi(size), stoi(size), stoi(caso), 3);
            cout << "para el tamaño " << size << " caso " << caso << " algoritmo strassen, el tiempo es " << ms << endl;
    }

    // print("Result Array", result_matrix, 0, 0, num_row1 - 1, num_col2 - 1); Para imprimir la matriz
    }