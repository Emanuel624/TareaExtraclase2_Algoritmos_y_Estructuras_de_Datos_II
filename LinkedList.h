#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>


// Nodo de la lista enlazada
struct Node {
    int data;
    Node* next;
};

// Declaracion de las funciones para la lista enlazada ordenada
void sortedInsert(Node** head, int data);
bool searchSortedLinkedList(Node* head, int target);

//Funcion para medir el tiempo
double measureSearchTime(Node* head, int target);

//Probar peor caso
void generateWorstCase(Node** head, int n);

//Pronar mejor caso
void generateBestCase(Node** head, int n);

//Probar caso promedio
void generateAverageCase(Node** head, int n);

//Toma de tiempo
double measureSearchTimeWithCase(Node** head, int n, std::string caseType);

#endif //LINKEDLIST_H
