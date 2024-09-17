#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include "BinarySearchTree.h"  // Incluir el archivo de cabecera del BST

// Función para convertir el BST en una cadena de texto (in-order traversal)
QString bstToString(Node* root) {
    QString result;
    if (root != nullptr) {
        result += bstToString(root->left);
        result += QString::number(root->data) + " ";
        result += bstToString(root->right);
    }
    return result;
}

int main(int argc, char *argv[]) {
    // Crear la aplicación Qt
    QApplication app(argc, argv);

    // Crear la ventana principal
    QWidget window;
    window.resize(400, 350);
    window.setWindowTitle("Árbol Binario de Búsqueda (BST)");

    // Crear el árbol binario de búsqueda (BST)
    Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    // Realizar el recorrido in-order del árbol y mostrar en la consola
    std::cout << "Recorrido in-order del BST: ";
    inorderTraversal(root);
    std::cout << std::endl;

    // Convertir el BST a una cadena de texto para mostrar en la ventana
    QString bstStr = bstToString(root);

    // Crear un QLabel para mostrar el recorrido in-order del BST
    QLabel *label = new QLabel("BST in-order traversal: " + bstStr);

    // Crear un layout y añadir el QLabel a la ventana
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    window.setLayout(layout);

    // Mostrar la ventana
    window.show();

    // Ejecutar el ciclo de eventos de Qt
    return app.exec();
}
