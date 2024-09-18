#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "Algoritmos.h"  // Incluir el archivo de cabecera donde están los algoritmos
#include <cmath> // Para cálculos de logaritmos y potencias

// Función para crear la gráfica de un algoritmo con comportamiento teórico y empírico
void createGraph(QString algorithmName, void (*sortFunction)(int[], int), QString complexity, std::string caseType) {
    // Crear la ventana de la gráfica
    QWidget *graphWindow = new QWidget;
    graphWindow->resize(800, 600);
    graphWindow->setWindowTitle(algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Crear la serie para graficar los tiempos de ejecución empíricos
    QtCharts::QLineSeries *empiricalSeries = new QtCharts::QLineSeries();
    empiricalSeries->setName("Tiempo de ejecución de " + algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Crear la serie para el comportamiento teórico
    QtCharts::QLineSeries *theoreticalSeries = new QtCharts::QLineSeries();
    theoreticalSeries->setName("Comportamiento Teórico (" + complexity + ")");

    // Variables para ajustar el eje Y dinámicamente
    double maxEmpiricalTime = 0;
    double maxTheoreticalTime = 0;

    // Variable para escalar los valores teóricos
    double scaleFactor = 1.0;

    // Generar y medir los tiempos para diferentes tamaños de N
    for (int n = 100; n <= 2000; n += 100) {
        double timeTaken = measureTime(n, sortFunction, caseType);  // Medir el tiempo de ejecución con el caso adecuado
        empiricalSeries->append(n, timeTaken);  // Añadir el valor empírico a la gráfica
        std::cout << "N = " << n << ", Tiempo = " << timeTaken << " segundos" << std::endl;

        // Calcular el comportamiento teórico
        double theoreticalTime;
        if (complexity == "O(n^2)") {
            theoreticalTime = n * n;
        } else if (complexity == "O(n log n)") {
            theoreticalTime = n * std::log(n);
        } else if (complexity == "O(n)") {
            theoreticalTime = n;
        } else if (complexity == "O(1)") {
            theoreticalTime = 1;
        }

        // Escalar el valor teórico según los valores empíricos
        if (n == 100) {
            scaleFactor = timeTaken / theoreticalTime;  // Establecer el factor de escala con el primer valor
        }
        theoreticalTime *= scaleFactor;  // Aplicar el factor de escala

        theoreticalSeries->append(n, theoreticalTime);  // Añadir valor teórico a la gráfica

        // Actualizar el máximo de cada serie
        if (timeTaken > maxEmpiricalTime) {
            maxEmpiricalTime = timeTaken;
        }
        if (theoreticalTime > maxTheoreticalTime) {
            maxTheoreticalTime = theoreticalTime;
        }
    }

    // Crear un gráfico
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(empiricalSeries);
    chart->addSeries(theoreticalSeries);
    chart->setTitle("Gráfico del " + algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Añadir ejes X e Y
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis;
    axisX->setTitleText("Tamaño del arreglo (N)");
    axisX->setRange(100, 2000);
    axisX->setTickCount(10);

    // Calcular el rango máximo en Y para incluir ambas series
    double maxY = std::max(maxEmpiricalTime, maxTheoreticalTime);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
    axisY->setTitleText("Tiempo de ejecución (unidades arbitrarias)");
    axisY->setRange(0, maxY * 1.1);  // Añadir 10% extra al rango Y para mayor claridad
    axisY->setTickCount(10);

    chart->setAxisX(axisX, empiricalSeries);
    chart->setAxisY(axisY, empiricalSeries);
    chart->setAxisY(axisY, theoreticalSeries);  // Asignar el mismo eje Y a la serie teórica

    // Crear una vista de gráfico
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Habilitar suavizado

    // Crear un layout y añadir el gráfico a la ventana
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView);
    graphWindow->setLayout(layout);

    // Mostrar la ventana de la gráfica
    graphWindow->show();
}

// Función principal para crear el menú de selección
int main(int argc, char *argv[]) {
    // Crear la aplicación Qt
    QApplication app(argc, argv);

    // Crear la ventana principal
    QWidget window;
    window.resize(600, 400);
    window.setWindowTitle("Seleccione un algoritmo y caso");

    // Crear layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);  // Establecer el espaciado general entre los algoritmos
    mainLayout->setContentsMargins(10, 10, 10, 10);  // Establecer márgenes exteriores

    // Función para añadir un algoritmo y sus botones a un layout
    auto addAlgorithmButtons = [&](QString name, void (*sortFunction)(int[], int)) {
        QLabel *label = new QLabel(name);  // Crear el label del algoritmo

        // Crear los botones para "Peor Caso", "Mejor Caso" y "Caso Promedio"
        QPushButton *peorCasoButton = new QPushButton("Peor Caso");
        QPushButton *mejorCasoButton = new QPushButton("Mejor Caso");
        QPushButton *casoPromedioButton = new QPushButton("Caso Promedio");

        // Definir comportamientos teóricos específicos por cada botón sin condicionales adicionales
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

        // Crear un layout horizontal para los botones
        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->setSpacing(5);  // Establecer espaciado entre los botones
        buttonLayout->addWidget(peorCasoButton);
        buttonLayout->addWidget(mejorCasoButton);
        buttonLayout->addWidget(casoPromedioButton);

        // Crear un layout vertical para el label y los botones
        QVBoxLayout *algorithmLayout = new QVBoxLayout;
        algorithmLayout->addWidget(label);
        algorithmLayout->addLayout(buttonLayout);
        algorithmLayout->setSpacing(0);  // Reducir aún más el espaciado entre el label y los botones
        algorithmLayout->setContentsMargins(0, 0, 0, 0);  // Eliminar márgenes adicionales

        // Añadir el layout del algoritmo al layout principal
        mainLayout->addLayout(algorithmLayout);
    };

    // Añadir algoritmos y sus botones al layout principal
    addAlgorithmButtons("BubbleSort", bubbleSort);
    addAlgorithmButtons("SelectionSort", selectionSort);
    addAlgorithmButtons("MergeSort", [](int arr[], int n) { mergeSort(arr, 0, n - 1); });

    // Añadir botones para Sorted Linked List y Binary Search Tree
    addAlgorithmButtons("Sorted Linked List", [](int arr[], int n) {
        // Aquí iría la lógica de ordenación para la lista enlazada ordenada
    });

    addAlgorithmButtons("Binary Search Tree Insert", [](int arr[], int n) {
        // Aquí iría la lógica para la inserción en el árbol binario de búsqueda
    });

    // Asignar el layout principal a la ventana
    window.setLayout(mainLayout);

    // Mostrar la ventana principal
    window.show();

    // Ejecutar el ciclo de eventos de Qt
    return app.exec();
}
