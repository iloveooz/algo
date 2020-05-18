/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.5. �����                                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : MatrixGraph.cpp                                  *
*  �������� : ���������� ������� ������ MatrixGraph            *
***************************************************************/

#include "MatrixGraph.h"

// �����������
MatrixGraph::MatrixGraph(int n) {
  graph = new bool*[vertexNumber = n];
  for (int i=0; i<n; i++) {
    // �������� ������
    bool *row = graph[i] = new bool[n];
    // ������������� ��������� ������
    for (int j = 0; j < n; j++) {
      row[j] = false;
    }
  }
}

// ����������
MatrixGraph::~MatrixGraph() {
  for (int i = 0; i < vertexNumber; i++) {
    delete graph[i];
  }
  delete graph;
}

// ���������� ���� - ������� ������� ��������������� � true
void MatrixGraph::addArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;    // ����������� ������ ����
  graph[from][to] = true;
}

// �������� ������������� ����
bool MatrixGraph::hasArc(int from, int to) const {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return false;    // ����������� ������ ����
  return graph[from][to];
}

