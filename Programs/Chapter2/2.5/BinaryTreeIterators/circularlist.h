/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.5. ����������� ��������                           *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : circularlist.h                                   *
*  �������� : �������� � ���������� ���������� ������          *
***************************************************************/

#ifndef __CIRCULAR_LIST_H
#define __CIRCULAR_LIST_H

#include <stdlib.h>
#include <exception>

//==============================================================
// �����, ������������ �������������� �������� EmptyException,
// ������� ����� ��������� ��� �������� ������� � ��������� ������� ������.
//==============================================================

class EmptyException : public std::exception {
  char * reason;
public:
  EmptyException() : reason("Accessing to element of an empty list") {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// ������ ������� ��� ����������� ���������� ������.
// ������������ ������� �� ������� �������� ������� ������� � ���,
// ��� ��������� ������� ������ �������� ��������� �� ������ �������.
//==============================================================

template <class T>
class CircularList {

  //============================================================
  // ������� ������ �������� ���������� �������� � ��������� �� 
  // ��������� ������� (��������� ������� �������� ��������� �� ������).
  //============================================================
  struct ListItem {
    T item;             // ������� ������
    ListItem *next;     // ��������� �������

    ListItem(const T & item, ListItem *next = NULL) {
      ListItem::item = item;
      ListItem::next = next;
    }
  };

  // ������ ����������� ���������� �� ��������� �������,
  // ���������� ��������� �� ������ ������� ������.
  // ���� ��������� �������� NULL, ���� ������ ����.
  ListItem *last;

public :

  // ����������� "�� ���������" ������� ������ ������.
  CircularList() { last = NULL; }

  // ����������� ����������� ���������� � ������� ��������� ������������.
  CircularList(const CircularList<T> & src) { *this = src; }

  // ���������� ������ ����������� ������, ������� ���������� ������.
  virtual ~CircularList() { destroy(); }

  // ����� �������� ����� ��������� � ������ ��� � ����� ������.
  void insertHead(const T & item);
  void insertTail(const T & item);

  // ������ ������� ����� �������.
  void removeHead();

  // ������� 'empty' ���������, �������� �� ������ ���� ���� �������. 
  bool empty() { return last == NULL; }

  // ������� "�������" ��������� ������ ��� ������ �/��� ������
  // � ������� � ���������� ��������� ������.
  T & head();
  const T & head() const;
  T & tail();
  const T & tail() const;

  // �������� ������������
  CircularList<T> & operator = (const CircularList<T> & src);

  // ������� destroy ����������� ������, ������� ���������� ������
  // � ������ ������ ������.
  void destroy();
};

// ������� ������ �������� � ������ ������
template <class T>
void CircularList<T>::insertHead(const T & item) {
  if (last == NULL) {
    // ����� ������� ����� ������������ ������ � ���������
    last = new ListItem(item);
    last->next = last;
  } else {
    // ����� ������� ����������� �� ���������
    last->next = new ListItem(item, last->next);
  }
}

// ������� ������ �������� � ����� ������
template <class T>
void CircularList<T>::insertTail(const T & item) {
  // ������� ��������� ������� � ������ ������.
  insertHead(item);
  // ����� ������ ������� ���� ��������� � ��������� ������
  // ���������� "����������" ������ �� ���� ���
  last = last->next;
}

// �������� �������� �� ������ ������. ������, ������� ���������, �������������.
template <class T>
void CircularList<T>::removeHead() {
  if (last == NULL) throw EmptyException();
  if (last->next == last) {
    // ��������� ������������ �������
    delete last;
    last = NULL;
  } else {
    ListItem * itemToDelete = last->next;
    last->next = last->next->next;
    delete itemToDelete;
  }
}

// ������� ������� � ������ ������.
template <class T>
T & CircularList<T>::head() {
  if (last == NULL) throw EmptyException();
  return last->next->item;
}

template <class T>
const T & CircularList<T>::head() const {
  if (last == NULL) throw EmptyException();
  return last->next->item;
}

// ������� ������� � ����� ������.
template <class T>
T & CircularList<T>::tail() {
  if (last == NULL) throw EmptyException();
  return last->item;
}

template <class T>
const T & CircularList<T>::tail() const {
  if (last == NULL) throw EmptyException();
  return last->item;
}

// �������� ������������
template <class T>
CircularList<T> & CircularList<T>::operator = (const CircularList<T> & src) {
  // ���� �����-�� �������� ��� ���� � ������, �� ��� ������������.
  destroy();
  // ������������ ����������� � ���������� ������ ������.
  if (!src.empty()) {
    ListItem * current = src.last->next; // First element
    do {
      insertTail(current->item);
      if (current == src.last) break;    // it was the last element!
      current = current->next;
    } while (true);
  }
}

// ������� destroy ����������� ������, ������� ���������� ������
// � ������� ���������������� ������� ������� removeHead.
template <class T>
void CircularList<T>::destroy() {
  while (last) removeHead();
}

#endif
