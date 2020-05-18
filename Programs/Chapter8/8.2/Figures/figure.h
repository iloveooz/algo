/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : figure.h                                         *
*  Описание : Определение основных классов для реализации      *
*             точек, холста и фигур                            *
***************************************************************/

#ifndef __FIGURE_H
#define __FIGURE_H

#include "smartptr.h"

//--------------------------------------------------------------
// Традиционное определение точки плоскости
//--------------------------------------------------------------
class Point {
  int x, y;     // Координаты точки

public :
  // Конструкторы
  Point(int x = 0, int y = 0) : x(x), y(y) {}
  Point(const Point & src) : x(src.x), y(src.y) {}

  // Функции доступа
  int getX() const { return x; }
  int getY() const { return y; }
};

//--------------------------------------------------------------
// Абстрактный холст для поточечного рисования
//--------------------------------------------------------------
class Canvas {
public :
  virtual ~Canvas() {}

  // Функции для определения размеров холста
  virtual int getSizeX() const = 0;
  virtual int getSizeY() const = 0;

  // Функции рисования точки:
  // один из двух вариантов должен быть переопределен
  virtual void putPoint(int x, int y) { putPoint(Point(x, y)); }
  virtual void putPoint(const Point & pt) { putPoint(pt.getX(), pt.getY()); }

  // Функции стирания точки:
  // один из двух вариантов должен быть переопределен
  virtual void clearPoint(int x, int y) { clearPoint(Point(x, y)); }
  virtual void clearPoint(const Point & pt) { clearPoint(pt.getX(), pt.getY()); }

  // Функция рисования прямой линии
  virtual void line(const Point & ptFrom, const Point & ptTo);
};

//--------------------------------------------------------------
// Абстрактная фигура для рисования на холсте
//--------------------------------------------------------------
class Figure {
public :
  virtual ~Figure() {}
  // Функция рисования на холсте 'c'.
  // Опорная точка для рисования имеет координаты x и y
  virtual void draw(Canvas & c, int x, int y) const = 0;
};

typedef SmartPtr<Figure> FigurePtr;

//--------------------------------------------------------------
// Определение класса для сдвига опорной точки фигуры вдоль оси X
//--------------------------------------------------------------
class ShiftXFigure : public Figure {
  FigurePtr baseFigure;   // Базовая фигура
  int shift;              // Величина сдвига в точках

public :
  // Конструктор
  ShiftXFigure(const FigurePtr & base, int shift) : baseFigure(base), shift(shift) {}

  // Функция рисования сдвигает опорную точку
  void draw(Canvas & c, int x, int y) const {
    baseFigure->draw(c, x + shift, y);
  }
};

//--------------------------------------------------------------
// Определение класса для сдвига опорной точки фигуры вдоль оси Y
//--------------------------------------------------------------
class ShiftYFigure : public Figure {
  FigurePtr baseFigure;   // Базовая фигура
  int shift;              // Величина сдвига в точках

public :
  // Конструктор
  ShiftYFigure(const FigurePtr & base, int shift) : baseFigure(base), shift(shift) {}

  // Функция рисования сдвигает опорную точку
  void draw(Canvas & c, int x, int y) const {
    baseFigure->draw(c, x, y + shift);
  }
};

//--------------------------------------------------------------
// Определение класса для объединения двух фигур
//--------------------------------------------------------------
class JointFigure : public Figure {
  FigurePtr baseFigure1,    // объединяемые фигуры
            baseFigure2;

public :
  // Конструктор
  JointFigure(const FigurePtr & base1, const FigurePtr & base2)
    : baseFigure1(base1), baseFigure2(base2) {}

  // Функция рисования последовательно рисует обе фигуры
  void draw(Canvas & c, int x, int y) const {
    baseFigure1->draw(c, x, y); baseFigure2->draw(c, x, y);
  }
};

// Заголовки функций, реализующих базовые операции над фигурами
FigurePtr shiftX(const FigurePtr & fig, int x);
FigurePtr shiftY(const FigurePtr & fig, int y);
FigurePtr join(const FigurePtr & fig1, const FigurePtr & fig2);

#endif
