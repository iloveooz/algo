/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.1. ��� � ������������� ��������                   *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : erato.cpp                                        *
*  �������� : ���������� ��������� ���������� ���������������- *
*             ��� ������� ����� � ������� "������ ����������"  *
***************************************************************/

#include "erato.h"

SmartPtr<IntSet> filter(int n, const SmartPtr<IntSet> & set) {
  return SmartPtr<IntSet>(new Filter(n, set));
}

SmartPtr<IntSet> sieve(int max, const SmartPtr<IntSet> & set) {
  int first = **set->elements();
  SmartPtr<IntSet> result = set;
  if (first * first <= max) {
    result = add(sieve(max, filter(first, set)), first);
  }
  return result;
}
