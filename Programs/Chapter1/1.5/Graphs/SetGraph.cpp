/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.5. Графы                                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : SetGraph.cpp                                     *
*  Описание : Определение реализации методов класса SetGraph   *
***************************************************************/

#include "SetGraph.h"

// Деструктор графа уничтожает массив множеств
SetGraph::~SetGraph() {
  for (int i = 0; i < vertexNumber; i++) {
    delete graph[i];
  }
  delete [] graph;
}

// Добавление новой дуги состоит просто в добавлении
// нового элемента к множеству
void SetGraph::addArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;    // Неправильно задана дуга
  *graph[from] |= to;
}

// Проверка существования дуги сводится к проверке
// наличия элемента в множестве
bool SetGraph::hasArc(int from, int to) const {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return false;    // Неправильно задана дуга
  return graph[from]->has(to);
}
