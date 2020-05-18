/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.1. ������ � ����� � ������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : queue.h                                          *
*  �������� : ������ ������� ��� ����������� �����������       *
*             �������                                          *
***************************************************************/

#ifndef __QUEUE_H
#define __QUEUE_H

#include <exception>

using namespace std;

//==============================================================
// ������ QueueOverflow � QueueUnderflow ������������ ���
// �������� ��������� �������������� ��������, �����������
// ��� ������ � ��������.
//==============================================================

class QueueOverflow : public exception {
  char * reason;
public:
  QueueOverflow() : reason("Queue Overflow") {}
  const char * what() const throw() { return reason; }
};

class QueueUnderflow : public exception {
  char * reason;
public:
  QueueUnderflow() : reason("Queue Underflow") {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// ������ ������� Queue ������������ ������� ����������� �������.
//==============================================================

template <class T>
class Queue {
public:
  // ����������� ����������, ������ ��� ��� ��������������� � �������-��������
  virtual ~Queue() {}

  // ����������� �������� � ��������.

  // ���������� ������ �������� � �������.
  virtual void enqueue(const T & e) = 0;

  // �������� ��������� ��������. 
  // �������������� �������� QueueUnderflow ����� ����������,
  // ���� � ������� ��� ���������.
  virtual void dequeue() = 0;

  // �������� ������� �������
  virtual bool empty() const = 0;

  // ������� ������� �� ������ �/��� ������ ��������� �/��� ���������� ���������.
  virtual T & head() = 0;
  virtual const T & head() const = 0;
  virtual T & tail() = 0;
  virtual const T & tail() const = 0;
};

#endif
