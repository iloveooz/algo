/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.5. �����                                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : SetGraph.cpp                                     *
*  �������� : ����������� ���������� ������� ������ SetGraph   *
***************************************************************/

#include "SetGraph.h"

// ���������� ����� ���������� ������ ��������
SetGraph::~SetGraph() {
  for (int i = 0; i < vertexNumber; i++) {
    delete graph[i];
  }
  delete [] graph;
}

// ���������� ����� ���� ������� ������ � ����������
// ������ �������� � ���������
void SetGraph::addArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;    // ����������� ������ ����
  *graph[from] |= to;
}

// �������� ������������� ���� �������� � ��������
// ������� �������� � ���������
bool SetGraph::hasArc(int from, int to) const {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return false;    // ����������� ������ ����
  return graph[from]->has(to);
}
