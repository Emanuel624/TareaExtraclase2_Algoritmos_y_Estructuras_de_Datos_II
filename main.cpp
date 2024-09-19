#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include "Graphs.h"  // Contiene createGraphLinkedListSearch y createGraphBSTInsert
#include "Algoritmos.h"   // Incluir el archivo de algoritmos

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.resize(600, 400);
    window.setWindowTitle("Seleccione un algoritmo y caso");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Funcion para añadir un algoritmo y sus botones a un layout
    auto addAlgorithmButtons = [&](QString name, void (*sortFunction)(int[], int)) {
        QLabel *label = new QLabel(name);

        QPushButton *peorCasoButton = new QPushButton("Peor Caso");
        QPushButton *mejorCasoButton = new QPushButton("Mejor Caso");
        QPushButton *casoPromedioButton = new QPushButton("Caso Promedio");

        QObject::connect(peorCasoButton, &QPushButton::clicked, [=]() {
            if (name == "MergeSort") {
                createGraph(name, sortFunction, "O(n log n)", "worst");
            } else {
                createGraph(name, sortFunction, "O(n^2)", "worst");
            }
        });

        QObject::connect(mejorCasoButton, &QPushButton::clicked, [=]() {
            if (name == "BubbleSort") {
                createGraph(name, sortFunction, "O(n)", "best");
            } else if (name == "MergeSort") {
                createGraph(name, sortFunction, "O(n log n)", "best");
            } else {
                createGraph(name, sortFunction, "O(n^2)", "best");
            }
        });

        QObject::connect(casoPromedioButton, &QPushButton::clicked, [=]() {
            if (name == "MergeSort") {
                createGraph(name, sortFunction, "O(n log n)", "average");
            } else {
                createGraph(name, sortFunction, "O(n^2)", "average");
            }
        });

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->setSpacing(5);
        buttonLayout->addWidget(peorCasoButton);
        buttonLayout->addWidget(mejorCasoButton);
        buttonLayout->addWidget(casoPromedioButton);

        QVBoxLayout *algorithmLayout = new QVBoxLayout;
        algorithmLayout->addWidget(label);
        algorithmLayout->addLayout(buttonLayout);
        algorithmLayout->setSpacing(0);
        algorithmLayout->setContentsMargins(0, 0, 0, 0);

        mainLayout->addLayout(algorithmLayout);
    };

    // Añadir algoritmos de ordenacion
    addAlgorithmButtons("BubbleSort", bubbleSort);
    addAlgorithmButtons("SelectionSort", selectionSort);
    addAlgorithmButtons("MergeSort", [](int arr[], int n) { mergeSort(arr, 0, n - 1); });

    // Diversos casos para All Sorted Linked List Search
    QLabel *linkedListLabel = new QLabel("All Sorted LinkedList Search");
    QPushButton *worstLinkedListButton = new QPushButton("Peor Caso");
    QPushButton *bestLinkedListButton = new QPushButton("Mejor Caso");
    QPushButton *averageLinkedListButton = new QPushButton("Caso Promedio");

    QObject::connect(worstLinkedListButton, &QPushButton::clicked, [=]() {
        createGraphLinkedListSearch("All Sorted LinkedList Search", "O(n)", "worst");
    });
    QObject::connect(bestLinkedListButton, &QPushButton::clicked, [=]() {
        createGraphLinkedListSearch("All Sorted LinkedList Search", "O(1)", "best");
    });
    QObject::connect(averageLinkedListButton, &QPushButton::clicked, [=]() {
        createGraphLinkedListSearch("All Sorted LinkedList Search", "O(n)", "average");
    });

    QHBoxLayout *linkedListButtonLayout = new QHBoxLayout;
    linkedListButtonLayout->setSpacing(5);
    linkedListButtonLayout->addWidget(worstLinkedListButton);
    linkedListButtonLayout->addWidget(bestLinkedListButton);
    linkedListButtonLayout->addWidget(averageLinkedListButton);

    QVBoxLayout *linkedListLayout = new QVBoxLayout;
    linkedListLayout->addWidget(linkedListLabel);
    linkedListLayout->addLayout(linkedListButtonLayout);
    mainLayout->addLayout(linkedListLayout);

    // Botones para "Binary Search Tree Insert"
    QLabel *bstLabel = new QLabel("Binary Search Tree Insert");
    QPushButton *worstBSTButton = new QPushButton("Peor Caso");
    QPushButton *bestBSTButton = new QPushButton("Mejor Caso");
    QPushButton *averageBSTButton = new QPushButton("Caso Promedio");

    // Conectar botones de Binary Search Tree Insert con la función de graficación
    QObject::connect(worstBSTButton, &QPushButton::clicked, [=]() {
        createGraphBSTInsert("Binary Search Tree Insert", "O(n)", "worst");
    });
    QObject::connect(bestBSTButton, &QPushButton::clicked, [=]() {
        createGraphBSTInsert("Binary Search Tree Insert", "O(log n)", "best");
    });
    QObject::connect(averageBSTButton, &QPushButton::clicked, [=]() {
        createGraphBSTInsert("Binary Search Tree Insert", "O(log n)", "average");
    });

    QHBoxLayout *bstButtonLayout = new QHBoxLayout;
    bstButtonLayout->setSpacing(5);
    bstButtonLayout->addWidget(worstBSTButton);
    bstButtonLayout->addWidget(bestBSTButton);
    bstButtonLayout->addWidget(averageBSTButton);

    QVBoxLayout *bstLayout = new QVBoxLayout;
    bstLayout->addWidget(bstLabel);
    bstLayout->addLayout(bstButtonLayout);
    mainLayout->addLayout(bstLayout);

    window.setLayout(mainLayout);
    window.show();

    return app.exec();
}
