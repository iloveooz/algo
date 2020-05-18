/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.2. ������ � ����������� ������ �� ��������� ����� *
*               � ������ ������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : bricks.h                                         *
*  �������� : �������������� ����������� �������������� �      *
*             ������� ���������� ������� ����� �� ���          *
***************************************************************/

#ifndef __BRICKS_H
#define __BRICKS_H

#include "figure.h"

//--------------------------------------------------------------
// ����������� ��������������
//--------------------------------------------------------------
class Rectangle : public Figure {
  // ������� ������ ��������������
  int xSize, ySize;

public :
  // �����������
  Rectangle(int xSize = 10, int ySize = 10)
    : xSize(xSize), ySize(ySize) {}

  // ������� ������� � �������� ��������������
  int getSizeX() const { return xSize; }
  int getSizeY() const { return ySize; }

  // ������� ��������� �������������� �� ������
  void draw(Canvas & c, int x, int y) const {
    c.line(Point(x, y), Point(x+xSize-1, y));
    c.line(Point(x, y), Point(x, y+ySize-1));
    c.line(Point(x+xSize-1, y), Point(x+xSize-1, y+ySize-1));
    c.line(Point(x, y+ySize-1), Point(x+xSize-1, y+ySize-1));
  }
};

//--------------------------------------------------------------
// ������� ���������� ������� ����� �� �������
//--------------------------------------------------------------
// ������ �� ���������� ����� � ��� �� ������
extern FigurePtr row(const FigurePtr & fig, int number, int shiftX);

// ������� �� ���������� ����� � ��� �� ������
extern FigurePtr column(const FigurePtr & fig, int number, int shiftY);

// ���� ����� �� ������� ��� ���������� "��������� ������"
extern FigurePtr twoRows(const FigurePtr & base, int number, int shiftX, int shiftY);

// ���������� "��������� ������"
extern FigurePtr wall(const FigurePtr & base, int numberX, int numberY, int shiftX, int shiftY);


#endif
