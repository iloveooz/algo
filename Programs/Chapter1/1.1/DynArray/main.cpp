/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.1. �������                                        *
*                                                              *
*  �����    : A.���������                                      *
*  ����     : dynarray.cpp                                     *
*  �������� : ������������ ������ DynArray                     *
***************************************************************/

#include <iostream>
#include "dynarray.h"

using namespace std;

/*****************************************************************
  ��������� ����� ������������ ����� ������� ��� ������������
  ������ ������ DynArray. ������� doCode �������� ������, ���������
  ������������ ������ � �������� ������� �������. ������� main
  ���������� �� ��� ����������� ������ "Hello, world!".
******************************************************************/

// ������� �������������� ����� ���������� �������,
// �������� ������������ ��������.
void doCode(char * source, char * dest, DynArray<char> & codeTable) {
  for (int i = 0;  source[i];  i++) {
    dest[i] = codeTable[source[i]];
  }
}

int main() {
  DynArray<char> codeTable(128);
  for (int c = 0; c < 128; c++) codeTable[c] = c;
  // "��������������" ������� ������� ��� ��������� ��������� ����
  for (int i = 0; i < 13; i++) {
    char b = codeTable['a' + i];
    codeTable['a' + i] = codeTable['z' - i];
    codeTable['z' - i] = b;
  }

  char *src = "Hello, World!";            // �������� ���������
  char *dst = new char[strlen(src) + 1];  // ����� ��� ����������
  memset(dst, 0, strlen(src) + 1);
  doCode(src, dst, codeTable);
  cout << "Source string : <" << src << ">\n"
       << "Destination string : <" << dst << ">\n";
  return 0;
}

