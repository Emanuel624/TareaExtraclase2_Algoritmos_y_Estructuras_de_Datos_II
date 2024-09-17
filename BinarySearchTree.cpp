#include "BinarySearchTree.h"
#include <iostream>

// Función para crear un nuevo nodo
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Función para insertar un valor en el árbol binario de búsqueda (BST)
Node *insert(Node* root, int data) {
    // Si el árbol está vacío, se crea un nuevo nodo
    if (root == nullptr) {
        return createNode(data);
    }

    // Si el valor es menor que el valor del nodo actual, insertarlo en el subárbol izquierdo
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    // Si el valor es mayor, insertarlo en el subárbol derecho
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    // Retornar la raíz sin cambios si el valor ya está en el árbol
    return root;
}

// Función para realizar el recorrido in-order del árbol binario
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);  // Recorrer el subárbol izquierdo
        std::cout << root->data << " ";  // Imprimir el valor del nodo
        inorderTraversal(root->right);  // Recorrer el subárbol derecho
    }
}

