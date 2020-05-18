/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.1. ������� ������������� �����                    *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : ���� ��������� �������� ��� ��������, ��������-  *
*             ������� � ���� ������ ��������� ���������        *
***************************************************************/

#include "ListString.h"
#include <iostream>

using namespace std;

int main() {
  // ������� ��������� ��������� ������
  ListString s("We all live in a yellow submarine!");

  // ��������� ������ ��������� � ����������� ���������� �����
  // ����� �������� �������������� �� � ������������ �������������
  cout << "Before insertion: " << s << endl;

  // ����������� ����� ������
  int len = s.length();

  // � ������ ����������� ����� ���������
  s.insert(len-1, ", yellow submarine");
  s.insert(len-1, ", yellow submarine");

  // �������� ��, ��� ����������
  ListString s1 = s;

  // �������� ����� �� ������
  ListString word = s.substr(17, 23);

  // ������ � ����� ������� ��� ��������� ��������.
  // �������, ��� �������� ��������� ������
  ((cout << "String: [" << (char*)s << "] has the structure: ") <<= s) << endl;
  s += " Yeah!";
  ((cout << "String: [" << (char*)s << "] has the structure: ") <<= s) << endl;
  s += " Yeah!";
  ((cout << "String: [" << (char*)s << "] has the structure: ") <<= s) << endl;
  s += " Yeah!";
  ((cout << "String: [" << (char*)s << "] has the structure: ") <<= s) << endl;

  // ������������� ��������� ����������
  cout << "After insertion: " << (char*)s << endl;
  cout << "Before appending: " << (char*)s1 << endl;
  cout << "A word from the string: " << (char*)word << endl;

  return 0;
}
