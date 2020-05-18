/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.2. ������                                         *
*                                                              *
*  �����    : A.���������                                      *
*  ����     : IntList.cpp                                      *
*  �������� : ������ �����: ���������� ������� ������          *
***************************************************************/

#include <iostream>
#include "IntList.h"

using namespace std;

// ���������� ������������ �����������
IntList::IntList(const IntList & src) {
  count = 0;
  first = last = NULL;
  addLast(src);   // ��������� ������ src � ����� ������ this
}

// ���������� �����������
IntList::~IntList() {
  ListItem *current = NULL; // ��������� �� �������, ���������� ��������
  ListItem *next = first;   // ��������� �� ��������� �������
  while (next) {            // ���� ���� ��� �������� � ������
    current = next;
    next = next->next;      // ������� � ���������� ��������
    delete current;         // ������������ ������
  }
}

// ���������� ��������� ��������� ������ � ����� �������������
void IntList::addLast(const IntList & src) {
  for (ListItem *cur = src.first; cur;  cur = cur->next)
    addLast(cur->item);  // ���������� ������ �������� � ��. ����
}

// ���������� ������ �������� � ������ ������
void IntList::addFirst(int item) {
  // ������� ����� ������� ������
  ListItem *newItem = new ListItem(item, first);
  if (!first) {
    // ������ ��� ���� � ����� ������� ����� � ������, � ���������
    last = newItem;
  }
  first = newItem;
  count++;    // ����� ��������� ������ �����������.
}

// ���������� ������ �������� � ����� ������
void IntList::addLast(int item) {
  // ������� ����� ������� ������
  ListItem *newItem = new ListItem(item);
  if (!last) {
    // ������ ��� ���� � ����� ������� ����� � ������, � ���������
    first = newItem;
  } else {
    // ����� ������� �������������� � ���������� �������� ������
    last->next = newItem;
  }
  last = newItem;
  count++;    // ����� ��������� ������ �����������.
}

// �������� ������� �������� �� ������
int IntList::removeFirst() {
  int res = first->item;  // ���������� ������� ��������
  first = first->next;    // ������ ������� ���������� ������
  count--;                // ����� ��������� ������ �����������
  return res;   // ��������� ������� ������������ � �������� ����������
}

// �������� ��������� ��������
bool IntList::remove(int n) {
  ListItem *pred = 0,         // ��������� �� ���������� �������
           *current = first;  // ��������� �� ������� �������
  while (current) {
    if (current->item == n) {
      if (pred) {            // ������������ ������ �� ��������� �������
        pred->next = current->next;
      }
      if (current == last) { // ��������� ��������� �������
        last = pred;         // ������������ ������ �� ��������� �������
      }
      delete current;        // ����������� ������
      count--;               // ��������� ���������� ���������
      return true;
    } else {                 // ��������� � ���������� ��������
      pred = current;
      current = current->next;
    }
  }
  // ��������� ������� �� ������
  return false;
}

// ������� ������ �������� � ������������� ������
void IntList::insert(int n) {
  ListItem *pred = NULL,    // �������, �������������� ������������
           *succ = first;   // �������, ��������� �� �����������
  while (succ != NULL && succ->item < n) { // ����� ����� �������
    pred = succ; 
    succ = succ->next;
  }
  // ���������� ����� �������:
  ListItem *newItem = new ListItem(n, succ);
  if (succ == NULL) {      // ����������� ������� � ���������
    last = newItem;
  }
  // ��������� ����� ������� � ������
  if (pred == NULL) {
    first = newItem; 
  } else {
    pred->next = newItem;
  }
  count++;
}

// ����� ��������� ������ � ��������� ���� � ����������� �������� �����
void IntList::printAll() {
  ListItem *current = first;  // ��������� �� �������
  while (current) {
    cout << current->item << ' ';
    current = current->next;  // ������� � ���������� ��������
  }
  cout << endl;
}
