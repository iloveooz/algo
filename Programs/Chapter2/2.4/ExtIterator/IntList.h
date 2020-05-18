/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.4. ���������                                      *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : IntList.h                                     *
*  ��������    : ������ �����: �������� ������                 *
***************************************************************/

#ifndef __INT_LIST_H
#define __INT_LIST_H

#include <stdlib.h>
#include <exception>
#include "Iterator.h"

using namespace std;

//**************************************************************
// �������� ������ IntList
//**************************************************************

class IntList {
/* ��������� ListItem ������������ ������� ������, 
   ��������� �� ��������� ��������� � ������� ��������� 'next'.
*/
  struct ListItem {
    int item;         // ������� ������
    ListItem *next;   // ��������� �� ��������� �������

    // ����������� �������� ListItem
    ListItem(int i, ListItem *n = NULL) { item = i; next = n; }
  };

  int count;             // ������� ����� ���������
  ListItem *first;       // ��������� �� ������ �������
  ListItem *last;        // ��������� �� ��������� �������

public:

  // ����������� "���������" ������� ������ ������
  IntList() { count = 0; first = last = 0; }

  // ���������� ������
  ~IntList();

  // Number of elements - a simple inline function
  int getCount() { return count; }

  // ���������� �������� � ����� ������
  void addLast(int item);

  // ����� ��� �������������� ��������, ��������� � ����������� �������� � ������
  class NoListElement : public exception {
    char * reason;
  public :
    NoListElement(char * msg = "") : reason(msg) {}
    const char * what() const throw() { return reason; }
  };

  // �����, �������������� ������� �������� ������
  class MyIterator : public Iterator<int> {
    ListItem * curPos;   // ������� ������� � ������
    ListItem ** pred;    // ������ �� �����, ��� �������� 
                         // ��������� �� ���� �������

  public :
    // �����������
    MyIterator(IntList & list) { curPos = *(pred = &list.first); }

    // ���������� ������� ����������
    bool hasMoreElements() const { return curPos != NULL; }

    void nextElement() { if (curPos) curPos = *(pred = &curPos->next); }

    const int & getCurrent() const { return curPos->item; }

    int & getCurrent() { return curPos->item; }

    void remove() {
      if (!curPos)
        throw NoListElement("remove: no current element");
      *pred = curPos->next;
      delete curPos;
      curPos = *pred;
    }

    void insertBefore(int newValue) {
      ListItem * newItem = new ListItem(newValue, curPos);
      curPos = *pred = newItem;
    }

    void insertAfter(int newValue) {
      if (!curPos)
        throw NoListElement("insertAfter: no current element");
      ListItem * newItem = new ListItem(newValue, curPos->next);
      curPos = *(pred = &newItem->next);
    }
  };

  friend class MyIterator;

  // ����� iterator() ��������� � ������ ������� �������� ��� ����� ������
  MyIterator * iterator() { return new MyIterator(*this); }
};

#endif
