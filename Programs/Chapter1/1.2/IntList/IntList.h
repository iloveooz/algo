/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.2. ������                                         *
*                                                              *
*  �����    : A.���������                                      *
*  ����     : IntList.h                                        *
*  �������� : ������ �����: ����������� ������                 *
***************************************************************/

#ifndef __INT_LIST
#define __INT_LIST

#include <stdlib.h>

//**************************************************************
// ����� IntList
//**************************************************************

class IntList {
/* ����� ListItem ������������ ������� ������, ��������� �� 
   ��������� � ������� ���� next
*/
  struct ListItem {
    int item;         // �������� �������� ������
    ListItem *next;   // ��������� �� ��������� ������� ������

    // ����������� ��� �������� ������ ��������
    ListItem(int i, ListItem *n = NULL) { item = i; next = n; }
  };

  int count;             // ������� ����� ���������
  ListItem *first;       // ������ ������� ������
  ListItem *last;        // ��������� ������� ������

public :

  // ����������� "�� ���������" - �������� ������� ������
  IntList() { count = 0; first = last = NULL; }

  // ����������� "�����������" � �������� ����� ���������� ������
  IntList(const IntList & src);

  // ���������� ������
  ~IntList();

  // ������ � ������� �������� ������
  int head() const { return first->item; }
  int & head() { return first->item; }

  // ������ � ���������� �������� ������
  int tail() const { return last->item; }
  int & tail() { return last->item; }

  // �������� �������� � ����� ������
  void addLast(const IntList & src);

  // �������� ���� ������� � ������ ������
  void addFirst(int item);

  // �������� ���� ������� � ����� ������
  void addLast(int item);

  // ������� ������ ������� 
  int removeFirst();

  // �������� ��������� ��������
  bool remove(int n);

  // Searching and removing an element
  void insert(int n);

  // ���������� ��������� ������
  int getCount() { return count; }

  // Printing all the elements to the standard output stream
  void printAll();
};    // ����� ����������� ������ IntList

#endif
