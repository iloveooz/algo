/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.2. ����� ���������� �����                         *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : ListGraph.cpp                                    *
*  �������� : ����������� ���������� ������� ������ ListGraph  *
***************************************************************/

#include "ListGraph.h"
#include "liststack.h"
#include "listqueue.h"
#include <iostream>

using namespace std;

//**************************************************************
// ������ ������ ListGraph
//**************************************************************

// ���������� ����
void ListGraph::addArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;          // ����������� ������ ����
  graph[from].addLast(to);
}

// ����� ����
bool ListGraph::hasArc(int from, int to) const {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return false;    // ����������� ������ ����
  Iterator<int> * ends = graph[from].iterator();
  bool found = false;
  while (ends->hasMoreElements() && !(found = (to == **ends))) ++*ends;
  delete ends;
  return found;
}

//**************************************************************
// ������ �������� ��������� ������ ����� (����� "� �������")
//**************************************************************

// ����������� �������� ��������� ������ �����
ListGraph::ExtGraphIterator::ExtGraphIterator(ListGraph *graph) :
    // ��������� ������������ ������:
    setNotPassed(0, graph->vertexCount()-1),
    // ������� ������� - ����������� ����� ������� �������:
    current(0),
    // ����� ���������� ��������� ���������:
    components(0),
    // ���� ��������������� ���:
    arcs(new ListStack<Iterator<int>*>),
    // ����, ���������� ������: 
    graph(graph) 
{
  // � ��������� ������������ ������ ���������� ��� ������� �����
  setNotPassed.addScale(0, graph->vertexCount()-1);
}

// �������, ��������������� � �������� ������� ��������� �������
// �� ���� ������ ����� "� �������"
Iterator<int> & ListGraph::ExtGraphIterator::operator ++() {
  // 1. �������� ������������ ������
  if (!hasMoreElements()) return *this;

  // 2. �������� ������� �������
  setNotPassed -= current;

  // 3. ������� ��������� �������
  // ������� ������������� ����, ��������� �� ������� �������
  Iterator<int> *nextPoints = (graph->graph)[current].iterator();
  for (;;) {
    if (!nextPoints->hasMoreElements()) {
      // ��������� ���� ���
      delete nextPoints;
      if (arcs->empty()) {
        // ���� ��� ����� ����: ���������� ��������� ��������,
        // �������� ��������� �� ��������� ������������ ������
        components++;
        Iterator<int> * setIterator = setNotPassed.iterator();
        current = (setIterator->hasMoreElements() ? **setIterator : -1);
        delete setIterator;
        return *this;
      } else {
        // �������� ��������� ���� �� �����
        nextPoints = **arcs;
        arcs->pop();
      }
    }
    // ����, ������� � ��������� �������, �������
    int vertex = **nextPoints;     // ��� ����� ��������� �������
    ++*nextPoints;
    if (setNotPassed.has(vertex)) {
      // ��� ������������ �������; ��� ����������� �������
      current = vertex;
      if (nextPoints->hasMoreElements()) {
        // ���� ���� ��� ����, ������� �� ���� �������,
        // �� �������� ��������� ������ ������������ � ����
        arcs->push(nextPoints);
      } else {
        delete nextPoints;
      }
      return *this;
    }
  }
}

//**************************************************************
// ������ �������� ��������� ������ ����� (����� "� ������")
//**************************************************************

// ����������� �������� ��������� ������ �����
ListGraph::BreadthGraphIterator::BreadthGraphIterator(ListGraph *graph) :
    // ��������� ������������ ������:
    setNotPassed(0, graph->vertexCount()-1),
    // ���� ��������������� ���:
    qNext(new ListQueue<int>),
    // ����, ���������� ������: 
    graph(graph) 
{
  // � ��������� ������������ ������ ���������� ��� ������� �����
  setNotPassed.addScale(0, graph->vertexCount()-1);
  // �������� ��������� �������
  operator ++();
}

// ������� ������ ��������� �� ��������� �������
// � ������� ������ ������ ����� "� �������"
Iterator<int> & ListGraph::BreadthGraphIterator::operator ++() {
  // ������� ��������� �������; ���� ��� �� �����,
  // �� ���� ������� �� ��� ��������� ������� �
  // ��������� � ������� �� ������������ ��������
  if (!qNext->empty()) {
    // �������� ������� �� �������
    int vertex = qNext->head();
    qNext->dequeue();

    // ������������� ����, ������� �� ���� �������
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

  // ������ ���������, ���� �� ��� ������������ �������
  if (!hasMoreElements()) {
    return *this;
  }

  // �������, ���� ������� �� �������� ������ ������,
  // �� ��������� ������� ������� �� ��������� ������������.
  if (qNext->empty()) {
    // �������� ������������ ������� �� ��� �� ����������
    Iterator<int> * setIterator = setNotPassed.iterator();
    int selected = **setIterator;
    delete setIterator;

    qNext->enqueue(selected);
    setNotPassed -= selected;
  }
  return *this;
}

//**************************************************************
// ������� ������ ����������� ���� ����� ����� ���������
// � ������������� �����
//**************************************************************

vector<int> ListGraph::getShortestPath(int beg, int end) const {
  vector<int> shortestPath;
 
  // ����������� ������ ���������� ��������� � �������� ������
  // ��������������� ��������
  if (beg == end) {
    shortestPath.push_back(end);
    return shortestPath;
  }

  // �������� ��������� ������� � �������� ��������
  int selected = beg;
  Queue<int> *qNext = new ListQueue<int>;
  Set setNotPassed(0, vertexCount()-1);
  setNotPassed.addScale(0, vertexCount()-1);
  int *backs = new int[vertexCount()];

  // ������������� ������� �������� �����
  for (int i=0;  i < vertexCount();  i++) {
    backs[i] = -1;
  }

  // �������� ������ ������� � �������
  setNotPassed -= selected;
  qNext->enqueue(selected);

  // �������� ���� ������ �� ������
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
      // ����� ���������� �������� �� ���������� �������� �������
      if (next == end) finish = true;

      ++*iNext;
    }
  }

  if (finish) {
    // ������ ���� �� ��������� � �������� �������
    // ������������ ��������������� �������
    vector<int>::iterator it = shortestPath.begin();
    for (int i = end;  backs[i] != -1;  i = backs[i]) {
      it = shortestPath.insert(it, i);
    }
    shortestPath.insert(it, beg);
  }

  return shortestPath;
}

//**************************************************************
// ������� ������ ����������� ���� ����� ����� ��������� �
// ����������� ����� � ���������������� ������� ��� (�������� ��������)
//**************************************************************

double ListGraph::getDijkstraPath(
     int beg,
     int end,
     const GraphWeight & weights,
     vector<int> & path) const {

  path.clear();

  // ��������� ��������������� ������:
  Set notPassed(0, vertexCount()-1);
  notPassed.addScale(0, vertexCount()-1);

  // ������ �������� �����
  int *backs = new int[vertexCount()];

  // ������ ����������� ����������. � ������ ������ ��� ����������
  // ���������� �������, ����� ���������� �� �������� �������
  double *dist = new double[vertexCount()];
  for (int i = 0; i < vertexCount(); i++) dist[i] = INFINITY;
  dist[beg] = 0;

  // ���� ������ � ��������� ����������� �������
  while(!notPassed.empty()) {
    // ����� ����������� �������: ������������� ������ dist
    // � ������� ������� � ����������� ����������� �� beg
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

    // ���� ����������� ������� �� �������, �� ���� ���
    if (border == -1) return INFINITY;
    // ���� ����������� ������� ������� � ��������,
    // �� ��������� � ������������ ����������
    if (border == end) break;

    // ��������� ������, ������� � �����������
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

  // ������������ ��������������� �������
  int current = end;
  while(current != beg) {
    path.insert(path.begin(), current);
    current = backs[current];
  }
  path.insert(path.begin(), beg);

  return dist[end];
}
