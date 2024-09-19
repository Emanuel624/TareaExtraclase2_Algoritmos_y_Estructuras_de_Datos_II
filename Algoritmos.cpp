#include "Algoritmos.h"
#include <chrono>
#include <random>  // Para generar numeros aleatorios

// Implementacion optimizada de Bubble Sort para arreglos de enteros
void bubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Intercambiar elementos si están fuera de orden
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // Si no hubo intercambios en una pasada completa, el arreglo ya esta ordenado
        if (!swapped) {
            break;
        }
    }
}


// Implementacion Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

// Implementacion Merge para MergeSort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];

    delete[] leftArr;
    delete[] rightArr;
}

//mergeSort como tal
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Generar el peor caso (arreglo en orden inverso)
void generateWorstCase(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = n - i;  // Llenar el arreglo en orden descendente
    }
}

// Generar el mejor caso (arreglo ya ordenado en orden ascendente)
void generateBestCase(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;  // Llenar el arreglo en orden ascendente
    }
}

// Generar un caso promedio (arreglo con numeros aleatorios)
void generateAverageCase(int arr[], int n) {
    std::random_device rd;  // Semilla aleatoria
    std::mt19937 gen(rd());  // Generador Mersenne Twister
    std::uniform_int_distribution<> dist(1, n);  // Distribucion uniforme entre 1 y n

    for (int i = 0; i < n; ++i) {
        arr[i] = dist(gen);  // Llenar el arreglo con valores aleatorios
    }
}

// Funcion para medir el tiempo de ejecucion de cualquier algoritmo
double measureTime(int n, void (*sortFunction)(int[], int), std::string caseType) {
    int* arr = new int[n];

    if (caseType == "best") {
        generateBestCase(arr, n);  // Generar el mejor caso
    } else if (caseType == "worst") {
        generateWorstCase(arr, n);  // Generar el peor caso
    } else if (caseType == "average") {
        generateAverageCase(arr, n);  // Generar el caso promedio
    }

    auto start = std::chrono::high_resolution_clock::now();
    sortFunction(arr, n);  // Ejecutar la funcion de ordenamiento
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    delete[] arr;  // Liberar la memoria
    return duration.count();
}
