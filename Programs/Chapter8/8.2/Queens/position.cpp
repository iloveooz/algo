/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : position.cpp                                  *
*  Описание    : Представление позиции: реализация некоторых   *
*                алгоритмов                                    *
***************************************************************/

#include "position.h"
#include <stdlib.h>

using namespace std;

ostream & operator << (ostream & os, const Position & pos) {
  return pos.print(os);
}

// Рекурсивная функция, получающая новую правильную позицию из старой
// с помощью добавления нового ферзя на следующую горизонталь.
// Аргумент row задает количество уже рассталенных ферзей (заполненных
// горизонталей)
SmartPtr<Position> recQueen2(const SmartPtr<Position> & position,
                             int row, int maxQueens) {
  if (row == maxQueens) {
    // Уже расставлены все ферзи
    return position;
  } else {
    // Пытаемся поставить нового ферзя в ряд с номером row
    for (int col = 1;  col <= maxQueens;  col++) {
      if (position->permits(row, col)) {
        // Новый ферзь не атакует ни одного из уже расставленных.
        // Формируем новую позицию и делаем рекурсивный вызов
        SmartPtr<Position> nextPos(
                         new NewPosition(position, col, row, maxQueens));
        SmartPtr<Position> newPos =
                         recQueen2(nextPos, row + 1, maxQueens);
        // Если удалось обнаружить правильную позицию с таким ферзем 
        if (newPos) return newPos;
      }
    }
    // Не удалось поставить нового ферзя ни на одну вертикаль
    return SmartPtr<Position>(NULL);
  }
}

SmartPtr<Position> queen2(int n) {
  // В начале работы позиция пуста и ни одного ферзя еще не расставлено
  return recQueen2(SmartPtr<Position>(new EmptyPosition()), 0, n);
}
