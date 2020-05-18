/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.3. Определение остовных деревьев                  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : ListGraph.cpp                                    *
*  Описание : Определение реализации методов класса ListGraph  *
***************************************************************/

#include "ListGraph.h"
#include "arc.h"
#include "arrayheap.h"
#include "infinity.h"
#include "set.h"

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

//--------------------------------------------------------------
// Алгоритм Крускала нахождения минимального остовного дерева
//--------------------------------------------------------------

double ListGraph::minSkeleton(
    std::ostream & out,     // Выходной поток для вывода результирующей информации
    const GraphWeight & gw  // Нагрузка на ребра графа
    ) {
  // Суммарный вес найденного минимального остовного дерева:
  double weight = 0;
  // Пирамида, содержащая информацию о ребрах графа:
  ArrayHeap<Arc> arcs(vertexNumber * vertexNumber / 2);

  //---------------------------------------------------------------
  // Структура узла в лесе, представляющем частично построенное
  // минимальное остовное дерево
  //---------------------------------------------------------------
  struct SkeletonNode {
    int node;   // номер узла исходного графа
    int next;   // ссылка на родительский узел
    // Конструкторы:
    SkeletonNode(int n = 0) : node(n), next(-1) {}
    SkeletonNode(const SkeletonNode & node) : node(node.node), next(node.next) {}
  };

  // Начальное заполнение пирамиды ребер:
  // просматриваются все ребра графа,
  // и информация о них заносится в пирамиду.
  for (int i = 0; i < vertexNumber; i++) {
    Iterator<int> *neighbors = graph[i].iterator();
    while (neighbors->hasMoreElements()) {
      int j = **neighbors;
      // Граф неориентированный, поэтому для исключения дублирования информации
      // рассматриваются только дуги, ведущие из вершины с меньшим номером
      // в вершину с большим номером. Петли (если они есть) сразу же исключаются.
      if (i < j) {
        // Добавление ребра в пирамиду:
        arcs += Arc(i, j, gw.arcLength(i, j));
      }
      ++*neighbors;
    }
    delete neighbors;
  }

  // Начальное заполнение леса: каждая вершина графа представляет
  // собой отдельное дерево, состоящее из единственной вершины.
  SkeletonNode skeleton[vertexNumber];
  for (int i = 0; i < vertexNumber; i++) {
    skeleton[i] = SkeletonNode(i);
  }

  // Основной цикл по ребрам, включенным в пирамиду
  while (!arcs.empty()) {
    // Очередное ребро выбирается с вершины пирамиды и исключается из нее:
    Arc nextArc = *arcs;
    arcs.remove();

    // u и v - концы выбранного ребра
    int u = nextArc.from, v = nextArc.to;

    // Следующие два цикла находят корни деревьев, содержащих эти вершины:
    while(skeleton[u].next != -1) u = skeleton[u].next;
    while(skeleton[v].next != -1) v = skeleton[v].next;

    if (u != v) {
      // Ребро включается в остовное дерево,...
      out << nextArc << "; ";
      weight += nextArc.weight;
      // ... а два дерева соединяются в одно.
      skeleton[u].next = v;
    }
  }

  return weight;
}

//--------------------------------------------------------------
// Алгоритм Прима нахождения минимального остовного дерева
//--------------------------------------------------------------

double ListGraph::minSkeletonPrim(std::ostream & out, const GraphWeight & gw) {
  // Множество непройденных вершин (сначала - все вершины)
  Set notPassed(0, vertexNumber-1);
  notPassed.addScale(0, vertexNumber-1);

  // Массив расстояний от вершин до уже построенной части
  double *dist = new double[vertexNumber];

  // Массив направлений от новых вершин к уже построенной части
  double *ends = new double[vertexNumber];

  // Инициализация массивов расстояний и направлений
  for (int i = 0; i < vertexNumber; i++) {
    dist[i] = INFINITY;
    ends[i] = -1;
  }

  // Суммарный вес построенной части дерева
  double sumWeight = 0;

  // Основной цикл поиска новых вершин
  while (!notPassed.empty()) {
    // Поиск ближайшей вершины
    double minDist = INFINITY;
    Iterator<int> *iVertices = notPassed.iterator();
    int minVertex = **iVertices;
    while (iVertices->hasMoreElements()) {
      int nextVertex = **iVertices;
      if (dist[nextVertex] < minDist) {
        minDist = dist[nextVertex];
        minVertex = nextVertex;
      }
      ++*iVertices;
    }
    delete iVertices;
      
    if (dist[minVertex] < INFINITY) {
      // Присоединяем очередное ребро
      out << "(" << ends[minVertex] << "," << minVertex << "); ";
      sumWeight += minDist;
    }
    notPassed -= minVertex;

    // Новая вершина присоединена;
    // корректируем информацию о расстояниях
    Iterator<int> *neighbors = graph[minVertex].iterator();
    while (neighbors->hasMoreElements()) {
      int next = **neighbors;
      if (notPassed.has(next) && gw.arcLength(minVertex, next) < dist[next]) {
        dist[next] = gw.arcLength(minVertex, next);
        ends[next] = minVertex;
      }
      ++*neighbors;
    }
    delete neighbors;
  }
  return sumWeight;
}
