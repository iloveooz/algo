/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.5. �����                                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : Graph.h                                          *
*  �������� : ����������� ������������ ������ Graph            *
***************************************************************/

#ifndef __GRAPH_H
#define __GRAPH_H

//**************************************************************
// ����������� ���� - ������� ����� ��� ���� ������������� �����
//**************************************************************

class Graph {

public:

  // ������ ����������� �������, ��������� ���������������
  // ��� ������� ����������� ������������� �����

  // ����������� ������ ����������
  virtual ~Graph() {}
  // ���������� ����
  virtual void addArc(int from, int to) = 0;
  // ����� ����
  virtual bool hasArc(int from, int to) const = 0;
  // ������� ����� ������
  virtual int vertexCount() const = 0;
};

#endif
