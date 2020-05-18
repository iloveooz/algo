/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.2. ����� ���������� �����                         *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : MatrixGraph.h                                    *
*  �������� : ����������� ������ MatrixGraph � �����������     *
*             ����� � ���� ������� ���������� ��������         *
***************************************************************/

#ifndef __MATRIX_GRAPH_H
#define __MATRIX_GRAPH_H

#include <iostream>
#include <exception>
#include "graphweight.h"
#include "infinity.h"

class IncompatibleSizes : public std::exception {
  char * reason;
public :
  IncompatibleSizes(char * message = "Incompatible sizes of matrices") : reason(message) {}
  const char * what() const throw() { return reason; }
};

//**************************************************************
// ����������� ������ MatrixGraph �����,
// ��������������� �������� ���������
//**************************************************************

class MatrixGraph {

  friend MatrixGraph mult(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes);
  friend MatrixGraph add(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes);
  friend MatrixGraph closure(const MatrixGraph & G);
  friend void FloydWarshall(MatrixGraph & G);
  friend void getMaxPaths(const MatrixGraph & G, const GraphWeight & w, double ** & P, int ** & D);

  // ��������� ������ ���������� ��������
  bool **graph;

  // ����� ������ �����
  int vertexNumber;

public:

  // ������������
  MatrixGraph(int n);
  MatrixGraph(const MatrixGraph & src);

  // ����������
  ~MatrixGraph();

  // �������� ������������ ������
  MatrixGraph & operator = (const MatrixGraph & src);

  // ������� �������� ����� ������ ������ ������
  // ����� ����������� ��������
  int vertexCount() const { return vertexNumber; }

  // �������� ������ ������ � ������
  void addArc(int from, int to);
  void removeArc(int from, int to);
  bool hasArc(int from, int to) const;
};

// ����� ������� ��������� ����� � �������� �����

std::ostream & operator << (std::ostream &out, const MatrixGraph & matrix);

MatrixGraph mult(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes);
MatrixGraph add(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes);
MatrixGraph closure(const MatrixGraph & G);
void FloydWarshall(MatrixGraph & G);
void getMinPaths(const MatrixGraph & G, const GraphWeight & w, double ** & P, int ** & D);

#endif
