#include "LinkedList.h"
#include <iostream>

// Implementación para insertar en una lista enlazada ordenada
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

// Implementación para buscar en una lista enlazada ordenada
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

// Función para imprimir la lista enlazada
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
