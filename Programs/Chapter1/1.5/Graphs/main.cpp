/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.5. �����                                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : ������� ������������ ������������� �             *
*             �������������� ������                            *
***************************************************************/

#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include "convert.h"

using namespace std;

//-------------------------------------------------------------
// ������ ������� ���������� ������ ��� ������������
// ��� ������� ����������� ����� � ���� ������� ���������. 
// ���������! ������� ����� ������ ������ ������������� ���
// ����������� ������������� ������ ����� ����� ������� ��������.
//-------------------------------------------------------------

void print(const Graph & g) {
  int n = g.vertexCount();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << (g.hasArc(i, j) ? '1' : '0') << ' ';
    }
    cout << endl;
  }
}

//-------------------------------------------------------------
// �������� ����������� ������� ������� A-���� � ���������������
// ����������� ��� ������� � �-����, ����� � S-����, ����� �
// L-���� �, �������, ������� � �-����. ����� ������� ��������������
// ���� ��������� � ����������� �������� �����. ���� ������
// ���������� ���������� ����� ������� ��������������
//-------------------------------------------------------------

int main() {
  ArcGraph arcGraph(5);
  arcGraph.addArc(0, 1);
  arcGraph.addArc(0, 3);
  arcGraph.addArc(1, 2);
  arcGraph.addArc(1, 3);
  arcGraph.addArc(1, 4);
  arcGraph.addArc(3, 2);
  arcGraph.addArc(4, 1);
  cout << "Initial ArcGraph:\n";
  print(arcGraph);
  cout << endl;

  // �������������� � M-����
  MatrixGraph & matrixGraph = *convert(arcGraph);
  cout << "Coverted to MatrixGraph:\n";
  print(matrixGraph);
  cout << endl;

  // �������������� � S-����
  SetGraph & setGraph = *convert(matrixGraph);
  cout << "Coverted to SetGraph:\n";
  print(setGraph);
  cout << endl;

  // �������������� � L-����
  ListGraph & listGraph = *convert(setGraph);
  cout << "Coverted to ListGraph:\n";
  print(listGraph);
  cout << endl;

  // �������������� ������� � A-����
  ArcGraph & newArcGraph = *convert(listGraph);
  cout << "Coverted to ArcGraph:\n";
  print(newArcGraph);
  cout << endl;

  return 0;
}

