
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

// Definición de la estructura del nodo del árbol binario de búsqueda (BST)
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Función para crear un nuevo nodo
Node* createNode(int data);

// Función para insertar un valor en el BST
Node* insert(Node* root, int data);

// Función para imprimir el árbol en orden (in-order traversal)
void inorderTraversal(Node* root);

#endif //BINARYSEARCHTREE_H
