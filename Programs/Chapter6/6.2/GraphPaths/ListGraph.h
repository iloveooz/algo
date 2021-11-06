/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.2. Поиск кратчайших путей                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : ListGraph.h                                      *
*  Описание : Определение класса ListGraph с реализацией графа *
*             в виде массива списков дуг                       *
***************************************************************/

#ifndef __LIST_GRAPH_H
#define __LIST_GRAPH_H

#include "iterator.h"
#include "list.h"
#include "set.h"
#include "stack.h"
#include "queue.h"
#include "graphweight.h"
#include "infinity.h"
#include <vector>

//==============================================================
// Определение класса ListGraph
//==============================================================

class ListGraph {
  // Массив списков дуг
  List<int> *graph;

  // Количество вершин графа
  int vertexNumber;

public:

  // Класс для реализации внешнего итератора вершин графа
  class ExtGraphIterator : public Iterator<int> {
    Set setNotPassed;            // множество непройденных вершин
    int current;                 // текущая вершина
    int components;
    Stack<Iterator<int>*> *arcs; // стек итераторов исходящих дуг
    ListGraph *graph;            // граф

  public :

    //==========================================================
    //  Конструктор
    //    graph - граф для обхода
    //==========================================================
    ExtGraphIterator(ListGraph *graph);

    //==========================================================
    //  Деструктор
    //==========================================================
    ~ExtGraphIterator() { delete arcs; }

    // Функция проверяет, остались ли еще не пройденные вершины
    bool hasMoreElements() const {
      return !setNotPassed.empty();
    }

    // Функция сдвига итератора на следующую вершину
    // в порядке обхода вершин графа "в глубину"
    Iterator<int> & operator ++();

    // Функция, выдающая номер очередной вершины на пути обхода
    const int & operator *() const { return current; }

    // Функция, выдающая число пройденных компонент связности
    int getComponentsPassed() const { return components; }
  };

  class BreadthGraphIterator : public Iterator<int> {
    ListGraph *graph;          // граф для обхода
    Queue<int> *qNext;         // очередь вершин
    Set setNotPassed;          // множество непройденных вершин

  public :

    //==========================================================
    //  Конструктор
    //    graph - граф для обхода
    //==========================================================
    BreadthGraphIterator(ListGraph *graph);

    //==========================================================
    //  Деструктор
    //==========================================================
    ~BreadthGraphIterator() { delete qNext; }

    // Функция проверяет, остались ли еще не пройденные вершины
    bool hasMoreElements() const {
      return !qNext->empty() || !setNotPassed.empty();
    }

    // Функция сдвига итератора на следующую вершину
    // в порядке обхода вершин графа "в глубину"
    Iterator<int> & operator ++();

    // Функция, выдающая номер очередной вершины на пути обхода
    const int & operator *() const { return qNext->head(); }
  };

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

  // Создание внешнего итератора вершин графа (обход "в глубину")
  Iterator<int> * iterator() { return new ExtGraphIterator(this); }

  // Создание внешнего итератора вершин графа (обход "в ширину")
  Iterator<int> * breadthIterator() { return new BreadthGraphIterator(this); }

  vector<int> getShortestPath(int beg, int end) const;
  double getDijkstraPath(int beg, int end, const GraphWeight & weights, vector<int> & path) const;

protected :
  // Пара из номера вершины и итератора исходящих дуг
  // определяется для работы внутреннего итератора
  struct Pair {
    int sourceVertex;
    Iterator<int>* iterator;
    Pair(int v = -1, Iterator<int>* i = NULL) : sourceVertex(v), iterator(i) {}
  };
};

#endif
