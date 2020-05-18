/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.4. ���������                                      *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : set.h                                            *
*  �������� : ����������� ������ Set � ����������� ���������   *
*             � ���� ������� �����                             *
***************************************************************/

#ifndef __SET_H
#define __SET_H

typedef unsigned short WORD;          // 16-������� ����������� �����

class Set {

  int minElem;    // ������ ������� �����
  int maxElem;    // ������� ������� �����
  WORD *elems;    // ���� �����
  int numWords;   // ����� ����� � ������ (WORDs)

  // �������� ��� �����������: �����������, �����������, ��������, ����������

  friend const Set & operator | (const Set & s1, const Set & s2);
  friend const Set & operator & (const Set & s1, const Set & s2);
  friend const Set & operator - (const Set & s1, const Set & s2);
  friend const Set & operator - (const Set & s);

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

  // ����������� ��������
  Set & operator &= (const Set & other);

  // �������� �������� �� ���������
  Set & operator -= (int n);

  // �������� ��������� �� ��������� (�������� ��������)
  Set & operator -= (const Set & other);

  // �������� (���������� ����������) ���������
  Set & inverse();
};

#endif
