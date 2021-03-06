/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.4. ���������                                      *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : ������������ ������ ������� ���������            *
***************************************************************/

#include <iostream>
#include <stdexcept>
#include "set.h"

using namespace std;

// ��������� ������� ������� ���������� ��������� �����
// � ����������� �������� ����� cout
void printSet(const Set & s) {
  cout << '[';
  bool first = true;
  for (int i = 0; i < 256; i++) {
    if (s.has(i)) {
      cout << (first ? "" : ", ") << i;
      first = false;
    }
  }
  cout << ']' << endl;
}

// ������� main ��������� ��������� �� �������
int main () {
  Set s1, s2;      // ������������ "���������" ������� ��������� [0..255]

  // ���������� ���������:
  (((s1 |= 2) |= 5) |= 25) |= 32;
  ((((s2 |= s1) |= 1) |= 5) |= 12) |= 18;

  // ������ �����������:
  cout << "s1 = "; printSet(s1);
  cout << "s2 = "; printSet(s2);

  // ��� ���� ��������� ��������� � ������� ������������ �����������
  Set s3 = s2;

  // �������� ��������
  s3 -= s1;

  // ������ �����������:
  cout << "s3 = "; printSet(s3);

  // ������� �������� �������, ������� �� ��������� ���������
  try {
    s1 |= 1000;
  } catch (const exception & x) {
    // ����� ��������� �� �������������� ��������
    cout << "Exception: " << x.what() << endl;
  }

  return 0;
}
