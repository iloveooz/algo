/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.1. Обходы и поиск в графах                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : ListGraph.cpp                                    *
*  Описание : Определение реализации методов класса ListGraph  *
***************************************************************/

#include "ListGraph.h"
#include "liststack.h"
#include "listqueue.h"

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
// Методы, реализующие различные внутренние итераторы вершин графа
//**************************************************************

void ListGraph::traverseDepthRec(GraphActor & actor) {
  // множество непройденных вершин:
  Set setNotPassed(0, vertexCount()-1);
  setNotPassed.addScale(0, vertexCount()-1);

  // Цикл по компонентам связности графа
  while (!setNotPassed.empty()) {
    // Выбираем произвольную вершину из еще не пройденных
    Iterator<int> * setIterator = setNotPassed.iterator();
    int first = **setIterator;
    delete setIterator;

    // Отмечаем заход в новую компоненту связности
    actor.newSelection(first);

    // Осуществляем обход компоненты связности
    // с помощью вспомогательной рекурсивной функции
    traverseDepthRec(first, actor, setNotPassed);
  }
}

void ListGraph::traverseDepthRec(int v, GraphActor & actor, Set & setNotPassed) {
  // Отмечаем вход в вершину...
  actor.vertexIn(v);
  // ...и удаляем ее из списка непройденных вершин
  setNotPassed -= v;

  // Организуем цикл по дугам, исходящим из этой вершины
  Iterator<int> * curList = graph[v].iterator();
  while (curList->hasMoreElements()) {
    int e = **curList;          // номер вершины на конце очередной дуги
    bool newVertex = setNotPassed.has(e);  // вершина еще не пройдена?

    // Проходим дугу по направлению ее следования
    actor.arcForward(v, e, newVertex);

    // Если попали в еще не пройденную вершину,
    // то производим рекурсивный вызов функции
    if (newVertex) {
      traverseDepthRec(e, actor, setNotPassed);
    }

    // Проходим дугу в обратном направлении
    actor.arcBackward(v, e);

    // Переходим к следующей дуге
    ++*curList;
  }
  delete curList;

  // Отмечаем выход из вершины
  actor.vertexOut(v);
}

void ListGraph::traverseDepth(GraphActor & actor) {
  // множество непройденных вершин:
  Set setNotPassed(0, vertexCount()-1);
  setNotPassed.addScale(0, vertexCount()-1);

  // стек дуг:
  ListStack<Pair> arcs;

  // Цикл по компонентам связности графа
  while (!setNotPassed.empty()) {
    // Выбираем произвольную вершину из еще не пройденных
    Iterator<int> * setIterator = setNotPassed.iterator();
    int current = **setIterator;
    // Отмечаем заход в новую компоненту связности
    actor.newSelection(current);
    delete setIterator;
    // Список неисследованных дуг, исходящих из очередной вершины
    Iterator<int> * curList = graph[current].iterator();

    // Цикл по вершинам одной компоненты связности
    while (current != -1) {
      // Проходим текущую вершину
      setNotPassed -= current;
      actor.vertexIn(current);

      // Цикл прохода по дугам
      for (;;) {
        // Есть дуга, ведущая из текущей вершины?
        if (curList->hasMoreElements()) {
          int arcEnd = **curList;
          bool newVertex = setNotPassed.has(arcEnd);
          ++*curList;
          // Проходим вперед по выбранной дуге
          actor.arcForward(current, arcEnd, newVertex);
          if (newVertex) {
            // Дуга ведет в новую ранее не рассмотренную вершину.
            // Запоминаем ситуацию, делаем шаг вперед по выбранной дуге
            // и переходим к рассмотрению следующей вершины
            arcs.push(Pair(current, curList));
            current = arcEnd;
            curList = graph[current].iterator();
            break;
          } else {
            // Дуга ведет в уже пройденную вершину.
            // Выполняем обратный проход по этой дуге
            actor.arcBackward(current, arcEnd);
          }
        } else {
          // Покидаем окончательно текущую вершину и
          // возвращаемся к предыдущим вершинам
          actor.vertexOut(current);
          delete curList;
          if (arcs.empty()) {
            // Компонента связности пройдена полностью
            current = -1;
            break;
          } else {
            // Делаем обратный проход по дуге, извлеченной из стека дуг
            Pair previous = *arcs;
            arcs.pop();
            actor.arcBackward(previous.sourceVertex, current);
            current = previous.sourceVertex;
            curList = previous.iterator;
          }
        }
      }
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
// Метод для внутренней итерации вершин графа (обход "в ширину")
//**************************************************************

void ListGraph::traverseBreadth(GraphActor & actor) {
  // Очередь вершин
  Queue<int> *qNext = new ListQueue<int>;
  // Множество еще не пройденных вершин
  Set setNotPassed;
  setNotPassed.addScale(0, vertexCount()-1);

  while (!(qNext->empty() && setNotPassed.empty())) {
    if (qNext->empty()) {
      // Выбор очередной исходной вершины
      Iterator<int> * setIterator = setNotPassed.iterator();
      int selected = **setIterator;
      delete setIterator;

      // Вершина ставится в очередь qNext
      actor.newSelection(selected);
      qNext->enqueue(selected);
      setNotPassed -= selected;
    }

    // Выбор вершины из очереди
    int vertex = qNext->head();
    qNext->dequeue();

    actor.vertexIn(vertex);
    // Просмотр всех дуг, ведущих из этой вершины
    Iterator<int> *iArcs = graph[vertex].iterator();
    while (iArcs->hasMoreElements()) {
      int next = **iArcs;
      bool newVertex = setNotPassed.has(next);
      actor.arcForward(vertex, next, newVertex);
      if (newVertex) {
        qNext->enqueue(next);
        setNotPassed -= next;
      }
      ++*iArcs;
    }
    delete iArcs;
  }
}
