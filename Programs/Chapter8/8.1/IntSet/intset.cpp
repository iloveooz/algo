/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.1. ��� � ������������� ��������                   *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : intset.cpp                                       *
*  �������� : ���������� ��������� ����������� ����� � ������� *
*             ������������� � ���� ������������������ �������  *
***************************************************************/

#include "intset.h"

void IntSet::IntSetIterator::findNext() {
  while (!currentSet->contains(currentElement)) {
    currentElement++;
  }
}

// ������� add ���������� ��������� � ����������� ���������
SmartPtr<IntSet> add(const SmartPtr<IntSet> & set, int n) {
  return SmartPtr<IntSet>(new SetPlusElement(set, n));
}

// ������� addRange ���������� ��������� � ������������ ����������
SmartPtr<IntSet> addRange(const SmartPtr<IntSet> & set, int min, int max) {
  return SmartPtr<IntSet>(new SetPlusRange(set, min, max));
}

// ������� remove ���������� ��������� � ��������� ���������
SmartPtr<IntSet> remove(const SmartPtr<IntSet> & set, int n) {
  return SmartPtr<IntSet>(new SetMinusElement(set, n));
}

// ������� removeRange ���������� ��������� � ���������� ����������
SmartPtr<IntSet> removeRange(const SmartPtr<IntSet> & set, int min, int max) {
  return SmartPtr<IntSet>(new SetMinusRange(set, min, max));
}

// ������� conjunct ���������� ����������� ���� ��������
SmartPtr<IntSet> conjunct(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2) {
  return SmartPtr<IntSet>(new Conjunction(s1, s2));
}

// ������� disjunct ���������� ����������� ���� ��������
SmartPtr<IntSet> disjunct(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2) {
  return SmartPtr<IntSet>(new Disjunction(s1, s2));
}

// ������� inverse ���������� ���������� ���������
SmartPtr<IntSet> inverse(const SmartPtr<IntSet> & s) {
  return SmartPtr<IntSet>(new Inversion(s));
}

// ������� diff ������ �������� ���� �������� ��������
SmartPtr<IntSet> diff(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2) {
  return SmartPtr<IntSet>(new Difference(s1, s2));
}
