/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.1. �������                                        *
*                                                              *
*  �����    : A.���������                                      *
*  ����     : dynarray.h                                       *
*  �������� : ����������� ������� ������� DynArray             *
***************************************************************/

#ifndef __DYN_ARRAY_H
#define __DYN_ARRAY_H

#include <stdexcept>     // ����������� �������������� ��������

using namespace std;

template <class Elem>
class DynArray {
  int size;        // ������� ������ ������� (���������� ���������)
  int maxSize;     // ������ ���������� ������
  Elem *array;     // ��� ������ (������� maxSize)

public :
  // ����������� ������ �������. ��������� ���������, ������� ������
  // ���� ������� ��� ��� ��������, � ������� ����� ������ ������������.
  // ��� ���� �������������� �������� �������� ������ ���
  // ��������� ������������� ���������
  DynArray(int sz = 0, int maxSz = 0, Elem *iniArray = NULL);

  // ����������� �����������
  DynArray(const DynArray<Elem> & a) {
    size = maxSize = 0;
    *this = a;
  }

  // ���������� � ����������� ������� ����� ������.
  ~DynArray() { delete[] array; }

  // �������� ���������
  Elem & operator [] (int i);

  // �������� ������������� �����������
  DynArray<Elem> & operator = (const DynArray<Elem> & a);

  // ��������� �������� ������� �������. �������� delta ������
  // ������ ��������� (������������� � ���������� �������;
  // ������������� - ����������)
  void resize(int delta);

  // ���������� ������ �������� � ��������� ����������� �������
  void add(const Elem & e);

private:

  // �������� ���������� �������
  void enlarge(int delta);

  // �������� ���������� ������� �������
  void shrink(int delta);
};     // ����� ����������� ������ DynArray

// ����� ������� ���������� �������-������ ������ DynArray
// ���������� ������������
template <class Elem>
DynArray<Elem>::DynArray(int sz, int maxSz, Elem *iniArray) {
  if ((size = sz) < 0) {
    throw out_of_range("DynArray constructor : Negative array size");
  }
  maxSize = (maxSz < sz ? sz : maxSz);
  array = new Elem[maxSize];      // ��������� ������
  if (iniArray) {                 // ����������� ���������
    for (int i = 0; i < size; i++)
      array[i] = iniArray[i];
  }
}

// ���������� �������� ����������
template <class Elem>
Elem & DynArray<Elem>::operator [] (int i) {
  if (i < 0 || i >= size) {
    throw out_of_range("operator [] : Array index is out of range");
  }
  return array[i];
}

// ���������� �������� ������������ (������������� �����������)
template <class Elem>
DynArray<Elem> & DynArray<Elem>::operator = (const DynArray<Elem> & a) {
  resize(a.size - size);
  for (int i = 0; i < size; i++)
    array[i] = a.array[i];
  return *this;
}

// ���������� �������� ��������� �������� ������� �������
template <class Elem>
void DynArray<Elem>::resize(int delta) {
  if (delta > 0) enlarge(delta);        // ���������� ������� �������
  else if (delta < 0) shrink(-delta);   // ���������� ������� �������
}

// ���������� �������� ���������� ��������
template <class Elem>
void DynArray<Elem>::add(const Elem & e) {
  resize(1);
  array[size-1] = e;
}

// ���������� �������� ���������� �������
template <class Elem>
void DynArray<Elem>::enlarge(int delta) {
  if ((size += delta) > maxSize) {   // ���������� �������� ����� ������
    maxSize = size;
    Elem *newArray = new Elem[maxSize];
    // �������� ��������
    for (int i =0;  i < size - delta;  i++)
      newArray[i] = array[i];
    array = newArray;
  }
}

// ���������� �������� ���������� ������� �������
template <class Elem>
void DynArray<Elem>::shrink(int delta) {
  size = (delta > size ? 0 : size - delta);
}

#endif

