/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.3. ����� � �������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : calc.h                                           *
*  �������� : ������� ��� ���������� �������� ��������� ��     *
*             ���� ������                                      *
***************************************************************/

#ifndef __CALC_H
#define __CALC_H

#include <exception>

using namespace std;

//==============================================================
// �������������� �������� WrongExpression ���������
// ��� ����������� ������ � ����������� ���������.
//==============================================================

class WrongExpression : public exception {
  char * reason;
public:
  WrongExpression() : reason("Wrong expression") {}
  const char * what() const throw() { return reason; }
};

// ���������� �������

int exprValue(char * expr);

#endif
