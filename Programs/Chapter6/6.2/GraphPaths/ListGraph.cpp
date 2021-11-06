/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.2. Поиск кратчайших путей                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : ListGraph.cpp                                    *
*  Описание : Определение реализации методов класса ListGraph  *
***************************************************************/

#include "ListGraph.h"
#include "liststack.h"
#include "listqueue.h"
#include <iostream>

using namespace std;

//**************************************************************
// Методы класса ListGraph
//**************************************************************

// Добавление дуги
void ListGraph::addArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;          // Неправильно задана дуга
  graph[from].addLast(to);
}

// Поиск дуги
bool ListGraph::hasArc(int from, int to) const {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return false;    // Неправильно задана дуга
  Iterator<int> * ends = graph[from].iterator();
  bool found = false;
  while (ends->hasMoreElements() && !(found = (to == **ends))) ++*ends;
  delete ends;
  return found;
}

//**************************************************************
// Методы внешнего итератора вершин графа (обход "в глубину")
//**************************************************************

// Конструктор внешнего итератора вершин графа
ListGraph::ExtGraphIterator::ExtGraphIterator(ListGraph *graph) :
    // множество непройденных вершин:
    setNotPassed(0, graph->vertexCount()-1),
    // текущая вершина - произвольно берем нулевую вершину:
    current(0),
    // число пройденных компонент связности:
    components(0),
    // стек непросмотренных дуг:
    arcs(new ListStack<Iterator<int>*>),
    // граф, подлежащий обходу: 
    graph(graph) 
{
  // В множество непройденных вершин помещаются все вершины графа
  setNotPassed.addScale(0, graph->vertexCount()-1);
}

// Функция, устанавливающая в качестве текущей следующую вершину
// на пути обхода графа "в глубину"
Iterator<int> & ListGraph::ExtGraphIterator::operator ++() {
  // 1. Проверка корректности вызова
  if (!hasMoreElements()) return *this;

  // 2. Проходим текущую вершину
  setNotPassed -= current;

  // 3. Находим очередную вершину
  // Сначала рассматриваем дуги, выходящие из текущей вершины
  Iterator<int> *nextPoints = (graph->graph)[current].iterator();
  for (;;) {
    if (!nextPoints->hasMoreElements()) {
      // Очередной дуги нет
      delete nextPoints;
      if (arcs->empty()) {
        // стек дуг также пуст: компонента связности пройдена,
        // выбираем следующую из множества непройденных вершин
        components++;
        Iterator<int> * setIterator = setNotPassed.iterator();
        current = (setIterator->hasMoreElements() ? **setIterator : -1);
        delete setIterator;
        return *this;
      } else {
        // выбираем очередную дугу из стека
        nextPoints = **arcs;
        arcs->pop();
      }
    }
    // Дуга, ведущая в некоторую вершину, найдена
    int vertex = **nextPoints;     // это будет следующая вершина
    ++*nextPoints;
    if (setNotPassed.has(vertex)) {
      // это непройденная вершина; она объявляется текущей
      current = vertex;
      if (nextPoints->hasMoreElements()) {
        // если есть еще дуги, ведущие из этой вершины,
        // то итератор множества вершин записывается в стек
        arcs->push(nextPoints);
      } else {
        delete nextPoints;
      }
      return *this;
    }
  }
}

//**************************************************************
// Методы внешнего итератора вершин графа (обход "в ширину")
//**************************************************************

// Конструктор внешнего итератора вершин графа
ListGraph::BreadthGraphIterator::BreadthGraphIterator(ListGraph *graph) :
    // множество непройденных вершин:
    setNotPassed(0, graph->vertexCount()-1),
    // стек непросмотренных дуг:
    qNext(new ListQueue<int>),
    // граф, подлежащий обходу: 
    graph(graph) 
{
  // В множество непройденных вершин помещаются все вершины графа
  setNotPassed.addScale(0, graph->vertexCount()-1);
  // Выбираем очередную вершину
  operator ++();
}

// Функция сдвига итератора на следующую вершину
// в порядке обхода вершин графа "в глубину"
Iterator<int> & ListGraph::BreadthGraphIterator::operator ++() {
  // Сначала проверяем очередь; если она не пуста,
  // то надо удалить из нее очередную вершину и
  // поставить в очередь ее непройденных потомков
  if (!qNext->empty()) {
    // Выбираем вершину из очереди
    int vertex = qNext->head();
    qNext->dequeue();

    // Просматриваем дуги, ведущие из этой вершины
    Iterator<int> *arcs = (graph->graph)[vertex].iterator();
    while (arcs->hasMoreElements()) {
      int next = **arcs;
      if (setNotPassed.has(next)) {
        qNext->enqueue(next);
        setNotPassed -= next;
      }
      ++*arcs;
    }
  }

  // Теперь проверяем, есть ли еще непройденные вершины
  if (!hasMoreElements()) {
    return *this;
  }

  // Наконец, если очередь не содержит больше вершин,
  // то очередная вершина берется из множества непройденных.
  if (qNext->empty()) {
    // Выбираем произвольную вершину из еще не пройденных
    Iterator<int> * setIterator = setNotPassed.iterator();
    int selected = **setIterator;
    delete setIterator;

    qNext->enqueue(selected);
    setNotPassed -= selected;
  }
  return *this;
}

//**************************************************************
// Функция поиска кратчайшего пути между двумя вершинами
// в ненагруженном графе
//**************************************************************

vector<int> ListGraph::getShortestPath(int beg, int end) const {
  vector<int> shortestPath;
 
  // Тривиальный случай совпадения начальной и конечной вершин
  // рассматривается отдельно
  if (beg == end) {
    shortestPath.push_back(end);
    return shortestPath;
  }

  // Выбираем начальную вершину в качестве исходной
  int selected = beg;
  Queue<int> *qNext = new ListQueue<int>;
  Set setNotPassed(0, vertexCount()-1);
  setNotPassed.addScale(0, vertexCount()-1);
  int *backs = new int[vertexCount()];

  // Инициализация массива обратных меток
  for (int i=0;  i < vertexCount();  i++) {
    backs[i] = -1;
  }

  // Помещаем первую вершину в очередь
  setNotPassed -= selected;
  qNext->enqueue(selected);

  // Основной цикл обхода «в ширину»
  bool finish = false;
  while (!finish && !qNext->empty()) {
    int vertex = qNext->head();
    qNext->dequeue();

    Iterator<int> *iNext = graph[vertex].iterator();
    while (!finish && iNext->hasMoreElements()) {
      int next = **iNext;
      bool newVertex = setNotPassed.has(next);
      if (newVertex) {
        backs[next] = vertex;
        setNotPassed -= next;
        qNext->enqueue(next);
      }
      // Здесь происходит проверка на достижение конечной вершины
      if (next == end) finish = true;

      ++*iNext;
    }
  }

  if (finish) {
    // Найден путь из начальной в конечную вершину
    // Формирование результирующего вектора
    vector<int>::iterator it = shortestPath.begin();
    for (int i = end;  backs[i] != -1;  i = backs[i]) {
      it = shortestPath.insert(it, i);
    }
    shortestPath.insert(it, beg);
  }

  return shortestPath;
}

//**************************************************************
// Функция поиска кратчайшего пути между двумя вершинами в
// нагруженном графе с неотрицательными длинами дуг (алгоритм Дейкстры)
//**************************************************************

double ListGraph::getDijkstraPath(
     int beg,
     int end,
     const GraphWeight & weights,
     vector<int> & path) const {

  path.clear();

  // Множество непросмотренных вершин:
  Set notPassed(0, vertexCount()-1);
  notPassed.addScale(0, vertexCount()-1);

  // Массив обратных меток
  int *backs = new int[vertexCount()];

  // Массив минимальных расстояний. В начале работы все расстояния
  // бесконечно большие, кроме расстояния до исходной вершины
  double *dist = new double[vertexCount()];
  for (int i = 0; i < vertexCount(); i++) dist[i] = INFINITY;
  dist[beg] = 0;

  // Цикл поиска и обработки пограничной вершины
  while(!notPassed.empty()) {
    // Поиск пограничной вершины: просматриваем массив dist
    // в поисках вершины с минимальным расстоянием от beg
    int border = -1;
    double minDist = INFINITY;
    Iterator<int> *check = notPassed.iterator();
    while(check->hasMoreElements()) {
      int next = **check;
      if (dist[next] < minDist) {
        minDist = dist[border = next];
      }
      ++*check;
    }
    delete check;

    // Если пограничная вершина не найдена, то пути нет
    if (border == -1) return INFINITY;
    // Если пограничная вершина совпала с конечной,
    // то переходим к формированию результата
    if (border == end) break;

    // Обработка вершин, смежных с пограничной
    notPassed -= border;
    Iterator<int> *nextToBorder = graph[border].iterator();
    while (nextToBorder->hasMoreElements()) {
      int v = **nextToBorder;
      if (notPassed.has(v) && dist[v] >
          dist[border] + weights.arcLength(border, v)) {
        backs[v] = border;
        dist[v] = dist[border] + weights.arcLength(border, v);
      }
      ++*nextToBorder;
    }
    delete nextToBorder;
  }

  // Формирование результирующего вектора
  int current = end;
  while(current != beg) {
    path.insert(path.begin(), current);
    current = backs[current];
  }
  path.insert(path.begin(), beg);

  return dist[end];
}
