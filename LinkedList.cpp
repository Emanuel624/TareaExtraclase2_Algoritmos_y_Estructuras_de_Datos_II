#include "LinkedList.h"
#include <chrono>  // Para medir el tiempo

// Implementacion para insertar en una lista enlazada ordenada
void sortedInsert(Node** head, int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;

    if (*head == nullptr || (*head)->data >= data) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != nullptr && current->next->data < data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Implementacion para buscar en una lista enlazada ordenada
bool searchSortedLinkedList(Node* head, int target) {
    Node* current = head;
    while (current != nullptr && current->data <= target) {
        if (current->data == target) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Funcion para medir el tiempo de busqueda en la lista enlazada ordenada
double measureSearchTime(Node* head, int target) {
    auto start = std::chrono::high_resolution_clock::now();
    bool found = searchSortedLinkedList(head, target);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Funcion para generar el peor caso (elemento al final de la lista o no presente)
void generateWorstCase(Node** head, int n) {
    for (int i = 1; i <= n; ++i) {
        sortedInsert(head, i);
    }
}

// Funcion para generar el mejor caso (elemento al inicio)
void generateBestCase(Node** head, int n) {
    for (int i = 1; i <= n; ++i) {
        sortedInsert(head, i);
    }
}

// Funcion para generar el caso promedio (elemento en medio)
void generateAverageCase(Node** head, int n) {
    for (int i = 1; i <= n; ++i) {
        sortedInsert(head, i);
    }
}

// Funcion para medir el tiempo en funcioon del caso
double measureSearchTimeWithCase(Node** head, int n, std::string caseType) {
    *head = nullptr;  // Asegurarse de que la lista esté vacia

    // Generar el caso correcto
    int target;
    if (caseType == "best") {
        generateBestCase(head, n);
        target = 1;  // Mejor caso: el elemento esta al inicio
    } else if (caseType == "worst") {
        generateWorstCase(head, n);
        target = n + 1;  // Peor caso: el elemento no esta presente
    } else if (caseType == "average") {
        generateAverageCase(head, n);
        target = n / 2;  // Caso promedio: el elemento esta en medio
    }

    // Medir el tiempo de búsqueda
    return measureSearchTime(*head, target);
}