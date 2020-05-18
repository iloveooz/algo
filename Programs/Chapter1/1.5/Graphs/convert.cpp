/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.5. �����                                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : convert.h                                        *
*  �������� : ����������� ������� �������������� ������        *
***************************************************************/

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include "convert.h"

// �������������� �� A-����� � M-����
MatrixGraph * convert(const ArcGraph & srcGraph) {
  int n = srcGraph.vertexCount();
  MatrixGraph *destGraph = new MatrixGraph(n);
  // ���� �� ����� ������
  for (ArcGraph::Arc * current = srcGraph.first;
       current; current = current->next) {
    // ���������� �������� "������" ��� ���������������� �������� �������
    destGraph->graph[current->begin][current->end] = true;
  }
  return destGraph; 
}

// �������������� �� M-����� � S-����
SetGraph * convert(const MatrixGraph & srcGraph) {
  int n = srcGraph.vertexCount();
  SetGraph *destGraph = new SetGraph(n);
  for (int i = 0; i < n; i++) {
    bool * srcRow = srcGraph.graph[i];    // ������������� ������ ��������� �����
    Set & destRow = *destGraph->graph[i]; // ��������������� ��������� ��������������� �����
    for (int j = 0; j < n; j++) {
      // ����� ���� ������������ � ������� �������� ���������� �������� � ���������
      if (srcRow[j]) destRow |= j;
    }
  }
  return destGraph; 
}

// �������������� �� S-����� � L-����
ListGraph * convert(const SetGraph & srcGraph) {
  int n = srcGraph.vertexCount();
  ListGraph *destGraph = new ListGraph(n);
  for (int i = 0; i < n; i++) {
    Set & srcRow = *srcGraph.graph[i];          // ������������� ������ ��������� �����
    List<int> & destRow = destGraph->graph[i];  // ��������������� ������ ��� � �������������� �����
    for (int j = 0; j < n; j++)
      // ����� ���� ������������ � ������� �������� ���������� �������� � ������
      if (srcRow.has(j)) destRow.add(j);
  }
  return destGraph; 
}

// �������������� �� L-����� � A-����
ArcGraph * convert(const ListGraph & srcGraph) {
  int n = srcGraph.vertexCount();
  ArcGraph *destGraph = new ArcGraph(n);
  // ���� ����� ���������� ��� ���� ����� ��������� �����
  for (int i = 0; i < n; i++) {
    // ������ ����������� ��������������� � �������������� ������ � ��� ���������
    List<int>::ListItem *current = srcGraph.graph[i].first;
    while (current) {
      // ����� ���� ������������ � ���� � ������� �������� ���������� ����
      destGraph->addArc(i, current->item);
      current = current->next;
    }
  }
  return destGraph; 
}
