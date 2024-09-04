// C++ program for implementation of
// selection sort
#include <fstream>
#include <chrono>
#include <bits/stdc++.h>
#include <string>
using namespace std;

// Function for Selection sort
void selectionSort(vector<int>& vec, int n)
{
    // One by one move boundary of
    // unsorted subarray
    for (int i = 0; i < n - 1; i++)
    {
        // Find the minimum element in
        // unsorted array
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (vec[j] < vec[min_idx])
                min_idx = j;
        }

        // Swap the found minimum element
        // with the first element
        if (min_idx != i)
            swap(vec[min_idx], vec[i]);
    }
}

int main() {
    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;
    string n;
    string num;
    vector <int> vec;

    ifstream inputFile("dataset.txt");
    if (!inputFile.is_open()) { 
        cerr << "Habrió mal" << endl; 
        return 1; 
    } else {
        cout << "habrió!!!!" << endl;
    }
    
    
    getline(inputFile, n);
    for (int i = 0; i < stoi(n); i++) {
        getline(inputFile, num);
        vec.push_back(stoi(num));
    } 
    auto t1 = high_resolution_clock::now();
    selectionSort(vec, stoi(n));
    auto t2 = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(t2 - t1);
    cout << "tiempo que se demoro: " << time.count() << "ms" << endl;
    return 0;
}