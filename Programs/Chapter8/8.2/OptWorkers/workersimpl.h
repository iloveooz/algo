/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.2. ������ � ����������� ������ �� ��������� ����� *
*               � ������ ������                                *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : workersimpl.h                                 *
*  ��������    : ����������� ������� ��� ���������� ���������  *
*                ������������ ������������� ������� ����       *
***************************************************************/

#ifndef __WORKERS_IMPL_H
#define __WORKERS_IMPL_H

#include "workers.h"

class EmptyAssignment : public Assignment {
public :
  EmptyAssignment(fProd output) : Assignment(output) {}
  // ���������� ��������� ������������������ �����������
  double prod() const { return 0; }
  // ��������, �������� �� ������� � �������� ������� i
  bool free(int i) const { return true; }
  // ����� ���������� � ����������� ������� � �������� �����
  void print(ostream & os) const {}
};

class NewAssignment : public Assignment {
  int wr;                           // ����� ������ ��������
  int wp;                           // ����� ��� �������� �����
  SmartPtr<Assignment> oldAssign;   // ������� �����������

public :
  // �����������
  NewAssignment(int wr, int wp, const SmartPtr<Assignment> & oldAssign)
    : Assignment(oldAssign->getOutput()), wr(wr), wp(wp), oldAssign(oldAssign) {}

  // � ������� ������������������ ����� ����������� ������������������ 
  // ����� �������� wr �� ������� ����� wp.
  double prod() const {
    return oldAssign->prod() + output(wp, wr);
  }

  // �������� ��� ��, ��� ��� �������� ������, ����� �������� wr.
  bool free(int i) const {
    return i != wr && oldAssign->free(i);
  }

  // � ������ ������� ����������� ����������� ���������� � ���,
  // ��� ������� ����� wp ������ ���������� ����� wr.
  void print(ostream & os) const {
    oldAssign->print(os);
    os << "Place number: " << wp << "; worker number: " << wr << endl;
  }
};

SmartPtr<Assignment> recAssignment(const SmartPtr<Assignment> assign, int busy, int maxWorkers);

#endif
