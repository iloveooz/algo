/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.1. Обходы и поиск в графах                        *
*                                                              *
*  Автор    : А. Кубенский                                     *
*  Файл     : main.cpp                                         *
*  Описание : Примеры обхода графов                            *
***************************************************************/

#include "ListGraph.h"
#include "topsort.h"
#include <iostream>

using namespace std;

int main() {
  ListGraph testGraph(9);
  testGraph.addArc(0, 1);  testGraph.addArc(1, 0);
  testGraph.addArc(0, 4);  testGraph.addArc(4, 0);
  testGraph.addArc(0, 6);  testGraph.addArc(6, 0);
  testGraph.addArc(1, 4);  testGraph.addArc(4, 1);
  testGraph.addArc(1, 7);  testGraph.addArc(7, 1);
  testGraph.addArc(2, 8);  testGraph.addArc(8, 2);
  testGraph.addArc(3, 0);  testGraph.addArc(0, 3);
  testGraph.addArc(4, 6);  testGraph.addArc(6, 4);
  testGraph.addArc(4, 7);  testGraph.addArc(7, 4);
  testGraph.addArc(5, 2);  testGraph.addArc(2, 5);
  testGraph.addArc(6, 3);  testGraph.addArc(3, 6);
  testGraph.addArc(8, 5);  testGraph.addArc(5, 8);

  cout << endl << "Graph traversing with \"depth first\" algorithm" << endl;
  ListGraph::ExtGraphIterator * iter1 = new ListGraph::ExtGraphIterator(&testGraph);
  while (iter1->hasMoreElements()) {
    cout << **iter1 << ';';
    ++*iter1;
  }
  cout << endl << iter1->getComponentsPassed() << " components passed" << endl;
  delete iter1;

  cout << endl << "Graph traversing with \"breadth first\" algorithm" << endl;
  Iterator<int> * iter2 = testGraph.breadthIterator();
  while (iter2->hasMoreElements()) {
    cout << **iter2 << ';';
    ++*iter2;
  }
  cout << endl;
  delete iter2;

  class Logger : public GraphActor {
  public :
    void vertexIn(int vertex) { cout << "In vertex: " << vertex << endl; }
    void vertexOut(int vertex) { cout << "Out vertex: " << vertex << endl; }
    void arcForward(int begin, int end, bool newVertex) {
      cout << "Arc forward (" << (newVertex ? "new" : "old")
           << "): (" << begin << "-" << end << ")" << endl; 
    }
    void arcBackward(int begin, int end) {
      cout << "Arc backward: (" << begin << "-" << end << ")" << endl; 
    }
    void newSelection(int vertex) {
      cout << "New component started from vertex: " << vertex << endl; 
    }
  } logger;

  testGraph.traverseDepth(logger);

  class ComponentLogger : public GraphActor {
    int compNumber;
  public :
    ComponentLogger() : compNumber(0) {}
    void vertexIn(int vertex) { cout << vertex << "; "; }
    void newSelection(int vertex) { cout << endl << "Component #: " << ++compNumber << endl; }
  } compLogger1, compLogger2, compLogger3;

  testGraph.traverseDepth(compLogger1);
  cout << endl << endl;
  testGraph.traverseDepthRec(compLogger2);
  cout << endl << endl;
  testGraph.traverseBreadth(compLogger3);
  cout << endl << endl;

  ListGraph dag(6);
  dag.addArc(0, 1);
  dag.addArc(0, 5);
  dag.addArc(1, 3);
  dag.addArc(2, 0);
  dag.addArc(2, 4);
  dag.addArc(4, 5);
  dag.addArc(5, 3);

  Marker marker(dag);
  if (marker.hasError()) {
    cout << "Graph has a cycle!" << endl;
  } else {
    cout << "Marks of graph vertices:" << endl;
    for (int i = 0; i < dag.vertexCount(); i++) {
      cout << "Vertex # " << i << " has a mark # " << marker.getMark(i) << endl;
    }
  }

  return 0;
}
