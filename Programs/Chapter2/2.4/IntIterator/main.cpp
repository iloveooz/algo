/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.4. ���������                                      *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : main.cpp                                      *
*  ��������    : ���������� ��������� ������ �����:            *
*                ����������� �������                           *
***************************************************************/

#include <iostream>
#include "IntList.h"
#include "Summator.h"
#include "Comparator.h"
#include "NegCounter.h"

using namespace std;

// ������� ������������ ��������� � ������
int sum(IntList & l) {
  Summator summator;
  l.traverse(summator);
  return summator.getSum();
}

// ������� ������������ ��������� � ������ � �������� �������
int sumBack(IntList & l) {
  Summator summator;
  l.traverseBack(summator);
  return summator.getSum();
}

// ������� �������� ������� ��������� �������� � ������
bool hasElement(IntList & l, int value) {
  Comparator comp(value);
  l.traverse(comp);
  return comp.hasFound();
}

// ������� �������� ���������� ������������� ���������
int negatives(IntList & l) {
  NegativeCounter counter;
  l.traverse(counter);
  return counter.getCounter();
}

int main() {
  IntList list;         // ������ ����� ������ ������
  // ��������� � ������ ��������
  list.addLast(5);
  list.addLast(2);
  list.addLast(15);
  list.addLast(-3);
  list.addLast(8);

  // 1. ��������� ������������ ��������� � ������� ����������� ���������
  cout << "Sum of the list elements: " << sum(list) << endl;
  //    �� �� ����� � �������� �������
  cout << "Sum of the list elements taken in reverse: " << sumBack(list) << endl;

  // 2. ��������� ����� �������� � ������
  cout << "Searching element 2: " 
       << (hasElement(list, 2) ? "found" : "not found")
       << endl;
  cout << "Searching element 3: " 
       << (hasElement(list, 3) ? "found" : "not found")
       << endl;

  // 3. ��������� ������� �������� ���������� ������������� ���������
  cout << "Number of negative elements: " << negatives(list) << endl;

  return 0;
}
