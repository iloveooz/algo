/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.3. �������������� ������                          *
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
#include "substitutor.h"
#include "simplifier.h"
#include "diff.h"

using namespace std;

//==============================================================
// ������������ ������� parse � (string) ��� ���������
//==============================================================

int main() {
  // �������� ������ ������� ��� ������������ �������
  Expression * energy0 = Parser::parse("m * v * v / 2");
  cout << "Initial expression: " << (string)*energy0 << endl;

  // �������� ��������, � ������� ���������� v ������������ �������
  Context speed;
  speed.add("v", Parser::parse("v0 + a*t"));
  cout << "Substitution " << (string)*speed.find("v") << " instead of variable v" << endl;

  // ���������� substitutor ���������� ����������� �������� ��� ������
  Substitutor substitutor(&speed);
  energy0->accept(substitutor);

  // ����� ����� ������� � �������� ��
  Expression * energy1 = substitutor.getResult();
  cout << "Result: " << (string)*energy1 << endl;

  // ����������� 0 ������ ���������� v0
  speed.add("v0", Parser::parse("0")); 
  cout << "After substitution 0 instead of v0" << endl;

  energy1->accept(substitutor); 
  Expression * energy2 = substitutor.getResult(); 
  cout << (string)*energy2 << endl;

  // �������� ��������� �����������
  Simplifier simplifier;
  energy2->accept(simplifier);
  Expression * energy3 = simplifier.getResult(); 
  cout << "After simplification: " << (string)*energy3 << endl;

  // ������ ��� ���� �����������: ���� ������ ���������� a...
  speed.add("a", Parser::parse("0"));
  energy3->accept(substitutor);
  Expression * energy4 = substitutor.getResult(); 
  cout << "0 substituted instead of \'a\': " << (string)*energy4 << endl;

  // ...� �������� ���������� ���������
  energy4->accept(simplifier);
  cout << "After the last simplification: " 
       << (string)*simplifier.getResult() << endl << endl;

  // �������, ����������������� ��������� ���������...
  Expression * beforeDiff = Parser::parse("(x+1)/(x-1)");
  Diff dasher("x");
  beforeDiff->accept(dasher);
  Expression * afterDiff = dasher.getResult();
  cout << "Before derivative evaluation: " << (string)*beforeDiff << endl
       << "After derivative evaluation: " << (string)*afterDiff << endl;

  // ... � �������� ���
  afterDiff->accept(simplifier);
  cout << "after its simplification: " << (string)*simplifier.getResult() << endl;

  return 0;
}
