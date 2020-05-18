/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.4. ���������                                      *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : IntList.cpp                                   *
*  ��������    : ������ �����: ���������� ������� ������       *
***************************************************************/

#include "Actor.h"
#include "IntList.h"

// ���������� ������: ��� �������� ������ ������������
IntList::~IntList() {
  ListItem *current = NULL;  // �������, ���������� �����������
  ListItem *next = first;    // ��������� �������
  while (next) {
    current = next;     // ���������� ������ ��� ����������� ��������
    next = next->next;  // ��������� � ���������� ��������
    delete current;     // ���������� ������� �������
  }
}

  // ���������� �������� � ����� ������
void IntList::addLast(int item) {
  // �������� ������ �������� ������
  ListItem *newItem = new ListItem(item);
  if (!last) {
    // ����� ������� - ������ (� ������������) � ������
    first = newItem;
  } else {
    // ������������ ����� ������� � ����� ������
    last->next = newItem;
  }
  // ����� ������� - ��������� � ������
  last = newItem;
  count++;
}

// �������� ������
void IntList::traverse(Actor & a) {
  for (ListItem *current = first; current; current = current->next) {
    a.action(current->item);
  }
}

void IntList::traverseBackRec(Actor & a, ListItem * list) {
  if (list) {
    traverseBackRec(a, list->next);  // �������� ����������� ���������
    a.action(list->item);            // ��������� �������� list
  }
}
