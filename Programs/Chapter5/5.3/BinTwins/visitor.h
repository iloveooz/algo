/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : visitor.h                                        *
*  �������� : �������� ������������ ���������� �����           *
*             ��������������� ������ ���������                 *
***************************************************************/

#ifndef __VISITOR_H
#define __VISITOR_H

class Visitor;

#include "expression.h"

//=============================================================
// ����� Visitor ���������� ����������� ��������� ���������
// ����� ���������� ���� � �������������� ������ ���������
//=============================================================

class Visitor {
public :
  virtual void visit(Constant * cNode) = 0;
  virtual void visit(Variable * varNode) = 0;
  virtual void visit(Operator * opNode) = 0;
};

#endif
