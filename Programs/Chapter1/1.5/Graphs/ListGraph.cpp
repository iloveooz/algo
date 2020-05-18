/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.5. �����                                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : ListGraph.cpp                                    *
*  �������� : ����������� ���������� ������� ������ ListGraph  *
***************************************************************/

#include "ListGraph.h"

//**************************************************************
// ������ ������ ListGraph
//**************************************************************

// ���������� ����
void ListGraph::addArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;          // ����������� ������ ����
  graph[from].add(to);
}

// ����� ����
bool ListGraph::hasArc(int from, int to) const {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return false;    // ����������� ������ ����
  return graph[from].has(to);
}
