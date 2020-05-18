/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.5. �����                                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : ListGraph.h                                      *
*  �������� : ����������� ������ ListGraph � ����������� ����� *
*             � ���� ������� ������� ���                       *
***************************************************************/

#ifndef __LIST_GRAPH_H
#define __LIST_GRAPH_H

#include "Graph.h"
#include <stdlib.h>

class SetGraph;
class ArcGraph;
class ListGraph;

//**************************************************************
// ����������� ������� ��� ������ List ��������� ���������������
// � ���� ListGraph.h
//**************************************************************

template <class T>
class List {
  // ��������� ������ ������ ���� �������� ��� ������� ��������������
  friend ArcGraph * convert(const ListGraph & srcGraph);

  // ����������� �������� ������
  struct ListItem {
    T item;             // ��� �������
    ListItem *next;     // ��������� �� ��������� �������

    // ����������� �������� ������
    ListItem(const T &item, ListItem *next = NULL) {
      ListItem::item = item;
      ListItem::next = next;
    }
  };

  // ������������� ������: ��������� �� ������ � ��������� ��������
  ListItem *first, *last;

  // ������� ����� ���������
  int count;

public:

  // ����������� ������ ������� ����� ������ ������
  List() { first = last = NULL; count = 0; }

  // ���������� ������ ���������� ��� ��������
  ~List();

  // ����� ��� ���������� �������� � ������
  void add(const T &);

  // ����� ��� ��������, ������� �� ������� � ������
  bool has(const T &) const;
};

//**************************************************************
// ������ �������� ������ List
//**************************************************************

// ����������
template <class T>
List<T>::~List() {
  ListItem * current = first,
           * pred = NULL;
  while (current) {
    pred = current;
    current = current->next;
    delete pred;
  }
}

// ���������� �������� � ������
template <class T>
void List<T>::add(const T & item) {
  ListItem *newItem = new ListItem(item);
  // ����� ������� ����������� � ����� ������
  if (last) last->next = newItem; else first = newItem;
  last = newItem;
  count++;
}

// �������� ������������� �������� � ������
template <class T>
bool List<T>::has(const T & item) const {
  for (ListItem *current = first; current; current = current->next) {
    if (current->item == item) return true;
  }
  // ������� �� ������!
  return false;
}

//**************************************************************
// ����������� ������ ListGraph
//**************************************************************

class ListGraph : public Graph {
  // ������ ������� �������������� ��������� � �������
  // ������������� L-�����
  friend ListGraph * convert(const SetGraph & srcGraph);
  friend ArcGraph * convert(const ListGraph & srcGraph);

  // ������ ������� ���
  List<int> *graph;

  // ���������� ������ �����
  int vertexNumber;

public:

  // ����������� ������� ������ ������ �������
  ListGraph(int n) : vertexNumber(n), graph(new List<int>[n]) {}

  // ���������� ���������� ������ ���
  ~ListGraph() { delete graph; }

  // ������� �������� ����� ������ ������ ������
  // ����� ����������� ��������
  int vertexCount() const { return vertexNumber; }

  // �������� ������ ������ � ������
  void addArc(int from, int to);
  bool hasArc(int from, int to) const;
};

#endif
