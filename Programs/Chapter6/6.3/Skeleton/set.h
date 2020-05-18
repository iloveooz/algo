/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.2. ����� ���������� �����                         *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : set.h                                            *
*  �������� : ����������� ������ Set � ����������� ���������   *
*             � ���� ������� �����                             *
***************************************************************/

#ifndef __SET_H
#define __SET_H

#include "iterator.h"

typedef unsigned short WORD;          // 16-������� ����������� �����

class Set {

  // �������� ��� �����������: �����������, �����������, ��������, ����������

  friend const Set & operator | (const Set & s1, const Set & s2);
  friend const Set & operator & (const Set & s1, const Set & s2);
  friend const Set & operator - (const Set & s1, const Set & s2);
  friend const Set & operator - (const Set & s);

  int minElem;    // ������ ������� �����
  int maxElem;    // ������� ������� �����
  WORD *elems;    // ���� �����
  int numWords;   // ����� ����� � ������ (WORDs)

  class SetIterator : public Iterator<int> {
    // ���������:
    Set * set;
    // "�����" �������� ��������:
    int nextWord;
    int nextBit;
    // ���������� ������������ ��������� ���������:
    int left;
  public :
    SetIterator(Set * set) : set(set), nextWord(-1), nextBit(15), left(set->card()+1) { ++*this; }
    bool hasMoreElements() const { return left > 0; }
    Iterator<int> & operator ++();
    const int & operator *() const { return nextWord*16 + nextBit + set->minElem; }
  };

public:
    
  // �����������
  Set(int min = 0, int max = 255);

  // ����������� �����������
  Set(const Set & s);

  // ����������
  ~Set();

  // �������� �������������� �������� ���������
  bool has(int n) const;

  // ���������� ��������
  Set & operator |= (int n);

  // ���������� ��������� (����������� ��������)
  Set & operator |= (const Set & other);

  // ���������� ����� �� ��������� ���������
  Set & addScale(int from, int to);

  // �������� ����� �� ��������� ���������
  Set & remScale(int from, int to);

  // ����������� ��������
  Set & operator &= (const Set & other);

  // �������� �������� �� ���������
  Set & operator -= (int n);

  // �������� ��������� �� ��������� (�������� ��������)
  Set & operator -= (const Set & other);

  // �������� (���������� ����������) ���������
  Set & inverse();

  // ���������� ��������� ���������
  int card() const;

  // �������� ������� ���������
  bool empty() const;

  // �������� ���������
  Iterator<int> * iterator() { return new SetIterator(this); }
};

#endif
