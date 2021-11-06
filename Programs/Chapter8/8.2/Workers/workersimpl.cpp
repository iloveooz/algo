/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : workersimpl.cpp                               *
*  Описание    : Реализация функционального алгоритма          *
*                распределения рабочих мест с оптимальной      *
*                производительностью                           *
***************************************************************/

#include "workersimpl.h"

//-----------------------------------------------------------------------
// Рекурсивная функция recAssignment строит и выдает лучшую
// расстановку maxWorkers работников при условии, что busy рабочих мест
// уже заняты, и эта расстановка определяется аргументом assign функции.
//-----------------------------------------------------------------------
SmartPtr<Assignment> recAssignment(
           const SmartPtr<Assignment> assign, int busy, int maxWorkers) {
  if (busy == maxWorkers) {
    // Все рабочие уже расставлены, можно выдавать 
    // указатель на полученную расстановку работников.
    return assign;
  } else {
    // Максимальная достигнутая производительность
    double maxAchieved = -1;
    // Лучшая расстановка, при которой была достигнута
    // эта максимальная производительность
    SmartPtr<Assignment> bestAchieved;
    // Цикл перебора оставшихся рабочих – кандидатов на новое место
    for (int num = 0;  num < maxWorkers;  num++) {
      if (assign->free(num)) {
        // Найден очередной свободный работник, пробуем ставить его на
        // место busy+1 и вычислить наилучшую в этих условиях расстановку
        SmartPtr<Assignment> next(new NewAssignment(num, busy, assign));
        SmartPtr<Assignment> newAssign = recAssignment(
                                              next, busy+1, maxWorkers);
        // Проверяем достигнутую производительность:
        double curAchieved = newAssign->prod();
        if (curAchieved > maxAchieved) {
          // Получили что-то лучшее, чем было
          maxAchieved = curAchieved;
          bestAchieved = newAssign;
        }
      }
    }
    // Результат - лучшая из достигнутых расстановок
    return bestAchieved;
  }
}

// Функция, вычисляющая лучшую расстановку рабочих
SmartPtr<Assignment> bestAssignment(fProd output, int n) {
  SmartPtr<Assignment> basePtr(new EmptyAssignment(output));
  return recAssignment(basePtr, 0, n);
}

