/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.5. Графы                                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : SetGraph.h                                       *
*  Описание : Определение класса SetGraph с реализацией графа  *
*             в виде массива множеств                          *
***************************************************************/

#ifndef __SET_GRAPH_H
#define __SET_GRAPH_H

#include "Graph.h"
#include "Set.h"    // Определение класса Set импортировано из предыдущей главы

// Ссылки на другие определения графов для функций преобразования
class MatrixGraph;
class ListGraph;

class SetGraph : public Graph {
  // Данные функции преобразования нуждаются в деталях
  // представления S-графа
  friend SetGraph * convert(const MatrixGraph & srcGraph);
  friend ListGraph * convert(const SetGraph & srcGraph);

  // Массив множеств дуг
  Set **graph;

  // Число вершин
  int vertexNumber;

public:

  // Конструктор создает массив из пустых множеств
  SetGraph(int n) : vertexNumber(n), graph(new Set*[n]) {
    for (int i = 0; i < n; i++) { graph[i] = new Set(0,n); }
  }

  // Деструктор уничтожает массив множеств
  ~SetGraph();

  // Функция подсчета числа вершин просто выдает
  // ранее сохраненное значение
  int vertexCount() const { return vertexNumber; }

  // Основные методы работы с графом
  void addArc(int from, int to);
  bool hasArc(int from, int to) const;
};

#endif
