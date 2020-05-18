/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.5. �����                                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : ArcGraph.cpp                                     *
*  �������� : ���������� ������� ������ ArcGraph               *
***************************************************************/

#include "ArcGraph.h"

// ����������
ArcGraph::~ArcGraph() {
  Arc * current = first,
      * pred = NULL;
  while (current) {
    pred = current;
    current = current->next;
    delete pred;
  }
}

// ���������� ���� � ������
void ArcGraph::addArc(int from, int to) {
  if (from < 0 || to < 0 || from >= vertexNumber || to >= vertexNumber)
    return;      // ����������� ������ ����
  Arc *newArc = new Arc(from, to);
  // ����� ���� ����������� � ����� ������
  if (last) last->next = newArc; else first = newArc;
  last = newArc;
  arcCount++;
}

// �������� ������������� ���� � �����
bool ArcGraph::hasArc(int from, int to) const {
  // ����, ������������ �������� ������ ���
  for (Arc *current = first; current; current = current->next) {
    if (current->begin == from && current->end == to) {
      // ���� �������
      return true;
    }
  }
  // ���� �� �������:
  return false;
}
