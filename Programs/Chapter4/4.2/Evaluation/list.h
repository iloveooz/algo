/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.2. ���������� �� ��������                         *
*                                                              *
*  �����    : �. ���������                                     *
*  ����     : list.h                                           *
*  �������� : ����������� ������� ��� ���������� ������        *
*             ���������                                        *
***************************************************************/

#ifndef __LIST_H
#define __LIST_H

#include <exception>

class NoElementFound : public std::exception {
  char * reason;
public :
  NoElementFound(char * msg = "No list element found")
    : reason(msg) {}
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

protected:

  // ����������� ��������� ������
  virtual void destroy();
};

// ������� ������� � ������ ������
template <class T>
T & List<T>::head() {
  if (first == NULL) {
    throw NoElementFound("head: no list element found!");
  }
  return first->item; 
}

template <class T>
const T & List<T>::head() const {
  if (first == NULL) {
    throw NoElementFound("head: no list element found!");
  }
  return first->item; 
}

// ������� ������� � ����� ������
template <class T>
T & List<T>::tail() {
  if (first == NULL) {
    throw NoElementFound("tail: no list element found!");
  }
  return last->item; 
}

template <class T>
const T & List<T>::tail() const {
  if (first == NULL) {
    throw NoElementFound("tail: no list element found!");
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
    throw NoElementFound("remove: no list element found!");
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
