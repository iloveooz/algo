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
*             ������� ������ ��������� ��������                *
***************************************************************/

#include <iostream>

using namespace std;

#include "expression.h"
#include "parser.h"
#include "diff.h"
#include "simplifier.h"
#include "boardmarkers.h"

BoardMarkersMemory * memoryManagement = new BoardMarkersMemory(5000);

int main() {
  // ����������������� ��������� ���������...
  Expression * beforeDiff = Parser::parse("(x+1)/(x-1)");
  Diff dasher("x");
  beforeDiff->accept(dasher);
  Expression * afterDiff = dasher.getResult();
  cout << "Before derivative evaluation: " << (string)*beforeDiff << endl
       << "After derivative evaluation: " << (string)*afterDiff << endl;

  // ... � �������� ���
  Simplifier simplifier;
  afterDiff->accept(simplifier);
  cout << "after its simplification: " << (string)*simplifier.getResult() << endl;

  return 0;
}
