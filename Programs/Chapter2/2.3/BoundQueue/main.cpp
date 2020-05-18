/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.2. ����� � �������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : ������� ��� ������������ ���������� �������� ��� *
*             ����������� ��������                             *
***************************************************************/

#include <iostream>
#include "queue.h"
#include "queuefactory.h"

using namespace std;

// ���������� ������������ ����������� ������� ������
extern QueueFactory<int> * factory;

int main() {
  // ������� ������� �� ����� �����
  Queue<int> * q = factory->newQueue();

  // ��������� � ����� ������� ��������� ���������
  for (int i = 0; i < 10; i += 3) {
    q->enqueue(i);
    cout << "next item enqueued: " << q->tail() << endl;
  }

  // ������� �������� �� ������� � �������������
  // �� ���������� � �������� ��������
  cout << "Now in the queue:" << endl;
  for (int j = 0; j < 10; j += 3) {
    cout << q->head() << "; ";
    q->dequeue();
  }
  cout << endl;

  // ���������� �������
  delete q;

  return 0;
}