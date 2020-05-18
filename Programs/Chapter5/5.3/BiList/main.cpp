/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : bilistmemory.cpp                                 *
*  �������� : ���� ������� ������������� � ���������� �������  *
*             ������ ����������� �������, ��������������� �    *
*             ��������� ��������������� ������                 *
***************************************************************/

#include "bilistmemory.h"
#include <iostream>

#include "expression.h"
#include "parser.h"
#include "diff.h"
#include "simplifier.h"

using namespace std;

BiListMemory * memoryManagement = new BiListMemory(2000);

int main() {
  // ����������������� ��������� ���������...
  Expression * beforeDiff = Parser::parse("(x+1)/(x-1)");
  Diff dasher("x");
  beforeDiff->accept(dasher);
  Expression * afterDiff = dasher.getResult();
  cout << "Before derivative evaluation: " << (string)*beforeDiff << endl;
  cout << "After derivative evaluation: " << (string)*afterDiff << endl;

  // ... � �������� ���
  Simplifier simplifier;
  afterDiff->accept(simplifier);
  cout << "after its simplification: " << (string)*simplifier.getResult() << endl;

  return 0;
}
