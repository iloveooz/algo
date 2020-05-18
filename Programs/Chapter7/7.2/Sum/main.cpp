/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 7. ����� ����������� � ��������� ���������        *
*          7.2. �� ����� ������� ���������� �������� ����      *
*                                                              *
*  �����    : �. ���������                                     *
*  ����     : main.cpp                                         *
*  �������� : �������� ������� ������ ����������� ���          *
*             ���������� �������� ����                         *
***************************************************************/

#include <iostream>
#include "emember.h"
#include "fibmember.h"
#include "fibmember1.h"
#include "lnmember.h"
#include "sum.h"

using namespace std;

int main() {
  // 1. ���������� ������������� �������� ����� �
  EMemberFactory eFactory;
  cout << "Approximate value for e = " << sum(eFactory, 10) << endl;

  // 2. ���������� ����� ������ ������ ������������������ ���������
  FibMemberFactory fibFactory;
  cout << "Fibonacci sum of 10 numbers = " << sum(fibFactory, 10) << endl;

  // 3. ���������� ������������� �������� ������������ ��������� ����� 2
  LnMemberFactory lnFactory;
  cout << "Approximate value for ln 2 = " << sum(lnFactory, 100) << endl;

  // 4. ���������� ����� ������ ������ ������������������ ���������
  //    (���������������� �������)
  FibMemberFactory1 fibFactory1;
  cout << "Fibonacci sum of 10 numbers = " << sum(fibFactory1, 10) << endl;

  return 0;
}
