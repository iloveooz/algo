/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : ���� ������� ������������� � ���������� �������  *
*             ������ ����������� �������, ��������������� �    *
*             ������� ������ ��������� ��������                *
***************************************************************/

#include <iostream>
#include "expression.h"
#include "parser.h"
#include "diff.h"
#include "simplifier.h"

using namespace std;

#include "bintwins.h"

BinTwinsMemory * memoryManagement = new BinTwinsMemory(20);

int main() {
  // ����������������� ��������� ���������...
  Expression * beforeDiff = Parser::parse("(x+1)/(x-1)+(x*x+x+1)/x");
  Diff dasher("x");
  beforeDiff->accept(dasher);
  Expression * afterDiff = dasher.getResult();
  cout << "Before derivative evaluation: " << (string)*beforeDiff << endl
       << "After derivative evaluation: " << (string)*afterDiff << endl;

  // ... � �������� ���
  Simplifier simplifier;
  afterDiff->accept(simplifier);
  cout << "after its simplification: " << (string)*simplifier.getResult() << endl;

  // ����� �������������� ������:
  cout << "Memory management statistics: " << BinTwinsMemory::getClaims()
       << " demands; memory needs: " << BinTwinsMemory::getDemanded()
       << " bytes; memory reserved: " << BinTwinsMemory::getReserved()
       << " bytes; percentage of usage: " << (100.0 * BinTwinsMemory::getDemanded() / BinTwinsMemory::getReserved())
       << " %" << endl;

  return 0;
}
