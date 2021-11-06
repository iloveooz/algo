/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.4. Итераторы                                      *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : Comparator.h                                  *
*  Описание    : Описание класса для итерации списка:          *
*                поиск заданного элемента                      *
***************************************************************/

#ifndef __COMPARATOR_H
#define __COMPARATOR_H

#include "Actor.h"

class Comparator : public Actor {
  int value;    // значение для сравнения
  bool found;   // признак того, найдено ли значение value в списке
public :
  Comparator(int val) : value(val), found(false) {}
  bool hasFound() { return found; }
  void action(int & element) { if (value == element) found = true; }
};

#endif
