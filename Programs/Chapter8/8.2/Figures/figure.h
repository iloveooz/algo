/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.2. ������ � ����������� ������ �� ��������� ����� *
*               � ������ ������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : figure.h                                         *
*  �������� : ����������� �������� ������� ��� ����������      *
*             �����, ������ � �����                            *
***************************************************************/

#ifndef __FIGURE_H
#define __FIGURE_H

#include "smartptr.h"

//--------------------------------------------------------------
// ������������ ����������� ����� ���������
//--------------------------------------------------------------
class Point {
  int x, y;     // ���������� �����

public :
  // ������������
  Point(int x = 0, int y = 0) : x(x), y(y) {}
  Point(const Point & src) : x(src.x), y(src.y) {}

  // ������� �������
  int getX() const { return x; }
  int getY() const { return y; }
};

//--------------------------------------------------------------
// ����������� ����� ��� ����������� ���������
//--------------------------------------------------------------
class Canvas {
public :
  virtual ~Canvas() {}

  // ������� ��� ����������� �������� ������
  virtual int getSizeX() const = 0;
  virtual int getSizeY() const = 0;

  // ������� ��������� �����:
  // ���� �� ���� ��������� ������ ���� �������������
  virtual void putPoint(int x, int y) { putPoint(Point(x, y)); }
  virtual void putPoint(const Point & pt) { putPoint(pt.getX(), pt.getY()); }

  // ������� �������� �����:
  // ���� �� ���� ��������� ������ ���� �������������
  virtual void clearPoint(int x, int y) { clearPoint(Point(x, y)); }
  virtual void clearPoint(const Point & pt) { clearPoint(pt.getX(), pt.getY()); }

  // ������� ��������� ������ �����
  virtual void line(const Point & ptFrom, const Point & ptTo);
};

//--------------------------------------------------------------
// ����������� ������ ��� ��������� �� ������
//--------------------------------------------------------------
class Figure {
public :
  virtual ~Figure() {}
  // ������� ��������� �� ������ 'c'.
  // ������� ����� ��� ��������� ����� ���������� x � y
  virtual void draw(Canvas & c, int x, int y) const = 0;
};

typedef SmartPtr<Figure> FigurePtr;

//--------------------------------------------------------------
// ����������� ������ ��� ������ ������� ����� ������ ����� ��� X
//--------------------------------------------------------------
class ShiftXFigure : public Figure {
  FigurePtr baseFigure;   // ������� ������
  int shift;              // �������� ������ � ������

public :
  // �����������
  ShiftXFigure(const FigurePtr & base, int shift) : baseFigure(base), shift(shift) {}

  // ������� ��������� �������� ������� �����
  void draw(Canvas & c, int x, int y) const {
    baseFigure->draw(c, x + shift, y);
  }
};

//--------------------------------------------------------------
// ����������� ������ ��� ������ ������� ����� ������ ����� ��� Y
//--------------------------------------------------------------
class ShiftYFigure : public Figure {
  FigurePtr baseFigure;   // ������� ������
  int shift;              // �������� ������ � ������

public :
  // �����������
  ShiftYFigure(const FigurePtr & base, int shift) : baseFigure(base), shift(shift) {}

  // ������� ��������� �������� ������� �����
  void draw(Canvas & c, int x, int y) const {
    baseFigure->draw(c, x, y + shift);
  }
};

//--------------------------------------------------------------
// ����������� ������ ��� ����������� ���� �����
//--------------------------------------------------------------
class JointFigure : public Figure {
  FigurePtr baseFigure1,    // ������������ ������
            baseFigure2;

public :
  // �����������
  JointFigure(const FigurePtr & base1, const FigurePtr & base2)
    : baseFigure1(base1), baseFigure2(base2) {}

  // ������� ��������� ��������������� ������ ��� ������
  void draw(Canvas & c, int x, int y) const {
    baseFigure1->draw(c, x, y); baseFigure2->draw(c, x, y);
  }
};

// ��������� �������, ����������� ������� �������� ��� ��������
FigurePtr shiftX(const FigurePtr & fig, int x);
FigurePtr shiftY(const FigurePtr & fig, int y);
FigurePtr join(const FigurePtr & fig1, const FigurePtr & fig2);

#endif
