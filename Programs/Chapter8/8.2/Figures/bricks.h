/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : bricks.h                                         *
*  Описание : Функциональное определение прямоугольника и      *
*             функций построения сложных фигур из них          *
***************************************************************/

#ifndef __BRICKS_H
#define __BRICKS_H

#include "figure.h"

//--------------------------------------------------------------
// Определение прямоугольника
//--------------------------------------------------------------
class Rectangle : public Figure {
  // Размеры сторон прямоугольника
  int xSize, ySize;

public :
  // Конструктор
  Rectangle(int xSize = 10, int ySize = 10)
    : xSize(xSize), ySize(ySize) {}

  // Функции доступа к размерам прямоугольника
  int getSizeX() const { return xSize; }
  int getSizeY() const { return ySize; }

  // Функция рисования прямоугольника на холсте
  void draw(Canvas & c, int x, int y) const {
    c.line(Point(x, y), Point(x+xSize-1, y));
    c.line(Point(x, y), Point(x, y+ySize-1));
    c.line(Point(x+xSize-1, y), Point(x+xSize-1, y+ySize-1));
    c.line(Point(x, y+ySize-1), Point(x+xSize-1, y+ySize-1));
  }
};

//--------------------------------------------------------------
// Функции построения сложных фигур из простых
//--------------------------------------------------------------
// Строка из экземляров одной и той же фигуры
extern FigurePtr row(const FigurePtr & fig, int number, int shiftX);

// Столбец из экземляров одной и той же фигуры
extern FigurePtr column(const FigurePtr & fig, int number, int shiftY);

// Пара строк со сдвигом для построения "кирпичной стенки"
extern FigurePtr twoRows(const FigurePtr & base, int number, int shiftX, int shiftY);

// Построение "кирпичной стенки"
extern FigurePtr wall(const FigurePtr & base, int numberX, int numberY, int shiftX, int shiftY);


#endif
