/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.3. �������                                        *
*                                                              *
*  �����    : A.���������                                      *
*  ����     : heap.cpp                                         *
*  �������� : ������, �������������� �� �������� "��������" :  *
*             ����������� ������.                              *
***************************************************************/

#ifndef __HEAP
#define __HEAP

#include <exception>

using namespace std;

//*************************************************************
// ����� NoMoreSpace ������������ ��� �������������
// �������������� �������� ��� ������������� ������� ��������
//*************************************************************

class NoMoreSpace : public exception {
  // ���� ��� ���������, ��� ���������
  char * msg;

public:
  // ����������� ������ ������ ������� - ��� �����!
  NoMoreSpace() : msg("No more space") {}

  // ����� 'what' ������ ������� ������������� �������������� ��������.
  const char * what() const throw() { return msg; }
};

//*************************************************************
// ������ ������� Heap ��� ������������� "��������������" ������
//*************************************************************

template <class T>
class Heap {
  int count;     // ���������� ����� � ������
  T *items;      // ������, �������������� ���� ������
  int size;      // ������ ����� �������

public:

  // � ������������ �������� ������ �������; ��������� ���� ���
  Heap(int size) {
    count = 0;
    items = new T[Heap::size = size];
  }

  // �������� ������� ������ �������� � ��������
  void insert(const T & element);

  // �������� ���������� ���� ����������� ������� ������� 
  // � ��������� �������� �� �������
  T & operator [](int i) { return items[i]; }
  const T & operator [](int i) const { return items[i]; }

  // ����� print ������ ������� ��� �������� 
  // �������� � ����������� �������� �����
  void print();
};

// ���������� �������� ������� ��������
template <class T>
void Heap<T>::insert(const T & elem) {
    // ���������, ���� �� ��� ����� � �������
    if (count >= size) throw NoMoreSpace();
    // ���������� ����� �������
    int curIndex = count++;          // ������ ������� ������� � ��������
    int parentIndex;                 // ������ "��������"
    // ���� "��������" ��������
    while (curIndex > 0 && elem < items[parentIndex = (curIndex-1)/2]) {
      // �������� ������� ����
      items[curIndex] = items[parentIndex];
      // � ��������� � ��������, �������� ���� � ��������
      curIndex = parentIndex;
    }
    // �������� ����� ������� �� ���� �����
    items[curIndex] = elem;
}

// ����� ��������� ��������
template <class T>
void Heap<T>::print() {
  for (int i = 0; i < count; i++) cout << items[i] << ' ';
  cout << endl;
}

#endif
