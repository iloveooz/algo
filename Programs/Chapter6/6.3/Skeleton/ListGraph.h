/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.3. ����������� �������� ��������                  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : ListGraph.h                                      *
*  �������� : ����������� ������ ListGraph � ����������� ����� *
*             � ���� ������� ������� ���                       *
***************************************************************/

#ifndef __LIST_GRAPH_H
#define __LIST_GRAPH_H

#include "list.h"
#include "graphweight.h"
#include <iostream>

//==============================================================
// ����������� ������ ListGraph
//==============================================================

class ListGraph {
  // ������ ������� ���
  List<int> *graph;

  // ���������� ������ �����
  int vertexNumber;

public:

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

  // �������� �������� ���������� ������������ ��������� ������
  double minSkeleton(std::ostream & out, const GraphWeight & gw);
  // �������� ����� ���������� ������������ ��������� ������
  double minSkeletonPrim(std::ostream & out, const GraphWeight & gw);
};

#endif
