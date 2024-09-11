#include <fstream>
#include <chrono>
#include <bits/stdc++.h>
#include <string>
using namespace std;

// Función para dividir el vector y seleccionar un pivote para quicksort
int partition(vector<int> &values, int left, int right) {
    int pivotIndex = left + (right - left) / 2;  // Selecciona un pivote en el medio
    int pivotValue = values[pivotIndex];  // Valor del pivote
    int i = left, j = right;
    int temp;
    
    // Reorganiza el vector alrededor del pivote
    while(i <= j) {
        while(values[i] < pivotValue) {  // Encuentra un valor mayor al pivote
            i++;
        }
        while(values[j] > pivotValue) {  // Encuentra un valor menor al pivote
            j--;
        }
        if(i <= j) {
            // Intercambia los valores para mover elementos menores a la izquierda y mayores a la derecha
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }
    return i;  // Retorna el índice de partición
}

// Implementación de quicksort
void quicksort(vector <int>& vec, int left, int right) {
    if(left < right) {
        int pivotIndex = partition(vec, left, right);  // Obtiene el pivote
        quicksort(vec, left, pivotIndex - 1);  // Ordena la mitad izquierda
        quicksort(vec, pivotIndex, right);  // Ordena la mitad derecha
    }
}

// Función para mezclar dos mitades del vector en merge sort
void merge(vector<int>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear vectores temporales para las mitades
    vector<int> L(n1), R(n2);

    // Copiar los datos a los vectores temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = vec[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Fusionar los vectores temporales de nuevo en vec[]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        } else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

// Implementación de merge sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;  // Calcula el punto medio
    mergeSort(arr, left, mid);  // Ordena la primera mitad
    mergeSort(arr, mid + 1, right);  // Ordena la segunda mitad
    merge(arr, left, mid, right);  // Fusiona ambas mitades
}

// Función para ordenar usando Selection Sort
void selectionSort(vector<int>& vec, int n) {
    // Uno por uno mueve el límite de la sublista no ordenada
    for (int i = 0; i < n - 1; i++) {
        // Encuentra el mínimo en la sublista no ordenada
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[min_idx])
                min_idx = j;
        }
        // Intercambia el elemento mínimo con el primer elemento
        if (min_idx != i)
            swap(vec[min_idx], vec[i]);
    }
}

// Función para medir el tiempo de ejecución de los algoritmos de ordenamiento
int testing(string name_file, string algor) {
    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;
    string n;  // Cantidad de valores en el archivo
    string num;  // Valor entero en una línea
    vector <int> vec;  // Vector que se ordenará

    // Abre el archivo
    ifstream inputFile(name_file);
    if (!inputFile.is_open()) { 
        cerr << "Error al abrir el archivo :(" << endl;  
    }
    
    getline(inputFile, n);  // Lee el número de elementos
    for (int i = 0; i < stoi(n); i++) {  // Saca cada valor entero
        getline(inputFile, num);
        vec.push_back(stoi(num));
    } 

    // Mide el tiempo de ejecución del algoritmo de ordenamiento
    auto t1 = high_resolution_clock::now();
    if (algor == "selection") {
        selectionSort(vec, stoi(n));
    } else if (algor == "quick") {
        quicksort(vec, 0, stoi(n) - 1);
    } else if (algor == "merge") {
        mergeSort(vec, 0, stoi(n) - 1);
    } else if (algor == "sort") {
        sort(vec.begin(), vec.end());  // Usa la función sort de C++
    } else {
        cout << "Algoritmo no reconocido!" << endl;
    }
    auto t2 = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(t2 - t1);  // Calcula la duración
    return time.count();  // Retorna el tiempo en milisegundos
}

// Función para realizar pruebas automáticas sobre varios algoritmos
void automatic_testing(int casos, string archivo) {
    int selection = 0;
    int merge = 0;
    int quick = 0;
    int sort = 0;
    
    // Ejecuta el test para cada algoritmo varias veces
    for (int i = 0; i < casos; i++) {
        selection += testing(archivo, "selection");
        merge += testing(archivo, "merge");
        quick += testing(archivo, "quick");
        sort += testing(archivo, "sort");
    }

    // Calcula los promedios 
    selection = selection /casos;
    merge = merge / casos;
    quick = quick / casos;
    sort = sort / casos;

    // Imprime los tiempos promedio de cada algoritmo
    cout << "Para archivo " << archivo << endl;
    cout << "Tiempo promedio Selection Sort " << selection << "ms" << endl;
    cout << "Tiempo promedio Merge Sort " << merge << "ms" << endl;
    cout << "Tiempo promedio Quick Sort " << quick << "ms" << endl;
    cout << "Tiempo promedio std::sort " << sort << "ms" << endl;
}

int main() {
    automatic_testing(3, "Tests/unordered_10000000.txt");  // Realiza pruebas automáticas con 3 repeticiones
}
