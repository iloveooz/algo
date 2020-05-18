/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.3. ����� � �������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : stack.h                                          *
*  �������� : ����������� ������������ �����                   *
***************************************************************/

#ifndef __STACK_H
#define __STACK_H

#include <exception>

using namespace std;

//==============================================================
// ������ StackOverflow � StackUnderflow ������������ ���
// �������������� ��������, ������� ���������� ��� ������ �� �������.
//==============================================================

class StackOverflow : public exception {
  char * reason;
public :
  StackOverflow() : reason("Stack Overflow") {}
  const char * what() const throw() { return reason; }
};

class StackUnderflow : public exception {
  char * reason;
public:
  StackUnderflow() : reason("Stack Underflow") {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// ������ ������� Stack ������������ ������� ������������ �����
//==============================================================

template <class T>
class Stack {
public:
  // ����������� ���������� ��� ��������������� ��� � �������-�����������
  virtual ~Stack() {}

  // �������� ��� ����������� ������.

  // ���������� ������ �������� �� ������� �����.
  virtual void push(const T & e) = 0;

  // �������� �������� � ������� �����. 
  // �������� StackUnderflow ����� ����������, ���� ������ �������� ���
  virtual void pop() = 0;

  // �������� ������� �����
  virtual bool empty() = 0;

  // ������� ������� � �������� �������� �����.
  virtual T & top() = 0;
  virtual const T & top() const = 0;
};

#endif
