
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Nodo de la lista enlazada
struct Node {
    int data;
    Node* next;
};

// Declaración de las funciones para la lista enlazada ordenada
void sortedInsert(Node** head, int data);
bool searchSortedLinkedList(Node* head, int target);
void printList(Node* head);

#endif //LINKEDLIST_H
