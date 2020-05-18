/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : diff.h                                           *
*  �������� : �������� ���������� ����� ���������������        *
*             ������ ��������� ��� ��� �����������������       *
***************************************************************/

#ifndef __DIFF_H
#define __DIFF_H

#include "visitor.h"
#include "expressionext.h"

//===============================================================
// ����� Diff ���������� ����������, ������� �������� ������
// ���������� ������ ����������� ��������� �� �������� ����������.
//===============================================================
class Diff : public Visitor {
  string variable;         // ����������, �� ������� ������� �����������
  Expression * result;     // ��������� ���������
  static Constant * zero;  // ��������� - ����
  static Constant * one;   // ��������� - �������

public :
  // �����������
  Diff(const string & var) : variable(var), result(NULL) {}

  // ������� ������� � ���������� ���������
  Expression * getResult() const { return result; }

  // ������� ��������� �����
  // ����������� ��������� ����� ����:
  void visit(Constant * cNode) { result = zero; }

  // ����������� ���������� ����� ���� ���� ������� � �����������
  // �� ����, �� �� ��� ����������, �� ������� ������� �����������
  void visit(Variable * vNode) {
    result = vNode->getVariable() == variable ? one : zero;
  }

  // �������� ������� ������ ���������� ��� ��������� �������� ��������
  void visit(Operator * opNode);
};

#endif
