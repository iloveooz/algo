/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.2. ������ � ����������� ������ �� ��������� ����� *
*               � ������ ������                                *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : position.h                                    *
*  ��������    : �������������� ������������� ������� �        *
*                �������������� �� ��������� ����� �������     *
***************************************************************/

#ifndef __POSITION_H
#define __POSITION_H

#include "smartptr.h"
#include <iostream>

using namespace std;

//-----------------------------------------------------------------
// ����������� �����, �������������� ������� � ��������������
// ������� �� ��������� ����� � �������������� ����.
//-----------------------------------------------------------------
class Position {
public :
  virtual ~Position() {}
  virtual bool permits(int i, int j) const = 0;
  virtual ostream & print(ostream & os) const = 0;
};

// ������� ������ ������� � ���������� �������� �����.
ostream & operator << (ostream & os, const Position & pos);

//-----------------------------------------------------------------
// ����� ��� ������������� ������ �������
//-----------------------------------------------------------------
class EmptyPosition : public Position {
public :
  bool permits(int i, int j) const { return true; }
  ostream & print(ostream & os) const { return os << endl; }
};

//-----------------------------------------------------------------
// ����� ��� ������������� �������, ��������� �� ������ ���
// ��������� ������� � ����������� ������ ����� � ������� (row, col)
//-----------------------------------------------------------------
class NewPosition : public Position {
  SmartPtr<Position> position;  // ������ �� "������" �������
  int col, row;                 // ���������� ������ �����
  int maxQueens;                // ������ �����

public :

  // ����������� �������� ������ ��� ���������� ����� �������
  NewPosition(const SmartPtr<Position> & position,
              int col, int row, int maxQueens)
    : position(position), col(col), row(row), maxQueens(maxQueens) {}

  // ������� �������� ������������ �����������
  bool permits(int i, int j) const {
    // ��������� (a) ������������� � ������� ��������;
    // (b) ������������ ������� ������� � �����;
    // (c) ������������ ����� �� ����� ��������� � �����
    return position->permits(i, j) && j != col && 
           abs(i - row) != abs(j - col);
  }

  // ������� ���������� ����� �������
  ostream & print(ostream & ps) const {
    position->print(ps);      // ������ ������ �������
    // �������� ����� �����������
    for (int i = 1; i < col; i++) { ps << ". "; }
    ps << "Q ";
    for (int i = col+1; i <= maxQueens; i++) { ps << ". "; }
    ps << endl;
  }
};

SmartPtr<Position> queen2(int n);

#endif
