/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.1. ��� � ������������� ��������                   *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : main.cpp                                      *
*  ��������    : �������� ���������� ��������� ������� �����   *
***************************************************************/

#include <iostream>
#include "erato.h"

using namespace std;

int main() {
  // ��������� ����������� �����, ������� �������:
  SmartPtr<IntSet> from2(new From2());
  // ���������� �������� ��������� � ������� "������ ����������"
  SmartPtr<IntSet> primes = sieve(1000, from2);
  
  // ������� ���������:
  int n;
  Iterator<int> * it = primes->elements();
  while ((n = **it) < 1000) {
    cout << " " << n;
    ++*it;
  }

  return 0;
}
