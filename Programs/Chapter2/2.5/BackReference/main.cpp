/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.5. ����������� ��������                           *
*                                                              *
*  �����    : A.Koubenski                                      *
*  ����     : main.cpp                                         *
*  �������� : ������� �������� ������ �������� ���������       *
*             ��������� ������ � ��������� ��������.           *
***************************************************************/

#include "tree.h"
#include "charAnalizer.h"
#include <iostream>

using namespace std;

int main() {
  // ������ ��������� ������������� ������ �� �������� � ������������
  // � ���, ��� ��� ���������� ��������� ������ CharAnalizer
  CharAnalizer analizer("(A(B)(C(E)(F(H)(I)(K)))(D(G)))");
  // ������ ������ �� ��������
  Tree<char> t(analizer);
  // ����������� ������ ������
  cout << "Tree structure expressed in parantheses (youngest sons marked with dashes):" << endl;
  t.print(cout);
  cout << endl;

  // ������ ����������� ����� ������ � ������� ����������� ������ "� �������".
  // ������������ �������� BackRefIterator, ���������� � ������� ������ t.iteratorBR
  cout << "Tree nodes in depth first order (external iterator using back references):" << endl;
  Iterator<char> * iBR = t.iteratorBR();
  for (; iBR->hasMoreElements(); ++*iBR) {
    cout << **iBR;
  }
  cout << endl << endl;
  delete iBR;

  return 0;
}
