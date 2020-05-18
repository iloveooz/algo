/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : bricks.cpp                                       *
*  Описание : Функции построения сложных фигур из "кирпичей"   *
***************************************************************/

#include "bricks.h"

// Горизонтальный ряд из фигур:
//    fig - базовая фигура;
//    number - количество фигур в ряду;
//    shiftX - расстояние между опорными точками фигур в ряду
FigurePtr row(const FigurePtr & fig, int number, int shiftX) {
  if (number == 1) return fig;
  FigurePtr r = row(fig, number-1, shiftX);
  FigurePtr sr(new ShiftXFigure(r, shiftX)); 
  return FigurePtr(new JointFigure(fig, sr));
}

// Вертикальный ряд из фигур:
//    fig - базовая фигура;
//    number - количество фигур в ряду;
//    shiftY - расстояние между опорными точками фигур в столбце
FigurePtr column(const FigurePtr & fig, int number, int shiftY) {
  if (number == 1) return fig;
  FigurePtr c = column(fig, number-1, shiftY);
  FigurePtr sc(new ShiftYFigure(c, shiftY)); 
  return FigurePtr(new JointFigure(fig, sc));
}

// Пара рядов со сдигом:
//    base - базовая фигура;
//    number - количество фигур в ряду;
//    shiftX - расстояние между опорными точками фигур в ряду
//    shiftY - расстояние между рядами
FigurePtr twoRows(const FigurePtr & base, int number, int shiftX, int shiftY) {
  FigurePtr row1 = row(base, number, shiftX);
  FigurePtr row2(new ShiftYFigure(row1, shiftY));
  FigurePtr srow2(new ShiftXFigure(row2, shiftX/2));
  return FigurePtr(new JointFigure(row1, srow2));
}

// "Кирпичная стенка" из экземпляров одной и той же фигуры
//    base - базовая фигура;
//    numberX - количество фигур в ряду;
//    numberY - количество рядов (четное);
//    shiftX - расстояние между опорными точками фигур в ряду
//    shiftY - расстояние между рядами
FigurePtr wall(const FigurePtr & base, int numberX, int numberY, int shiftX, int shiftY) {
  FigurePtr rows = twoRows(base, numberX, shiftX, shiftY);
  return column(rows, numberY / 2, 2*shiftY);
}
