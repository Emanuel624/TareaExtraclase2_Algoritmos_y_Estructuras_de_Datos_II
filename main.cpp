#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "Algoritmos.h"  // Incluir el archivo de cabecera donde están los algoritmos

// Función para crear la gráfica de un algoritmo
void createGraph(QString algorithmName, void (*sortFunction)(int[], int)) {
    // Crear la ventana de la gráfica
    QWidget *graphWindow = new QWidget;
    graphWindow->resize(800, 600);
    graphWindow->setWindowTitle(algorithmName);

    // Crear la serie para graficar los tiempos de ejecución
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
    series->setName("Tiempo de ejecución de " + algorithmName);

    // Variables para ajustar el eje Y dinámicamente
    double maxTime = 0;

    // Generar y medir los tiempos para diferentes tamaños de N
    for (int n = 100; n <= 2000; n += 100) {
        double timeTaken = measureTime(n, sortFunction);  // Medir el tiempo de ejecución
        series->append(n, timeTaken);  // Añadir el valor a la gráfica
        std::cout << "N = " << n << ", Tiempo = " << timeTaken << " segundos" << std::endl;

        if (timeTaken > maxTime) {
            maxTime = timeTaken;  // Ajustar el rango del eje Y
        }
    }

    // Crear un gráfico
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Gráfico del " + algorithmName);

    // Añadir ejes X e Y
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis;
    axisX->setTitleText("Tamaño del arreglo (N)");
    axisX->setRange(100, 2000);
    axisX->setTickCount(10);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
    axisY->setTitleText("Tiempo de ejecución (segundos)");
    axisY->setRange(0, maxTime * 1.1);  // Añadir 10% extra
    axisY->setTickCount(10);

    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);

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

        // Conectar los botones con la función createGraph
        QObject::connect(peorCasoButton, &QPushButton::clicked, [=]() {
            createGraph(name + " (Peor Caso)", sortFunction);
        });
        // Aquí puedes añadir las conexiones para Mejor Caso y Caso Promedio si lo necesitas.

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

    // Añadir el algoritmo "All Sorted LinkedList Search"
    addAlgorithmButtons("All Sorted LinkedList Search", [](int arr[], int n) {
        // Aquí iría la función de búsqueda para el algoritmo de LinkedList ordenada
        // Ejemplo placeholder
    });

    // Añadir el algoritmo "Binary Search Tree Insert"
    addAlgorithmButtons("Binary Search Tree Insert", [](int arr[], int n) {
        // Aquí iría la función de inserción para el árbol binario de búsqueda
        // Ejemplo placeholder
    });

    // Asignar el layout principal a la ventana
    window.setLayout(mainLayout);

    // Mostrar la ventana principal
    window.show();

    // Ejecutar el ciclo de eventos de Qt
    return app.exec();
}
