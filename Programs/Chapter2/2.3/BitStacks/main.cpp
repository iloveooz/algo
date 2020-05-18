/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.2. ����� � �������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : bitmain.cpp                                      *
*  �������� : �������, ������������� ������������ �����������  *
*             ������, ������������ ������� ���� ��� ��������   *
*             ���������� � ������ ����� ������.                *
***************************************************************/

#include <iostream>
#include "bitstack.h"

using namespace std;

//==============================================================
// ������� ������� ������������ ����������� ������.
// ���������� ������, ���� ���������� ����������� � ����������� 
// ������ ������ ���� ���������, � ��� ����� ���������� �����������.
// ��������������� ������ ���� ������: ������� � ����������.
// ���������:
// - txt - �������� �����, ���������� ������.
// - maxdeep - ����������� ��������� ������� ����������� ������.
//==============================================================

bool brackets(const char *txt) {
  // �������� ����� ��� �������� ���������� � �������
  BitStack stk;

  // ���� ��������� ��������� ��������, �� ��������
  // ������������� �������������� ��������.
  try {
    char c;
    // ���� ������� ������ ������ �� ��������.
    // ������������� ������ ������� � ���������� ������,
    // ��������� ������� ������ ������������.
    for (int i = 0;  (c = txt[i]);  i++) {
      switch (c) {
        // ����� ������ ���������� � ���� (0 - �������, 1 - ����������)
        case '(':
        case '[':
          stk.push(c == '[');
          break;
        // ������ ������ ����������� �� ������������ ����
        // �� �������, ������� �� ������� �����.
        case ')':
        case ']':
          // �������� ������������.
          if (stk.top() != (c == ']')) {
            return false;
          }
          // ������� ����� ������ � ������� �����.
          stk.pop();
          break;
      }
    }
    // ��������� ����� ������. ��� � �������, ���� ���� ����.
    return stk.empty();
  } catch (StackUnderflow) {
    // ���������� ������ ������ ������!
    return false;
  }
}

// Test main function
int main() {
  char *text = "( ( [[ ]([ ])]) ) ";
  cout << text << ": " << (brackets(text) ? "right" : "wrong") << endl;

  return 0;
}
