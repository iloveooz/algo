/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.2. ������ � ����������� ������ �� ��������� ����� *
*               � ������ ������                                *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : position.cpp                                  *
*  ��������    : ������������� �������: ���������� ���������   *
*                ����������                                    *
***************************************************************/

#include "position.h"
#include <stdlib.h>

using namespace std;

ostream & operator << (ostream & os, const Position & pos) {
  return pos.print(os);
}

// ����������� �������, ���������� ����� ���������� ������� �� ������
// � ������� ���������� ������ ����� �� ��������� �����������.
// �������� row ������ ���������� ��� ������������ ������ (�����������
// ������������)
SmartPtr<Position> recQueen2(const SmartPtr<Position> & position,
                             int row, int maxQueens) {
  if (row == maxQueens) {
    // ��� ����������� ��� �����
    return position;
  } else {
    // �������� ��������� ������ ����� � ��� � ������� row
    for (int col = 1;  col <= maxQueens;  col++) {
      if (position->permits(row, col)) {
        // ����� ����� �� ������� �� ������ �� ��� �������������.
        // ��������� ����� ������� � ������ ����������� �����
        SmartPtr<Position> nextPos(
                         new NewPosition(position, col, row, maxQueens));
        SmartPtr<Position> newPos =
                         recQueen2(nextPos, row + 1, maxQueens);
        // ���� ������� ���������� ���������� ������� � ����� ������ 
        if (newPos) return newPos;
      }
    }
    // �� ������� ��������� ������ ����� �� �� ���� ���������
    return SmartPtr<Position>(NULL);
  }
}

SmartPtr<Position> queen2(int n) {
  // � ������ ������ ������� ����� � �� ������ ����� ��� �� �����������
  return recQueen2(SmartPtr<Position>(new EmptyPosition()), 0, n);
}
