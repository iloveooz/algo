/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.3. Определение остовных деревьев                  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : ListGraph.h                                      *
*  Описание : Определение класса ListGraph с реализацией графа *
*             в виде массива списков дуг                       *
***************************************************************/

#ifndef __LIST_GRAPH_H
#define __LIST_GRAPH_H

#include "list.h"
#include "graphweight.h"
#include <iostream>

//==============================================================
// Определение класса ListGraph
//==============================================================

class ListGraph {
  // Массив списков дуг
  List<int> *graph;

  // Количество вершин графа
  int vertexNumber;

public:

  // Конструктор создает массив пустых списков
  ListGraph(int n) : vertexNumber(n), graph(new List<int>[n]) {}

  // Деструктор уничтожает списки дуг
  ~ListGraph() { delete [] graph; }

  // Функция подсчета числа вершин просто выдает
  // ранее сохраненное значение
  int vertexCount() const { return vertexNumber; }

  // Основные методы работы с графом
  void addArc(int from, int to);
  bool hasArc(int from, int to) const;

  // Алгоритм Крускала нахождения минимального остовного дерева
  double minSkeleton(std::ostream & out, const GraphWeight & gw);
  // Алгоритм Прима нахождения минимального остовного дерева
  double minSkeletonPrim(std::ostream & out, const GraphWeight & gw);
};

#endif
