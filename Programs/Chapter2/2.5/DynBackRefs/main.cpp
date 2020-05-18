/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.5. ����������� ��������                           *
*                                                              *
*  �����    : A.Koubenski                                      *
*  ����     : main.cpp                                         *
*  �������� : ������� �������� ������ ��������� ������ �����   *
*             ������ � ������������ ���������� ������.         *
***************************************************************/

#include "actor.h"
#include "tree.h"
#include "charAnalizer.h"
#include <iostream>

using namespace std;

// ��������, ������������ ������� Printer, ���������� �����
// ����������� ���� ������ � ����������� �������� �����.
class Printer : public Actor<char> {
public :
  void action(char & c) { cout << c; }
};

int main() {
  // ������ ��������� ������������� ������ �� �������� � ������������
  // � ���, ��� ��� ���������� ��������� ������ CharAnalizer
  CharAnalizer analizer("(A(B(D(G()())(H()()))())(C(E()())(F(I()())())))");
  // ������ ������ �� ��������
  Tree<char> t(analizer);
  // ����������� ������ ������
  cout << "Tree structure expressed in parantheses:" << endl;
  t.print(cout);
  cout << endl;

  // ������ ����������� ����� ������ � ������� �������������� ������
  // � ������� ����������� ��������� � ���������� ������ traverseWithInversion
  Printer p;
  cout << "Tree nodes in left infix order (internal iterator using references inversion):" << endl;
  t.traverseWithInversion(p);
  cout << endl << endl;

  // ����������� ������ ������ ����� ������ ��������� ������
  cout << "Tree structure again after traverse algorithm working:" << endl;
  t.print(cout);
  cout << endl;

  return 0;
}
