/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.4. Итераторы                                      *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : NegCounter.h                                  *
*  Описание    : Описание класса для итерации списка:          *
*                подсчет числа отрицательных элементов         *
***************************************************************/

#ifndef __NEG_COUNTER_H
#define __NEG_COUNTER_H

#include "Actor.h"

class NegativeCounter : public Actor {
  int counter;
public :
  NegativeCounter() : counter(0) {}
  int getCounter() { return counter; }
  void action(int & element) { counter += (element < 0); }
};

#endif
