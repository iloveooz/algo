/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.3. ����������� �������� ��������                  *
*                                                              *
*  �����    : �. ���������                                     *
*  ����     : list.h                                           *
*  �������� : ����������� ������� ��� ���������� ������        *
*             ���������                                        *
***************************************************************/

#ifndef __LIST_H
#define __LIST_H

#include <stdlib.h>
#include <exception>
#include "iterator.h"

class MyException : public std::exception {
  char * reason;
public :
  MyException(char * msg = "") : reason(msg) {}
  const char * what() const throw() { return reason; }
};

//**************************************************************
// ������ ������� List.
//**************************************************************

template <class T>
class List {
/* ��������� ListItem - ��� �����, �������������� ���� ����� ������,
   ��������� �� ��������� ������ ���������� 'next'.
*/
  struct ListItem {
    T item;           // ������� ������
    ListItem *next;   // ��������� �� ��������� �������
    // ����������� 
    ListItem(const T & i, ListItem *n = NULL) { item = i; next = n; }
  };

  int count;             // ������� ����� ���������
  ListItem *first;       // ��������� �� ������ �������
  ListItem *last;        // ��������� �� ��������� �������

public:

  // ����������� "�� ���������" ������� ������ ������
  List() : count(0), first(NULL), last(NULL) {}

  // ����������� ����������� ������� ����� ������-���������
  List(const List<T> & src) { *this = src; }

  // ���������� ������
  virtual ~List() { destroy(); }

  // ������ � ������ ������
  T & head();
  const T & head() const;

  // ������ � ����� ������
  T & tail();
  const T & tail() const;

  // ���������� ��������� �� ������ � ����� �������
  List<T> & operator = (const List<T> & src);

  // ���������� �������� � ������ ������
  void addFirst(const T & item);

  // ���������� �������� � ����� ������
  void addLast(const T & item);

  // �������� �������� �� ������ ������
  void remove();

  // ���������� ��������� ������
  int getCount() const { return count; }

  // ������� �������� ��������� ������
  Iterator<T>* iterator() { return new ListIterator(this); }

protected:
  // ����������� ������ ��� �������� ��������� ��������� ������
  class ListIterator : public Iterator<T> {
    ListItem * next;

  public :

    ListIterator(List<T> * list) : next(list->first) {}

    bool hasMoreElements() const { return next != NULL; }

    Iterator<T> & operator ++() {
      if (next != NULL) next = next->next;
      return *this;
    }

    const T & operator *() const { return next->item; }
  };

  // ����������� ��������� ������
  virtual void destroy();
};

// ������� ������� � ������ ������
template <class T>
T & List<T>::head() {
  if (first == NULL) {
    throw MyException("head: no list element found!");
  }
  return first->item; 
}

template <class T>
const T & List<T>::head() const {
  if (first == NULL) {
    throw MyException("head: no list element found!");
  }
  return first->item; 
}

// ������� ������� � ����� ������
template <class T>
T & List<T>::tail() {
  if (first == NULL) {
    throw MyException("tail: no list element found!");
  }
  return last->item; 
}

template <class T>
const T & List<T>::tail() const {
  if (first == NULL) {
    throw MyException("tail: no list element found!");
  }
  return last->item; 
}

// �������� ������������ ��������� ������� ������ �
// ��������� ��� �������� ��������� � ����� ����� ������
template <class T>
List<T> & List<T>::operator = (const List<T> & src) {
  destroy();
  for (ListItem *cur = src.first; cur;  cur = cur->next) {
    // ������ ������� ����������� � ������� ������ addLast
    addLast(cur->item);
  }
  return *this;
}

// ���������� �������� � ������ ������
template <class T>
void List<T>::addFirst(const T & item) {
  // �������� ��������
  ListItem *newItem = new ListItem(item, first);
  if (!first) {
    // ����� ������� - ������������
    last = newItem;
  }
  first = newItem;
  count++;
}

// ���������� �������� � ����� ������
template <class T>
void List<T>::addLast(const T & item) {
  // �������� ��������
  ListItem *newItem = new ListItem(item);
  if (!last) {
    // ����� ������� - ������������
    first = newItem;
  } else {
    // ����� ������� - �������������� � ����� ������
    last->next = newItem;
  }
  last = newItem;
  count++;
}

// �������� ������� ��������
template <class T>
void List<T>::remove() {
  if (first == NULL) {
    throw MyException("remove: no list element found!");
  }
  ListItem *itemToDelete = first;
  first = first->next;    // ������ ������� ���������� ������
  count--;
  delete itemToDelete;
}

// ����������� ������: ��� �������� ���������� ���������
template <class T>
void List<T>::destroy() {
  ListItem *current = NULL;  // ������ �� �������, ���������� �����������
  ListItem *next = first;    // ������ �� ��������� �������
  while (next) {
    current = next;     // ���� ������� ����� ���������
    next = next->next;  // ������� � ���������� ��������
    delete current;     // ���������� ������� �������
  }
  count = 0;
  first = last = NULL;
}

#endif
