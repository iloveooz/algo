/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.4. ���������                                      *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : NegCounter.h                                  *
*  ��������    : �������� ������ ��� �������� ������:          *
*                ������� ����� ������������� ���������         *
***************************************************************/

#ifndef __NEG_COUNTER_H
#define __NEG_COUNTER_H

#include "Actor.h"

class NegativeCounter : public Actor {
  int counter;
public :
  NegativeCounter() : counter(0) {}
  int getCounter() { return counter; }
  void action(int & element) { counter += (element < 0); }
};

#endif
