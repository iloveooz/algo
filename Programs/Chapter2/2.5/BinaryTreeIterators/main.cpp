/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.5. ����������� ��������                           *
*                                                              *
*  �����    : A.Koubenski                                      *
*  ����     : main.cpp                                         *
*  �������� : ������� �������� ������ ������� ����������       *
*             ������.                                          *
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

  // ������ ����������� ����� ������ � ������� ����������� ������ "� ������".
  // ������������ �������� BreadthFirst, ���������� � ������� ������ t.iteratorBF
  cout << "Tree nodes in breadth first order (external iterator using queue):" << endl;
  Iterator<char> * iBF = t.iteratorBF();
  for (; iBF->hasMoreElements(); ++*iBF) {
    cout << **iBF;
  }
  cout << endl << endl;
  delete iBF;

  // ������ ����������� ����� ������ � ������� �������������� ������
  // � ������� ����������� ��������� traverseInfixLeft
  Printer p;
  cout << "Tree nodes in left infix order (internal iterator using recursive function):" << endl;
  t.traverseInfixLeft(p);
  cout << endl << endl;

  // ������ ����������� ����� ������ � ������� ����������� ������ � ��������� 
  // ����� � ����� � ������� ����������� ��������� traverseUpDown
  cout << "Tree nodes in up-down order (internal iterator using stack):" << endl;
  t.traverseUpDown(p);
  cout << endl << endl;

  // ������ ����������� ����� ������ � ������� �������������� ������
  // � ������� ����������� ��������� traverseInfix
  cout << "Tree nodes in left infix order (internal iterator using stack):" << endl;
  t.traverseInfix(p);
  cout << endl;

  return 0;
}
