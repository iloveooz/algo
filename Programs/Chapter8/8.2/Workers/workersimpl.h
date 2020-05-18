/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : workersimpl.h                                 *
*  Описание    : Определение классов для реализации алгоритма  *
*                оптимального распределения рабочих мест       *
***************************************************************/

#ifndef __WORKERS_IMPL_H
#define __WORKERS_IMPL_H

#include "workers.h"

class EmptyAssignment : public Assignment {
public :
  EmptyAssignment(fProd output) : Assignment(output) {}
  // Вычисление суммарной производительности расстановки
  double prod() const { return 0; }
  // Проверка, свободен ли рабочий с заданным номером i
  bool free(int i) const { return true; }
  // Вывод информации о расстановке рабочих в выходной поток
  void print(ostream & os) const {}
};

class NewAssignment : public Assignment {
  int wr;                           // Номер нового рабочего
  int wp;                           // Номер его рабочего места
  SmartPtr<Assignment> oldAssign;   // Базовая расстановка

public :
  // Конструктор
  NewAssignment(int wr, int wp, const SmartPtr<Assignment> & oldAssign)
    : Assignment(oldAssign->getOutput()), wr(wr), wp(wp), oldAssign(oldAssign) {}

  // К базовой производительности труда добавляется производительность 
  // труда рабочего wr на рабочем месте wp.
  double prod() const {
    return oldAssign->prod() + output(wp, wr);
  }

  // Свободны все те, кто был свободен раньше, кроме рабочего wr.
  bool free(int i) const {
    return i != wr && oldAssign->free(i);
  }

  // К выводу базовой расстановки добавляется информация о том,
  // что рабочее место wp занято работником номер wr.
  void print(ostream & os) const {
    oldAssign->print(os);
    os << "Place number: " << wp << "; worker number: " << wr << endl;
  }
};

SmartPtr<Assignment> recAssignment(const SmartPtr<Assignment> assign, int busy, int maxWorkers);

#endif
