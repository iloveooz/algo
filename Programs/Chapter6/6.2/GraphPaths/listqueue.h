/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.2. ����� ���������� �����                         *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : listqueue.h                                      *
*  �������� : ������ ������� ��� ���������� ������� � ����     *
*             ������ ���������.                                *
***************************************************************/

#ifndef __LIST_QUEUE_H
#define __LIST_QUEUE_H

#include "queue.h"
#include "queuefactory.h"
#include "circularlist.h"

//==============================================================
// ����������� ������ �������� �� ������������� ������� � ���� 
// ������������ ������ ��������� �������.
//==============================================================

template<class T>
class ListQueue : public Queue<T> {
  CircularList<T> list;    // ������� ������

public :

  // ����������� "�� ���������" ������� ������ �������
  ListQueue() : list() {}

  // ����������� "�����������" ���������� �������� ������������ �������
  ListQueue(const ListQueue & src) { list = src.list; }

  // ����������� ����������
  virtual ~ListQueue() {}

  // ���������� ������ �������� ���������� � ����� ���������� ������
  void enqueue(const T & item) { 
    list.insertTail(item); 
  }

  // �������� �������� �� ������
  void dequeue();

  // �������� ������� ������� �������� � �������� ������� ������
  bool empty() const { return list.empty(); }

  // ������� ������� � ������ � ������ �������
  T & head();
  const T & head() const;
  T & tail();
  const T & tail() const;
};

// �������, �� ������������ "inline", "���������������" 
// �������������� ��������, ����������� ��� ��������� ������, 
// � ��������, ������������ ��� �������� � ��������.

template <class T>
void ListQueue<T>::dequeue() {
  try {
    list.removeHead();
  } catch (EmptyException) {
    throw QueueUnderflow();
  }
}

template <class T>
T & ListQueue<T>::head() {
  try {
    return list.head();
  } catch (EmptyException) {
    throw QueueUnderflow();
  }
}

template <class T>
const T & ListQueue<T>::head() const {
  try {
    return list.head();
  } catch (EmptyException) {
    throw QueueUnderflow();
  }
}

template <class T>
T & ListQueue<T>::tail() {
  try {
    return list.tail();
  } catch (EmptyException e) {
    throw QueueUnderflow();
  }
}

template <class T>
const T & ListQueue<T>::tail() const {
  try {
    return list.tail();
  } catch (EmptyException e) {
    throw QueueUnderflow();
  }
}

//==============================================================
// ������� ���������� �������� ���� ListQueue ���������
// ����������� ������� �������� QueueFactory
//==============================================================

template <class T>
class ListQueueFactory : public QueueFactory<T> {
public:
  // �������� ������������.
  Queue<T> *newQueue(int size = 100) { return new ListQueue<T>; }
};

#endif
