/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.4. ���������                                      *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : Comparator.h                                  *
*  ��������    : �������� ������ ��� �������� ������:          *
*                ����� ��������� ��������                      *
***************************************************************/

#ifndef __COMPARATOR_H
#define __COMPARATOR_H

#include "Actor.h"

class Comparator : public Actor {
  int value;    // �������� ��� ���������
  bool found;   // ������� ����, ������� �� �������� value � ������
public :
  Comparator(int val) : value(val), found(false) {}
  bool hasFound() { return found; }
  void action(int & element) { if (value == element) found = true; }
};

#endif
