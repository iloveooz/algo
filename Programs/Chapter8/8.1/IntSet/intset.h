/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.1. ��� � ������������� ��������                   *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : intset.h                                      *
*  ��������    : �������� ������������ ��������� �����         *
***************************************************************/

#ifndef __INTSET_H
#define __INTSET_H

#include "iterator.h"
#include "smartptr.h"

class IntSet {
protected :
  //-----------------------------------------------------------
  //  ���������� ����� IntSetIterator ��������� ��������
  //  ��������� ��������� � ������� ������� contains.
  //-----------------------------------------------------------
  class IntSetIterator : public Iterator<int> {
    int currentElement;         // ������� ����������� �������
    const IntSet * currentSet;  // ����������� ���������

  public :
    // �����������
    IntSetIterator(const IntSet * set)
      : currentElement(0), currentSet(set) {}

    // ������� hasMoreElements ������ ���������� true, ��� ���
    // ���������, ������ ������, �������������� �����������
    bool hasMoreElements() const { return true; }

    // �������� * ���������� ������� ������� ���������,
    // ���� �� ����. ���� � ��������� �� ����� ���� ��� ������
    // ���������, �� ��� ������� ����� �����������.
    int operator *() {
      findNext();    // �������������, ���� ��������� ������ ���
      return currentElement;
    }

    // �������� ++ ������������ ������� � ���������� ��������,
    // ���� �� ����. ���� � ��������� �� ����� ���� ��� ������
    // ���������, �� ��� ������� ����� �����������
    Iterator<int> & operator ++() {
      findNext();    // �������������, ���� ��������� ������ ���
      currentElement++;
      return *this;
    }

  private :
    // ������� ������� ���������� ������� ������� ���������
    void findNext();
  };

public :
  // ����������� ���������� ��������� ������� ��� ����,
  // ����� ��������� �������� ����������� ���� �����������
  // ��� ����������� ��������, �������������� ���������
  virtual ~IntSet() {}

  // �������� contains - ������������������ ������� ���������.
  // ��� ������ �������� true, ���� ������� n �����������
  // ���������, � false � ��������� ������.
  virtual bool contains(int n) const = 0;

  // �������� elements ������ �������� ��������� ���������.
  // ��������� ��������� ������������ ����������, ������
  // ��������� ���� ���� ��������� ���� ��������� ����������,
  // ��, ��� �������, ����� hasMoreElements ����� ���������
  // ����� ������ �������� �������� true.
  virtual Iterator<int> * elements() const {
    return new IntSetIterator(this);
  }
};

//------------------------------------------------------------------
//  ����� SetPlusElement ��������� ������� ��������� � �����������
//  ���������
//------------------------------------------------------------------
class SetPlusElement : public IntSet {
  SmartPtr<IntSet> oldSet;       // ���������
  int newElement;                // � ����������� � ���� �������

public :

  // ����������� ��������� ����������, ����� ������� ��������
  SetPlusElement(const SmartPtr<IntSet> & set, int n)
    : oldSet(set), newElement(n)
  {}

  // ����� ������� contains ���������� �� ������ ������ ���, ���
  // ������ ���������� � ����������� ��������
  bool contains(int n) const {
    return n == newElement || oldSet->contains(n);
  }
};

//------------------------------------------------------------------
//  ����� SetPlusRange ��������� ������� ��������� � ������������
//  ���������� �� ��������� ���������
//------------------------------------------------------------------
class SetPlusRange : public IntSet {
  SmartPtr<IntSet> oldSet; // ���������
  int minElement;          // ����������� �� ����������� � ���� ���������
  int maxElement;          // ������������ �� ����������� � ���� ���������

public :

  // ����������� ��������� ����������, ����� �������� ���������
  SetPlusRange(const SmartPtr<IntSet> & set, int min, int max)
    : oldSet(set), minElement(min), maxElement(max)
  {}

  // ����� ������� contains ���������� �� ������ ������ ���, ���
  // ������ ���������� � ����������� ���������
  bool contains(int n) const {
    return (n >= minElement && n <= maxElement) || oldSet->contains(n);
  }
};

//------------------------------------------------------------------
//  ����� SetMinusElement ��������� ������� ��������� � ���������
//  ���������
//------------------------------------------------------------------
class SetMinusElement : public IntSet {
  SmartPtr<IntSet> oldSet;       // ���������
  int remElement;                // � ��������� �� ���� �������

public :

  // ����������� ��������� ����������, ����� ������� ���������
  SetMinusElement(const SmartPtr<IntSet> & set, int n)
    : oldSet(set), remElement(n)
  {}

  // ����� ������� contains ���������� �� ������ ������ ���, ���
  // ������ ���������� �� ��������� ��������
  bool contains(int n) const {
    return n != remElement && oldSet->contains(n);
  }
};

//------------------------------------------------------------------
//  ����� SetMinusRange ��������� ������� ��������� � ����������
//  ���������� �� ��������� ���������
//------------------------------------------------------------------
class SetMinusRange : public IntSet {
  SmartPtr<IntSet> oldSet; // ���������
  int minElement;          // ����������� �� ��������� �� ���� ���������
  int maxElement;          // ������������ �� ��������� �� ���� ���������

public :

  // ����������� ��������� ����������, ����� �������� ���������
  SetMinusRange(const SmartPtr<IntSet> & set, int min, int max)
    : oldSet(set), minElement(min), maxElement(max)
  {}

  // ����� ������� contains ���������� �� ������ ������ ���, ���
  // ������ ���������� �� ��������� ���������
  bool contains(int n) const {
    return (n < minElement || n > maxElement) && oldSet->contains(n);
  }
};

//------------------------------------------------------------------
//  ����� Conjunction ��������� ������� ���������, �������������
//  ������������ ���� ������ ��������
//------------------------------------------------------------------
class Conjunction : public IntSet {
  SmartPtr<IntSet> s1;    // ������ �� ������������ ��������
  SmartPtr<IntSet> s2;    // ������ ������������ ���������

public :

  // ����������� ���������� ������������ ���������
  Conjunction(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2)
    : s1(s1), s2(s2) {}

  // ������� ���������� � �����������, ���� �� ���������� � �����
  // ������������ ����������
  bool contains(int n) const {
    return s1->contains(n) && s2->contains(n);
  }
};

//------------------------------------------------------------------
//  ����� Disjunction ��������� ������� ���������, �������������
//  ������������ ���� ������ ��������
//------------------------------------------------------------------
class Disjunction : public IntSet {
  SmartPtr<IntSet> s1;     // ������ �� ������������ ��������
  SmartPtr<IntSet> s2;     // ������ ������������ ���������

public :

  // ����������� ���������� ������������ ���������
  Disjunction(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2)
    : s1(s1), s2(s2) {}

  // ������� ���������� � �����������, ���� �� ���������� ���� ��
  // � ����� �� ������������ ��������
  bool contains(int n) const {
    return s1->contains(n) || s2->contains(n);
  }
};

//------------------------------------------------------------------
//  ����� Inversion ��������� ������� ���������, �������������
//  ����������� ������� ���������
//------------------------------------------------------------------
class Inversion : public IntSet {
  SmartPtr<IntSet> oldSet;     // ������������� ���������

public :

  // ����������� ���������� ������������� ���������
  Inversion(const SmartPtr<IntSet> & s) : oldSet(s) {}

  // ������� ���������� � ��������, ���� �� �� ����������
  // � �������� ���������
  bool contains(int n) const {
    return n >= 0 && !oldSet->contains(n);
  }
};

//------------------------------------------------------------------
//  ����� Difference ��������� ������� ���������, �������������
//  ��������� ���� ������ ��������
//------------------------------------------------------------------
class Difference : public IntSet {
  SmartPtr<IntSet> s1;       // �����������
  SmartPtr<IntSet> s2;       // ����������

public :

  // ����������� ���������� ���������� ���������
  Difference(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2)
    : s1(s1), s2(s2) {}

  // ������� ���������� � ��������, ���� �� ���������� �
  // �����������, �� �� ���������� � ����������
  bool contains(int n) const {
    return s1->contains(n) && !s2->contains(n);
  }
};

//-------------------------------------------------------------
// ��� �������� ������, ����������� ������� ������� �
// �������������� (����������� ��� ��������) ��������
//-------------------------------------------------------------

class EmptySet : public IntSet {
public :
  bool contains(int n) const { return false; }
};

class UniversalSet : public IntSet {
public :
  bool contains(int n) const { return n >= 0; }
};

// ������� add ���������� ��������� � ����������� ���������
SmartPtr<IntSet> add(const SmartPtr<IntSet> & set, int n);

// ������� addRange ���������� ��������� � ������������ ����������
SmartPtr<IntSet> addRange(const SmartPtr<IntSet> & set, int min, int max);

// ������� remove ���������� ��������� � ��������� ���������
SmartPtr<IntSet> remove(const SmartPtr<IntSet> & set, int n);

// ������� removeRange ���������� ��������� � ���������� ����������
SmartPtr<IntSet> removeRange(const SmartPtr<IntSet> & set, int min, int max);

// ������� conjunct ���������� ����������� ���� ��������
SmartPtr<IntSet> conjunct(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2);

// ������� disjunct ���������� ����������� ���� ��������
SmartPtr<IntSet> disjunct(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2);

// ������� inverse ���������� ���������� ���������
SmartPtr<IntSet> inverse(const SmartPtr<IntSet> & s);

// ������� diff ������ �������� ���� �������� ��������
SmartPtr<IntSet> diff(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2);

#endif
