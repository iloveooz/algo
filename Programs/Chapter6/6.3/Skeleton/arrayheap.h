/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.3. ����������� �������� ��������                  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : arrayhelp.h                                      *
*  �������� : ���������� �������� � ���� ������� ���������     *
***************************************************************/

#ifndef __ARRAY_HEAP_H
#define __ARRAY_HEAP_H

#include "heap.h"

//==============================================================
// ������ �������, ����������� �������� � ���� ������� ���������,
// � ������� ������� �������� � �������� i ����������� � �������
// � ��������� � ��������� 2*i+1 � 2*i+2.
//
// �������� ������� Element ������ ����� ����������� �� ���������,
// ����������� ����������� � ��� ���������� ������ ����
// ���������� ����������� �������� ���������
//==============================================================

template <class Element>
class ArrayHeap : public Heap<Element> {

  Element * array;    // ��������� �� ������ ���������
  int maxSize, size;  // ������ ������� � ������ ��������

public :
  // ������������:
  ArrayHeap(int maxSize) : maxSize(maxSize), size(0), array(new Element[maxSize]) {}
  ArrayHeap(const ArrayHeap & src);

  // �������� ������������ ��������
  void remove() throw(HeapUnderflow);

  // ������ � ������������ ��������
  Element & operator *() throw(HeapUnderflow);
  const Element & operator *() const throw(HeapUnderflow);

  // ���������� ������ ��������
  Heap<Element> & operator += (const Element & newElem) throw(HeapOverflow);

  // �������� ����� ���������
  bool empty() const { return size == 0; }
  int count() const { return size; }
};

//==============================================================
// ����������� �����������
//==============================================================
template <class Element>
ArrayHeap<Element>::ArrayHeap(const ArrayHeap & src)
    : maxSize(src.maxSize), size(src.size), array(new Element[maxSize]) {
  for (int i = 0; i < maxSize; i++) array[i] = src.array[i];
}

//==============================================================
// �������� ������������ ��������: �� ����� ������� ��������
// ������������ ������� �� ����� ������� � "��������������"
// ���� �� ��������
//==============================================================
template <class Element>
void ArrayHeap<Element>::remove() throw(HeapUnderflow) {
  // �������� �� ������������ ��������
  if (size == 0) throw HeapUnderflow();

  // ����� ��������� � �������� �����������
  if (--size == 0) return;

  // ���������� ��������� ������� ������� ��� "�������������"
  Element e = array[size];

  // ���� "�������������": current - ������ �������� ��������
  int current = 0;
  for (;;) {
    // ������������ �� �������� �������� �������� ��������:
    int elder = 2*(current + 1);

    // ���� �������� ���, �� "�������������" ������������:
    if (size < elder) break; else
    // ���� ������� ������ ����, �� ��� ������ �� ������� ������
    if (size == elder) {
      elder--;
    // ���� �������� ���, �� �������� ������ �������� � ������� ���������
    } else {
      if (array[elder-1] < array[elder]) elder--;
    }

    // ���������� ������� ������� � ����������� �� ��������
    // � ���������� ��� ����, ���� ����������
    if (e <= array[elder]) break;
    array[current] = array[elder];
    current = elder;
  }
  // "��������������" ������� ���������� �� ���� �����:
  array[current] = e;
}

//==============================================================
// ������ � ������������ �������� - ������� �������� �������
//==============================================================
template <class Element>
Element & ArrayHeap<Element>::operator *() throw(HeapUnderflow) {
  if (size == 0) throw HeapUnderflow();
  return *array; 
}

template <class Element>
const Element & ArrayHeap<Element>::operator *() const throw(HeapUnderflow) {
  if (size == 0) throw HeapUnderflow();
  return *array;
}

//==============================================================
// ���������� ������ �������� � ������: ����� ������� ����������
// � ����� ������� � ����� "��������������" ������,
// ���� �� ������ ���� �����
//==============================================================
template <class Element>
Heap<Element> & ArrayHeap<Element>::operator += (const Element & newElem) throw(HeapOverflow) {
  // �������� ���������� ����� � �������:
  if (size == maxSize) throw HeapOverflow();
  // ���� ������������� ���������� � ����� �������
  int current = size++;
  while (current > 0) {
    // ������ ������ �������� ��������
    int next = (current-1) / 2;
    if (array[next] > newElem) {
      // �������-������ ���������� ����
      array[current] = array[next];
      current = next;
    } else {
      // "�������������" ���������
      break;
    }
  }
  // ����� ������� �������� ���� �����
  array[current] = newElem;
  return *this;
}

#endif
