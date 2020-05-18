/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.2. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : �������� �������, ����������� ������ ���������   *
*             ������������� ������                             *
***************************************************************/

#include <iostream>
#include "treedictionary.h"

using namespace std;

int main() {
  // ������� ������� �� �� �����, ��� 100 ����
  TreeDictionary d(100);
  // ���������� ��������� ����� ����
  string text[] = {
    string("when"), string("we"), string("speak"), string("of"),
    string("free"), string("software"), string("we"), string("are"),
    string("referring"), string("to"), string("freedom"), string("not"),
    string("price"),
  };
  // ������� ����� � �������
  for (int i = 0; i < sizeof(text)/sizeof(string); i++) {
    d.addWord(text[i]);
  }
  // ������� ����� � ���������� �������
  cout << d;
}
