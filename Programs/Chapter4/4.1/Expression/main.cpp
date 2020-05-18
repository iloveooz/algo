/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.1. ������������� ���������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : �������� ��������� �������� ��� ��������������   *
*             ��������� � ���� ��������������� ������          *
***************************************************************/

#include <string>
#include <iostream>
#include "expression.h"
#include "dictionary.h"
#include "varcollector.h"
#include "copier.h"

using namespace std;

//==============================================================
// ������������ ������� parse � (string) ��� ���������
//==============================================================

int main() {
  // ������� ����������� ������ � �������������� ������ ���������
  Expression * expr = Expression::parse("(a + b)*(c + d) + 1 + 2*a");

  // � ����� ����������� ��� ������ � ������ � ������� ���.
  cout << (string)*expr << endl;
  // �������� ��������� � ���������, ��� ��� ����������� ���������
  // ��������� ��� ����� ��-�������� ����������
  Expression * exprCopy = expr->copy();
  delete expr;
  cout << (string)*exprCopy << endl;

  // ���� ���������� � ���������� ��������� � ������� ������� ������������ ������
  HashDictionary * vars = exprCopy->allVariables();

  // ������ ����������
  cout << *vars << endl;

  delete vars;

  // ���� ���������� � ���������� ��������� � ������� ����������
  VariableCollector collector;
  exprCopy->accept(collector);

  // ������ ����������
  cout << collector.getResult() << endl;

  // ������ ������ ����� ��������� � ������� ����������:
  Copier copier;
  exprCopy->accept(copier);
  Expression * copy2 = copier.getResult();

  // ��������� ���������� � ������� �������� ���������
  cout << "Expression is " << (*copy2 == *exprCopy ? "equal" : "not equal") << " to its copy" << endl;

  delete exprCopy;

  // �������� ����� �����
  cout << (string)*copy2 << endl;

  return 0;
}
