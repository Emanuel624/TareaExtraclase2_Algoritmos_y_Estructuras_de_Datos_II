#include "BinarySearchTree.h"
#include <iostream>
#include <chrono>  // Para medir el tiempo
#include <random>  // Para generar valores aleatorios en el caso promedio

// Funcion para crear un nuevo nodo
TreeNode* createNode(int data) {
    TreeNode* newNode = new TreeNode();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Funcion para insertar un valor en el árbol binario de búsqueda (BST)
TreeNode *insert(TreeNode* root, int data) {
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

// Función para medir el tiempo de inserción en el árbol binario de búsqueda (BST)
double measureBSTInsertTime(TreeNode* root, int data) {
    auto start = std::chrono::high_resolution_clock::now();
    root = insert(root, data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Función para generar diferentes casos de inserción en el BST
double measureBSTInsertTimeWithCase(TreeNode** root, int n, std::string caseType) {
    *root = nullptr;  // Asegurarse de que el árbol esté vacío

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, n);

    // Generar el caso correcto
    if (caseType == "best") {
        // Mejor caso: el árbol ya es un árbol completo y balanceado
        for (int i = 1; i <= n; ++i) {
            *root = insert(*root, i);  // Insertar en orden ascendente para que sea balanceado
        }
        return measureBSTInsertTime(*root, 1);  // El mejor caso es insertar un valor que ya esté presente

    } else if (caseType == "worst") {
        // Peor caso: insertar valores en orden ascendente para crear un árbol desbalanceado
        for (int i = 1; i <= n; ++i) {
            *root = insert(*root, i);
        }
        return measureBSTInsertTime(*root, n + 1);  // Insertar un valor que no esté presente

    } else if (caseType == "average") {
        // Caso promedio: insertar valores aleatorios
        for (int i = 1; i <= n; ++i) {
            *root = insert(*root, dist(gen));  // Insertar valores aleatorios
        }
        return measureBSTInsertTime(*root, dist(gen));  // Medir la inserción de un valor aleatorio
    }

    return 0.0;  // Por si el tipo de caso no coincide
}


