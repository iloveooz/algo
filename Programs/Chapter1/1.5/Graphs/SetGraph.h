/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.5. �����                                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : SetGraph.h                                       *
*  �������� : ����������� ������ SetGraph � ����������� �����  *
*             � ���� ������� ��������                          *
***************************************************************/

#ifndef __SET_GRAPH_H
#define __SET_GRAPH_H

#include "Graph.h"
#include "Set.h"    // ����������� ������ Set ������������� �� ���������� �����

// ������ �� ������ ����������� ������ ��� ������� ��������������
class MatrixGraph;
class ListGraph;

class SetGraph : public Graph {
  // ������ ������� �������������� ��������� � �������
  // ������������� S-�����
  friend SetGraph * convert(const MatrixGraph & srcGraph);
  friend ListGraph * convert(const SetGraph & srcGraph);

  // ������ �������� ���
  Set **graph;

  // ����� ������
  int vertexNumber;

public:

  // ����������� ������� ������ �� ������ ��������
  SetGraph(int n) : vertexNumber(n), graph(new Set*[n]) {
    for (int i = 0; i < n; i++) { graph[i] = new Set(0,n); }
  }

  // ���������� ���������� ������ ��������
  ~SetGraph();

  // ������� �������� ����� ������ ������ ������
  // ����� ����������� ��������
  int vertexCount() const { return vertexNumber; }

  // �������� ������ ������ � ������
  void addArc(int from, int to);
  bool hasArc(int from, int to) const;
};

#endif
