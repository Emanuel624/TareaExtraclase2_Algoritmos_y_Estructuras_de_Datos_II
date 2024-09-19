#ifndef GRAPHS_H
#define GRAPHS_H

#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QWidget>
#include <cmath>

// Graficar los algortimos de ordenamiento
void createGraph(QString algorithmName, void (*sortFunction)(int[], int), QString complexity, std::string caseType);

//Graficar All Sorted LinkedLIst Search
void createGraphLinkedListSearch(QString algorithmName, QString complexity, std::string caseType);

//Graficar Binary Search Tree Insert
void createGraphBSTInsert(QString algorithmName, QString complexity, std::string caseType);
#endif //GRAPHS_H
