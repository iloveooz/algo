/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.1. ��� � ������������� ��������                   *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : erato.h                                          *
*  �������� : ���������� ��������� ���������� ���������������- *
*             ��� ������� ����� � ������� "������ ����������"  *
***************************************************************/

#ifndef __ERATO_H
#define __ERATO_H

#include "intset.h"

//-------------------------------------------------------------
// �����, �������������� ��������� ���� ����������� �����,
// ������� �������
//-------------------------------------------------------------
class From2 : public IntSet {
public :
  bool contains(int n) const { return n >= 2; }
};

//-------------------------------------------------------------
// ����� ��� ������� ��������� ���������� ���������
// �������� ��������� "������ ����������"
//-------------------------------------------------------------
class Filter : public IntSet {
  int f;                 // ���������, �������� ������������� �����
  SmartPtr<IntSet> set;  // �������� ���������

public :
  // ����������� ���������� � ������ �������� ������:
  Filter(int f, const SmartPtr<IntSet> & set) : f(f), set(set) {}

  // ������������������ ������� ��������������� ���������:
  bool contains(int n) const {
    return n % f != 0 && set->contains(n);
  }
};

// ������� ��� ���������� ��������� "������ ����������"
extern SmartPtr<IntSet> filter(int n, const SmartPtr<IntSet> & set);
extern SmartPtr<IntSet> sieve(int max, const SmartPtr<IntSet> & set);

#endif
