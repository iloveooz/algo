/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.1. ������ � ����� � ������                        *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : graphactor.h                                  *
*  ��������    : �������� ������������ ���������� ���������    *
*                �����                                         *
***************************************************************/

#ifndef __GRAPH_ACTOR_H
#define __GRAPH_ACTOR_H

class GraphActor {
public :
  virtual void vertexIn(int vertex) {}
  virtual void vertexOut(int vertex) {}
  virtual void arcForward(int begin, int end, bool newVertex) {}
  virtual void arcBackward(int begin, int end) {}
  virtual void newSelection(int vertex) {}
};

#endif
