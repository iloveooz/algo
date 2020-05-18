/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.3. ����������� �������� ��������                  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : heap.h                                           *
*  �������� : ����������� ����������� �������� �� ���������    *
***************************************************************/

#ifndef __HEAP_H
#define __HEAP_H

#include <exception>

using namespace std;

//==============================================================
// ������ HeapOverflow � HeapUnderflow ���������� ���
// �������������� ��������, ������� ����� ���������� ���
// ���������� �������� ���������� �������� � ��������
// (HeapOverflow - ������������) � �������� ������������
// �������� (HeapUnderflow - ����������).
//==============================================================

class HeapOverflow : public exception {
  char * reason;
public :
  HeapOverflow(char * message = "Heap overflow!") : reason(message) {}
  const char * what() const throw() { return reason; }
};

class HeapUnderflow : public exception {
  char * reason;
public :
  HeapUnderflow(char * message = "Heap underflow!") : reason(message) {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// ������ ������� Heap ���������� ����������� ���������
// ��������: �������� ���������� ������ ��������, ������ �
// ������������ �������� � ��� �������� �� ��������.
// ��� �������� ��� ��������� ����������
// ��� ����������� (������) �������.
//==============================================================

template <class Element>
class Heap {
public :
  // �������� ������������ ��������:
  virtual void remove() throw(HeapUnderflow) = 0;

  // ������ � ������������ ��������:
  virtual Element & operator *() throw(HeapUnderflow) = 0;
  virtual const Element & operator *() const throw(HeapUnderflow) = 0;

  // ���������� ������ �������� � ��������:
  virtual Heap<Element> & operator += (const Element & newElem) throw(HeapOverflow) = 0;

  // �������� ������� ��������� � ��������:
  virtual bool empty() const = 0;
};

#endif
