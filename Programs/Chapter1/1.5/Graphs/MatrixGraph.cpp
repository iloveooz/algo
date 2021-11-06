/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.5. Графы                                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : MatrixGraph.cpp                                  *
*  Описание : Реализация методов класса MatrixGraph            *
***************************************************************/

#include "MatrixGraph.h"

// Конструктор
MatrixGraph::MatrixGraph(int n) {
  graph = new bool*[vertexNumber = n];
  for (int i=0; i<n; i++) {
    // создание строки
    bool *row = graph[i] = new bool[n];
    // инициализация элементов строки
    for (int j = 0; j < n; j++) {
      row[j] = false;
    }
  }
}

// Деструктор
MatrixGraph::~MatrixGraph() {
  for (int i = 0; i < vertexNumber; i++) {
    delete graph[i];
  }
  delete graph;
}

// Добавление дуги - элемент массива устанавливается в true
void MatrixGraph::addArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;    // Неправильно задана дуга
  graph[from][to] = true;
}

// Проверка существования дуги
bool MatrixGraph::hasArc(int from, int to) const {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return false;    // Неправильно задана дуга
  return graph[from][to];
}

