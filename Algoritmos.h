#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <string>

// Declaracion de la función Bubble Sort
void bubbleSort(int arr[], int n);

// Declaracion de la función Selection Sort
void selectionSort(int arr[], int n);

// Declaracion de las funciones para Merge Sort
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);

// Funcion para generar un arreglo con los elementos en orden inverso (peor caso)
void generateWorstCase(int arr[], int n);

//Funcion para generar un arreglo con los elementos ya en orden ascedente
void generateBestCase(int arr[], int n);

//Funcion para generar un arreglo con elementos aleatorios
void generateAverageCase(int arr[], int n);

// Función general para medir el tiempo de ejecución de cualquier algoritmo (BS, SS, MS)
double measureTime(int n, void (*sortFunction)(int[], int), std::string caseType);

#endif // ALGORITMOS_H
