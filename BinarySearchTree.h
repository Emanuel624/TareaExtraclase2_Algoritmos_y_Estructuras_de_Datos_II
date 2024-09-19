
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>

// Definicion de la estructura del nodo del árbol binario de búsqueda (BST)
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

// Función para crear un nuevo nodo
TreeNode* createNode(int data);

// Función para insertar un valor en el BST
TreeNode* insert(TreeNode* root, int data);

//Obtener el tiempo de insercion
double measureBSTInsertTime(TreeNode* root, int data);

//Medir el tiempo para cada caso
double measureBSTInsertTimeWithCase(TreeNode** root, int n, std::string caseType);


#endif //BINARYSEARCHTREE_H
