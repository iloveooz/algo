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
SmartPtr<Assignment> recAssignment(const SmartPtr<Assignment> assign,
                                   int busy, int maxWorkers, double maxFree, double * maxProds) {
  if (busy == maxWorkers) {
    // Все рабочие уже расставлены, можно выдавать 
    // указатель на полученную расстановку работников.
    return assign;
  } else {
    // Функция вычисления производительности
    fProd output = assign->getOutput();
    // Упорядочение свободных работников по убыванию производительности
    int * freeWorkers = new int[maxWorkers-busy];
    for (int num = 0, k = 0;  num < maxWorkers;  num++) {
      if (assign->free(num)) freeWorkers[k++] = num;
    }
    // Сортировка массива по убыванию производительности
    for (int i = 1; i < maxWorkers-busy; i++) {
      int j = i-1;
      int p = freeWorkers[i];
      while (j >= 0 && output(busy, freeWorkers[j]) < output(busy, p)) {
        freeWorkers[j+1] = freeWorkers[j];
        j--;
      }
      freeWorkers[j+1] = p;
    }
    // Максимальная достигнутая производительность
    double maxAchieved = -1;
    // Лучшая расстановка, при которой была достигнута
    // эта максимальная производительность
    SmartPtr<Assignment> bestAchieved;
    // Цикл перебора оставшихся рабочих – кандидатов на новое место
    for (int k = 0;  k < maxWorkers-busy;  k++) {
      int num = freeWorkers[k];
      // Выбираем очередного свободного работника и пробуем ставить его на
      // место busy+1, вычисляя наилучшую в этих условиях расстановку.
      // Предварительно проверяем, имеет ли смысл вообще пробовать.
      if (assign->prod() + output(busy, num) + maxFree - maxProds[num] > maxAchieved) {
        SmartPtr<Assignment> next(new NewAssignment(num, busy, assign));
        SmartPtr<Assignment> newAssign = recAssignment(
            next, busy+1, maxWorkers, maxFree - maxProds[num], maxProds);
        // Проверяем достигнутую производительность:
        double curAchieved = newAssign->prod();
        if (curAchieved > maxAchieved) {
          // Получили что-то лучшее, чем было
          maxAchieved = curAchieved;
          bestAchieved = newAssign;
        }
      }
    }
    delete[] freeWorkers;
    // Результат - лучшая из достигнутых расстановок
    return bestAchieved;
  }
}

// Функция, вычисляющая лучшую расстановку рабочих
SmartPtr<Assignment> bestAssignment(fProd output, int n) {
  double maxFree = 0;
  double * maxProds = new double[n];
  for (int wr = 0; wr < n; wr++) {
    double max = 0, curr;
    for (int wp = 0; wp < n; wp++) {
      if ((curr = output(wp, wr)) > max) max = curr;
    }
    maxFree += (maxProds[wr] = max);
  }
  SmartPtr<Assignment> basePtr(new EmptyAssignment(output));
  SmartPtr<Assignment> bestAssign = recAssignment(basePtr, 0, n, maxFree, maxProds);
  delete[] maxProds;
  return bestAssign;
}

