/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : position.h                                    *
*  Описание    : Функциональное представление позиции с        *
*                расставленными на шахматной доске ферзями     *
***************************************************************/

#ifndef __POSITION_H
#define __POSITION_H

#include "smartptr.h"
#include <iostream>

using namespace std;

//-----------------------------------------------------------------
// Абстрактный класс, представляющий позицию с расставленными
// ферзями на шахматной доске в функциональном виде.
//-----------------------------------------------------------------
class Position {
public :
  virtual ~Position() {}
  virtual bool permits(int i, int j) const = 0;
  virtual ostream & print(ostream & os) const = 0;
};

// Функция вывода позиции в символьный выходной поток.
ostream & operator << (ostream & os, const Position & pos);

//-----------------------------------------------------------------
// Класс для представления пустой позиции
//-----------------------------------------------------------------
class EmptyPosition : public Position {
public :
  bool permits(int i, int j) const { return true; }
  ostream & print(ostream & os) const { return os << endl; }
};

//-----------------------------------------------------------------
// Класс для представления позиции, созданной на основе уже
// имеющейся позиции с добавлением нового ферзя в позицию (row, col)
//-----------------------------------------------------------------
class NewPosition : public Position {
  SmartPtr<Position> position;  // Ссылка на "старую" позицию
  int col, row;                 // Координаты нового ферзя
  int maxQueens;                // Размер доски

public :

  // Конструктор получает данные для построения новой позиции
  NewPosition(const SmartPtr<Position> & position,
              int col, int row, int maxQueens)
    : position(position), col(col), row(row), maxQueens(maxQueens) {}

  // Функция проверки правильности расстановки
  bool permits(int i, int j) const {
    // Проверяем (a) совместимость с прошлой позицией;
    // (b) несовпадение номеров колонок с новой;
    // (c) ненахождение ферзя на одной диагонали с новым
    return position->permits(i, j) && j != col && 
           abs(i - row) != abs(j - col);
  }

  // Функция распечатки новой позиции
  ostream & print(ostream & ps) const {
    position->print(ps);      // печать старой позиции
    // Печатаем новую горизонталь
    for (int i = 1; i < col; i++) { ps << ". "; }
    ps << "Q ";
    for (int i = col+1; i <= maxQueens; i++) { ps << ". "; }
    ps << endl;
  }
};

SmartPtr<Position> queen2(int n);

#endif
