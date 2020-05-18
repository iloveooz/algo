/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.3. ����� � �������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : �������� ������� �� ���������� ��������� �       *
*             ������� ���� ������                              *
***************************************************************/

#include <stdio.h>
#include "calc.h"
#include "operator.h"
#include "stackfactory.h"
#include "liststack.h"

// ����������, �������������� ����������� ������� ������,
// ���������������� ��������� ������ ListStackFactory

// ������� ��� �������� ������ �� ����� �����
StackFactory<int> * stackIntFactory = new ListStackFactory<int>;

// ������� ��� �������� ����� �� ����������
StackFactory<Operator> * stackOpFactory = new ListStackFactory<Operator>;

// ������� ����������� �������
int main() {
  // ��������� ��� ������������:
  char * test = "5 - (2+3) * (15-10)";

  // �������� ����������:
  printf("%s = %d\n", test, exprValue(test));

  return 0;
}
