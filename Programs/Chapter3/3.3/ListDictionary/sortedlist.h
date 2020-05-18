/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.3. �������, �������������� �������� � ���������   *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : sortedlist.h                                     *
*  �������� : ������������� ������ ��������                    *
***************************************************************/

#ifndef __SORTED_LIST_H
#define __SORTED_LIST_H

#include "iterator.h"
#include "actor.h"

//=============================================================
// ����� SortedList ������������ ������������� �� �����������
// ������ ������������ ��������. ��������� �������� ������������
// �������� ��������������� ��� ���������� ��������� ��������
//=============================================================

template <class Object>
class SortedList {

private :

  // ������� ������ ������� �� ������� � ������ �� ��������� �������
  struct ListElem {
    Object item;       // �������� �������� ������
    ListElem *next;    // ������ �� ��������� �������

    // ������� �����������
    ListElem(const Object & i, ListElem * n = NULL) : item(i), next(n) {}
  };

  // ������ ����������� ������� �� ������ �������...
  ListElem * first;
  // ...� ��������� ����� ���������
  int count;

  // ���������� ����� ForwardIterator ��������� ������� �������� ������
  class ForwardIterator : public Iterator<Object> {
    // ������ �� ������� �������:
    ListElem * current;

  public :
    // ����������� ������������� ��������� �� ������ �������� ������
    ForwardIterator(SortedList<Object> * sl) : current(sl->first) {}

    // �������� ������������, ����� ������� ��������� �������� ������ ������
    bool hasMoreElements() const { return current != NULL; }

    // �������� ������ �������� �������� � ����������� ��������� ��
    // ��������� ������� ������
    Iterator<Object> & operator ++() {
      if (current) current = current->next;
      return *this;
    }

    // ������ � ������������ �������� - ��� ������ 
    // �� �������� �������� ��������� � ������
    Object & operator *() {
      if (current == NULL) throw "No more elements";
      return current->item;
    }
  };

  friend class ForwardIterator;

public :

  // ������������
  SortedList() : first(NULL), count(0) {}
  SortedList(const SortedList & src) : first(NULL), count(0) {
    *this = src;
  }

  // ����������
  ~SortedList() { destroy(); }

  // ����� ��������� ������
  int getCount() { return count; }

  // ������� ��� ��������, ������ ���������
  bool remove(const Object & item);

  // �������� ������� � ������������� ������
  void insert(const Object & item);

  // ����� ������� ��������, ������� ���������
  Object * find(const Object & item);

  // ������� �������� ������
  Iterator<Object> * iterator() { return new ForwardIterator(this); }

  // ���������� �������� ������
  void iterator(Actor<Object> & actor);

private :
  void destroy();
};

// ���������� ������� ��� ������ �� �������

// ������� ��� ��������, ������ ���������
template <class Object>
bool SortedList<Object>::remove(const Object & item) {
  ListElem ** current = &first;
  while (*current && item > (*current)->item) {
    current = &(*current)->next;
  }
  bool deleted = false;
  while (*current && item == (*current)->item) {
    ListElem *toDelete = *current;
    *current = (*current)->next;
    delete toDelete;
    deleted = true;
    count--;
  }
  return deleted;
}

template <class Object>
void SortedList<Object>::insert(const Object & item) {
  ListElem ** current = &first;
  while (*current && item > (*current)->item) {
    current = &(*current)->next;
  }
  *current = new ListElem(item, *current);
  count++;
}

template <class Object>
Object * SortedList<Object>::find(const Object & item) {
  ListElem * current = first;
  while (current && item > current->item) {
    current = current->next;
  }
  if (current && item == current->item) {
    return &current->item;
  } else {
    return NULL;
  }
}

template <class Object>
void SortedList<Object>::iterator(Actor<Object> & actor) {
  ListElem * current = first;
  while (current) {
    actor.action(current->item);
    current = current->next;
  }
}

template <class Object>
void SortedList<Object>::destroy() {
  ListElem * current = first;
  ListElem * pred;
  while (current) {
    pred = current;
    current = current->next;
    delete pred;
  }
  count = 0;
}

#endif
