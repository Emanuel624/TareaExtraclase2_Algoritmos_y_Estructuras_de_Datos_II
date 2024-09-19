#include "Graphs.h"
#include "Algoritmos.h"  // Incluir las implementaciones de algoritmos
#include <iostream>
#include "LinkedList.h"
#include "BinarySearchTree.h"

// Definición de la funcion createGraph para BS, SS, MS
void createGraph(QString algorithmName, void (*sortFunction)(int[], int), QString complexity, std::string caseType) {
    // Crear la ventana de la grafica
    QWidget *graphWindow = new QWidget;
    graphWindow->resize(800, 600);
    graphWindow->setWindowTitle(algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Crear la serie para graficar los tiempos de ejecucion empiricos
    QtCharts::QLineSeries *empiricalSeries = new QtCharts::QLineSeries();
    empiricalSeries->setName("Tiempo de ejecución de " + algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Crear la serie para el comportamiento teorico
    QtCharts::QLineSeries *theoreticalSeries = new QtCharts::QLineSeries();
    theoreticalSeries->setName("Comportamiento Teórico (" + complexity + ")");

    // Variables para ajustar el eje Y dinamicamente
    double maxEmpiricalTime = 0;
    double maxTheoreticalTime = 0;

    // Variable para escalar los valores teóricos
    double scaleFactor = 1.0;

    // Generar y medir los tiempos para diferentes tamaños de N
    for (int n = 100; n <= 2000; n += 100) {
        double timeTaken = measureTime(n, sortFunction, caseType);  // Medir el tiempo de ejecucion con el caso adecuado
        empiricalSeries->append(n, timeTaken);  // Añadir el valor empirico a la grafica
        std::cout << "N = " << n << ", Tiempo = " << timeTaken << " segundos" << std::endl;

        // Calcular el comportamiento teorico
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

        // Escalar el valor teorico segun los valores empiricos
        if (n == 100) {
            scaleFactor = timeTaken / theoreticalTime;  // Establecer el factor de escala con el primer valor
        }
        theoreticalTime *= scaleFactor;  // Aplicar el factor de escala

        theoreticalSeries->append(n, theoreticalTime);  // Añadir valor teorico a la grafica

        // Actualizar el maximo de cada serie
        if (timeTaken > maxEmpiricalTime) {
            maxEmpiricalTime = timeTaken;
        }
        if (theoreticalTime > maxTheoreticalTime) {
            maxTheoreticalTime = theoreticalTime;
        }
    }

    // Crear un grafico
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(empiricalSeries);
    chart->addSeries(theoreticalSeries);
    chart->setTitle("Gráfico del " + algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Añadir ejes X e Y
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis;
    axisX->setTitleText("Tamaño del arreglo (N)");
    axisX->setRange(100, 2000);
    axisX->setTickCount(10);

    // Calcular el rango maximo en Y para incluir ambas series
    double maxY = std::max(maxEmpiricalTime, maxTheoreticalTime);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
    axisY->setTitleText("Tiempo de ejecución (unidades arbitrarias)");
    axisY->setRange(0, maxY * 1.1);  // Añadir 10% extra al rango Y para mayor claridad
    axisY->setTickCount(10);

    chart->setAxisX(axisX, empiricalSeries);
    chart->setAxisY(axisY, empiricalSeries);
    chart->setAxisY(axisY, theoreticalSeries);  // Asignar el mismo eje Y a la serie teorica

    // Crear una vista de gráfico
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Habilitar suavizado

    // Crear un layout y añadir el grafico a la ventana
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView);
    graphWindow->setLayout(layout);

    // Mostrar la ventana de la grafica
    graphWindow->show();
}

//Funcion para graficar los casos de LinkedLIstSearch
void createGraphLinkedListSearch(QString algorithmName, QString complexity, std::string caseType) {
    // Crear la ventana de la grafica
    QWidget *graphWindow = new QWidget;
    graphWindow->resize(800, 600);
    graphWindow->setWindowTitle(algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Crear la serie para graficar los tiempos de ejecucion empiricos
    QtCharts::QLineSeries *empiricalSeries = new QtCharts::QLineSeries();
    empiricalSeries->setName("Tiempo de ejecución de " + algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Crear la serie para el comportamiento teorico
    QtCharts::QLineSeries *theoreticalSeries = new QtCharts::QLineSeries();
    theoreticalSeries->setName("Comportamiento Teórico (" + complexity + ")");

    // Variables para ajustar el eje Y dinamicamente
    double maxEmpiricalTime = 0;
    double maxTheoreticalTime = 0;

    // Variable para escalar los valores teóricos
    double scaleFactor = 1.0;

    Node* head = nullptr;  // Lista enlazada para los casos

    // Generar y medir los tiempos para diferentes tamaños de N
    for (int n = 100; n <= 2000; n += 100) {
        double timeTaken = measureSearchTimeWithCase(&head, n, caseType);  // Medir el tiempo de ejecución con el caso adecuado
        empiricalSeries->append(n, timeTaken);  // Añadir el valor empirico a la grafica
        std::cout << "N = " << n << ", Tiempo = " << timeTaken << " segundos" << std::endl;

        // Calcular el comportamiento teorico
        double theoreticalTime;
        if (complexity == "O(n)") {
            theoreticalTime = n;
        } else if (complexity == "O(1)") {
            theoreticalTime = 1;
        }

        // Escalar el valor teorico según los valores empiricos
        if (n == 100) {
            scaleFactor = timeTaken / theoreticalTime;  // Establecer el factor de escala con el primer valor
        }
        theoreticalTime *= scaleFactor;  // Aplicar el factor de escala

        theoreticalSeries->append(n, theoreticalTime);  // Añadir valor teórico a la grafica

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
    axisX->setTitleText("Tamaño de la lista (N)");
    axisX->setRange(100, 2000);
    axisX->setTickCount(10);

    // Calcular el rango maximo en Y para incluir ambas series
    double maxY = std::max(maxEmpiricalTime, maxTheoreticalTime);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
    axisY->setTitleText("Tiempo de ejecución (unidades arbitrarias)");
    axisY->setRange(0, maxY * 1.1);  // Añadir 10% extra al rango
    axisY->setTickCount(10);

    chart->setAxisX(axisX, empiricalSeries);
    chart->setAxisY(axisY, empiricalSeries);
    chart->setAxisY(axisY, theoreticalSeries);  // Asignar el mismo eje Y a la serie teorica

    // Crear una vista de gráfico
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Habilitar suavizado

    // Crear un layout y añadir el grafico a la ventana
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView);
    graphWindow->setLayout(layout);

    // Mostrar la ventana de la gráfica
    graphWindow->show();
}


// Nueva función para graficar (BST)
void createGraphBSTInsert(QString algorithmName, QString complexity, std::string caseType) {
    // Crear la ventana de la grafica
    QWidget *graphWindow = new QWidget;
    graphWindow->resize(800, 600);
    graphWindow->setWindowTitle(algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Crear la serie para graficar los tiempos de ejecución empiricos
    QtCharts::QLineSeries *empiricalSeries = new QtCharts::QLineSeries();
    empiricalSeries->setName("Tiempo de ejecución de " + algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Crear la serie para el comportamiento teorico
    QtCharts::QLineSeries *theoreticalSeries = new QtCharts::QLineSeries();
    theoreticalSeries->setName("Comportamiento Teórico (" + complexity + ")");

    // Variables para ajustar el eje Y dinamicamente
    double maxEmpiricalTime = 0;
    double maxTheoreticalTime = 0;

    // Variable para escalar los valores teoricos
    double scaleFactor = 1.0;

    TreeNode* root = nullptr;  //(BST)

    // Generar y medir los tiempos para diferentes tamaños de N
    for (int n = 100; n <= 2000; n += 100) {
        double timeTaken = measureBSTInsertTimeWithCase(&root, n, caseType);  // Medir el tiempo de insercion de cada caso
        empiricalSeries->append(n, timeTaken);  // Añadir el valor empirico a la gráfica
        std::cout << "N = " << n << ", Tiempo = " << timeTaken << " segundos" << std::endl;

        // Calcular el comportamiento teorico
        double theoreticalTime;
        if (complexity == "O(log n)") {
            theoreticalTime = std::log(n);
        } else if (complexity == "O(n)") {
            theoreticalTime = n;
        }

        // Escalar el valor teorico según los valores empíricos
        if (n == 100) {
            scaleFactor = timeTaken / theoreticalTime;  // Establecer el factor de escala con el primer valor
        }
        theoreticalTime *= scaleFactor;  // Aplicar el factor de escala

        theoreticalSeries->append(n, theoreticalTime);  // Añadir valor teorico a la grafica

        // Actualizar el maximo de cada serie
        if (timeTaken > maxEmpiricalTime) {
            maxEmpiricalTime = timeTaken;
        }
        if (theoreticalTime > maxTheoreticalTime) {
            maxTheoreticalTime = theoreticalTime;
        }
    }

    // Crear un grafico
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(empiricalSeries);
    chart->addSeries(theoreticalSeries);
    chart->setTitle("Gráfico del " + algorithmName + " (" + QString::fromStdString(caseType) + ")");

    // Añadir ejes X e Y
    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis;
    axisX->setTitleText("Cantidad de elementos (N)");
    axisX->setRange(100, 2000);
    axisX->setTickCount(10);

    // Calcular el rango maximo en Y para incluir ambas series
    double maxY = std::max(maxEmpiricalTime, maxTheoreticalTime);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
    axisY->setTitleText("Tiempo de ejecución (unidades arbitrarias)");
    axisY->setRange(0, maxY * 1.1);  // Añadir 10% extra al rango Y para mayor claridad
    axisY->setTickCount(10);

    chart->setAxisX(axisX, empiricalSeries);
    chart->setAxisY(axisY, empiricalSeries);
    chart->setAxisY(axisY, theoreticalSeries);  // Asignar el mismo eje Y a la serie teorica

    // Crear una vista de grafico
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Habilitar suavizado

    // Crear un layout y añadir el grafico a la ventana
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView);
    graphWindow->setLayout(layout);

    // Mostrar la ventana de la grafica
    graphWindow->show();
}
