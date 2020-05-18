/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.1. ����������� ������� ������������� ������       *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : digitsort.h                                      *
*  �������� : ������� ���������� ��������� ������� �������     *
*             �������� ����������                              *
***************************************************************/

#ifndef __DIGIT_SORT_H
#define __DIGIT_SORT_H

#include <alloc.h>

template <class Key>
struct Elem;

//==============================================================
// ����� ListBuffer ������������ �������� ��� ������ ��� 
// ����������� � ��� ������� ������ (��� �������� ����������).
//==============================================================
template <class Key>
class ListBuffer {
  Elem<Key> * buffer;   // ��������� �� �����
  int size;             // ������ ������
  int freePtr;          // ��������� ������� ���������� ��������

  static ListBuffer<Key> * singleton;

  // �����������:
  ListBuffer(int n) {
    buffer = (Elem<Key>*)calloc(size = n, sizeof(Elem<Key>));
    clear();
  }

public :

  static ListBuffer<Key> * getInstance() {
    return singleton;
  }

  static void setNewBuffer(int n) {
    singleton = new ListBuffer<Key>(n);
  }

  // ����������:
  ~ListBuffer() { free(buffer); }

  // ������� ������.
  void clear() {
    freePtr = 0;
  }

  // �������� ��������� �������� ��������� ����� ������
  Elem<Key> * get() {
    return & buffer[freePtr++];
  }
};

template <class Key>
ListBuffer<Key> * ListBuffer<Key>::singleton = NULL;

//==============================================================
// ����� Elem ������������ ������� ������ ������,
// ������������ ��� ���������� �������� ����������.
//==============================================================
template <class Key>
struct Elem {
  Key value;         // ��� �������
  Elem<Key> * next;  // ��������� ���������� �������� � ���� ������
  
  // ������������:
  Elem() { next = NULL; }   // �� ��������� ��������� ������� �����������
  Elem(const Elem<Key> & src) : value(src.value), next(src.next) {}
  Elem(const Key & val, Elem<Key> * n = NULL) : value(val), next(n) {}

  // �������� ������������:
  Elem<Key> & operator = (const Elem<Key> & src) {
    value = src.value; next = src.next;
    return *this;
  }

  // ������ ������
  void * operator new(size_t sz) {
    return ListBuffer<Key>::getInstance()->get();
  }
};

//==============================================================
// ����� KeyList ������������ ������ ������, ���������� �
// �������� ���� ������.
//==============================================================
template <class Key>
class KeyList {
  Elem<Key> * first;    // ��������� �� ������ ������� ������
  Elem<Key> * last;     // ��������� �� �������� ������� ������

public :

  // �����������
  KeyList() : first(NULL), last(NULL) {}

  // �������� ���������� ������ �������� � ����� ������
  void addKey(const Key & key) {
    // ����������� ��������� ������� � ���� ������
    Elem<Key> * newElem = new Elem<Key>(key);
    // ������������ ����� ������� � ��� ���������� ������
    if (first == NULL) {
      first = newElem;
    } else {
      last->next = newElem;
    }
    last = newElem;
  }

  // �������� toArray ��������� ��� �������� ������ �� ��������
  // ������� array, ������� � �������� � �������� from.
  // � �������� ���������� ������� ������ ������ ������� ��������
  // �������, ���������� �� ������������ ����������
  int toArray(Key * array, int from) {
    // ���������� �������� ��������� � ������� ��������� ptr.
    Elem<Key> * ptr = first;
    while (ptr != NULL) {
      array[from++] = ptr->value;
      ptr = ptr->next;
    }
    return from;
  }

  // ������� ������� ������ ������ "���������" ���������
  // �� ������ � ��������� �������� ������.
  void clear() { first = last = NULL; }
};

//-------------------------------------------------------------
// ������ digitSort ������ ������� ���������� ���������
// ������� ������� �������� ����������.
//   - Key - �����, �������� ��� ��������� �������;
//   - array - ��������������� ������;
//   - low, high - �������, �������� �������� ����������;
//-------------------------------------------------------------

template <class Key>
void digitSort(Key * array, int low, int high) {
  // ��������������, ��� � ������ ������ low <= high
  // � ���������� ���������� ���������� ������������� ��������
  // ������� � ��������� �� low �� high
  int n = high - low + 1;               // ����� �������
  int listNumber = array[low].power();  // ���������� ������� ������
  int passes = array[low].length();     // ���������� �������� �� �������

  ListBuffer<Key>::setNewBuffer(n);

  // ���������� ������ ������� ������:
  KeyList<Key> * lists = new KeyList<Key>[listNumber];

  // ���� �� �������� �� ������� (digit - ����� "�����"):
  for (int digit = passes-1; digit >= 0; digit--) {
    // ��������� ������ �� ������� � ��������������� ������
    for (int i = low; i <= high; i++) {
      lists[array[i][digit]].addKey(array[i]);
    }
    // �������� ������� ������� � ������ � �������� �������
    int start = low;
    for (int i = 0; i < listNumber; i++) {
      start = lists[i].toArray(array, start);
      lists[i].clear();
    }
    // ������� ������
    ListBuffer<Key>::getInstance()->clear();
  }
}

#endif
