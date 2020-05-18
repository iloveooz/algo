/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.2. ������ � ����������� ������ �� ��������� ����� *
*               � ������ ������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : bricks.cpp                                       *
*  �������� : ������� ���������� ������� ����� �� "��������"   *
***************************************************************/

#include "bricks.h"

// �������������� ��� �� �����:
//    fig - ������� ������;
//    number - ���������� ����� � ����;
//    shiftX - ���������� ����� �������� ������� ����� � ����
FigurePtr row(const FigurePtr & fig, int number, int shiftX) {
  if (number == 1) return fig;
  FigurePtr r = row(fig, number-1, shiftX);
  FigurePtr sr(new ShiftXFigure(r, shiftX)); 
  return FigurePtr(new JointFigure(fig, sr));
}

// ������������ ��� �� �����:
//    fig - ������� ������;
//    number - ���������� ����� � ����;
//    shiftY - ���������� ����� �������� ������� ����� � �������
FigurePtr column(const FigurePtr & fig, int number, int shiftY) {
  if (number == 1) return fig;
  FigurePtr c = column(fig, number-1, shiftY);
  FigurePtr sc(new ShiftYFigure(c, shiftY)); 
  return FigurePtr(new JointFigure(fig, sc));
}

// ���� ����� �� ������:
//    base - ������� ������;
//    number - ���������� ����� � ����;
//    shiftX - ���������� ����� �������� ������� ����� � ����
//    shiftY - ���������� ����� ������
FigurePtr twoRows(const FigurePtr & base, int number, int shiftX, int shiftY) {
  FigurePtr row1 = row(base, number, shiftX);
  FigurePtr row2(new ShiftYFigure(row1, shiftY));
  FigurePtr srow2(new ShiftXFigure(row2, shiftX/2));
  return FigurePtr(new JointFigure(row1, srow2));
}

// "��������� ������" �� ����������� ����� � ��� �� ������
//    base - ������� ������;
//    numberX - ���������� ����� � ����;
//    numberY - ���������� ����� (������);
//    shiftX - ���������� ����� �������� ������� ����� � ����
//    shiftY - ���������� ����� ������
FigurePtr wall(const FigurePtr & base, int numberX, int numberY, int shiftX, int shiftY) {
  FigurePtr rows = twoRows(base, numberX, shiftX, shiftY);
  return column(rows, numberY / 2, 2*shiftY);
}
