/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.2. ���������� �� ��������                         *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : �������� ��������� �������� ��� ��������������   *
*             ��������� � ���� ��������������� ������          *
***************************************************************/

#include <string>
#include <iostream>
#include "parser.h"
#include "expression.h"
#include "evaluator.h"

using namespace std;

//==============================================================
// ������������ ������� parse � (string) ��� ���������
//==============================================================

int main() {
  // ������� ����������� ������ � �������������� ������ ���������
  Expression * expr = Parser::parse("(a + b)*(c + d) + 1 + 2*a");

  // ������� �������� ���������� � ������� ��������� ��������
  // ��������� � ��������� ���������
  Context ctx;
  ctx.add("a", new Integer(1));
  ctx.add("b", new Integer(3));
  ctx.add("c", new Integer(2));
  ctx.add("d", new Integer(-1));

  // ���������� ������� �������������
  cout << (string)*expr << " has a value of "
       << (string)*(expr->evaluate(ctx)) << endl;

  // ���������� � ������� ����������
  Evaluator evaluator(&ctx);
  expr->accept(evaluator);
  cout << (string)*expr << " has a value of "
       << (string)*evaluator.getResult() << endl;

  return 0;
}
