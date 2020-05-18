/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.2. ����� ���������� �����                         *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : ListGraph.h                                      *
*  �������� : ����������� ������ ListGraph � ����������� ����� *
*             � ���� ������� ������� ���                       *
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
// ����������� ������ ListGraph
//==============================================================

class ListGraph {
  // ������ ������� ���
  List<int> *graph;

  // ���������� ������ �����
  int vertexNumber;

public:

  // ����� ��� ���������� �������� ��������� ������ �����
  class ExtGraphIterator : public Iterator<int> {
    Set setNotPassed;            // ��������� ������������ ������
    int current;                 // ������� �������
    int components;
    Stack<Iterator<int>*> *arcs; // ���� ���������� ��������� ���
    ListGraph *graph;            // ����

  public :

    //==========================================================
    //  �����������
    //    graph - ���� ��� ������
    //==========================================================
    ExtGraphIterator(ListGraph *graph);

    //==========================================================
    //  ����������
    //==========================================================
    ~ExtGraphIterator() { delete arcs; }

    // ������� ���������, �������� �� ��� �� ���������� �������
    bool hasMoreElements() const {
      return !setNotPassed.empty();
    }

    // ������� ������ ��������� �� ��������� �������
    // � ������� ������ ������ ����� "� �������"
    Iterator<int> & operator ++();

    // �������, �������� ����� ��������� ������� �� ���� ������
    const int & operator *() const { return current; }

    // �������, �������� ����� ���������� ��������� ���������
    int getComponentsPassed() const { return components; }
  };

  class BreadthGraphIterator : public Iterator<int> {
    ListGraph *graph;          // ���� ��� ������
    Queue<int> *qNext;         // ������� ������
    Set setNotPassed;          // ��������� ������������ ������

  public :

    //==========================================================
    //  �����������
    //    graph - ���� ��� ������
    //==========================================================
    BreadthGraphIterator(ListGraph *graph);

    //==========================================================
    //  ����������
    //==========================================================
    ~BreadthGraphIterator() { delete qNext; }

    // ������� ���������, �������� �� ��� �� ���������� �������
    bool hasMoreElements() const {
      return !qNext->empty() || !setNotPassed.empty();
    }

    // ������� ������ ��������� �� ��������� �������
    // � ������� ������ ������ ����� "� �������"
    Iterator<int> & operator ++();

    // �������, �������� ����� ��������� ������� �� ���� ������
    const int & operator *() const { return qNext->head(); }
  };

  // ����������� ������� ������ ������ �������
  ListGraph(int n) : vertexNumber(n), graph(new List<int>[n]) {}

  // ���������� ���������� ������ ���
  ~ListGraph() { delete [] graph; }

  // ������� �������� ����� ������ ������ ������
  // ����� ����������� ��������
  int vertexCount() const { return vertexNumber; }

  // �������� ������ ������ � ������
  void addArc(int from, int to);
  bool hasArc(int from, int to) const;

  // �������� �������� ��������� ������ ����� (����� "� �������")
  Iterator<int> * iterator() { return new ExtGraphIterator(this); }

  // �������� �������� ��������� ������ ����� (����� "� ������")
  Iterator<int> * breadthIterator() { return new BreadthGraphIterator(this); }

  vector<int> getShortestPath(int beg, int end) const;
  double getDijkstraPath(int beg, int end, const GraphWeight & weights, vector<int> & path) const;

protected :
  // ���� �� ������ ������� � ��������� ��������� ���
  // ������������ ��� ������ ����������� ���������
  struct Pair {
    int sourceVertex;
    Iterator<int>* iterator;
    Pair(int v = -1, Iterator<int>* i = NULL) : sourceVertex(v), iterator(i) {}
  };
};

#endif
