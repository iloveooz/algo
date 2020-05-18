/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.1. Абстрактные типы данных                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : structdate.cpp                                   *
*  Описание : Реализация календарной даты в виде структуры     *
*             из дня месяца и года (d, m, y)                   *
***************************************************************/

#include <stdio.h>
#include "structdate.h"

//==============================================================
// В следующих двух функциях может потребоваться коррекция даты
// после того, как новое значение поля будет установлено
//==============================================================

void StructDate::setMonth(int month) { 
  m = month;
  // возможно, нужна коррекция даты в случае, 
  // если день вышел за пределы месяца
  int limit = daysInMonth(m, y);
  if (d > limit) d = limit;
}

void StructDate::setYear(int year) {
  y = year;
  // возможна коррекция даты в случае 29 февраля
  if (d == 29 && m == FEBRUARY && !leapYear(y))
    d = 28;
}

//==============================================================
// Функции сдвига
//==============================================================

// Функции addDate и subDate реализованы в виде цикла,
// последовательно изменяющего дату путем прибавления (или вычитания)
// единицы к номеру месяца. Это может быть крайне неэффективно 
// в случае большого количества дней в аргументе.

Date & StructDate::addDate(int days) {
  if (days < 0) return subDate(-days);
  // цикл по месяцам
  while (days > 0) {
    int mDays = daysInMonth(m, y);
    if (d + days <= mDays) {
      // конец цикла: месяц изменять больше не нужно
      d += days;
      days = 0;
    } else {
      // переходим к первому числу следующего месяца
      days -= (mDays - d + 1);
      d = 1;
      // возможно, требуется сменить год
      if (++m > DECEMBER) {
        m = JANUARY;
        y++;
      }
    }
  }
  return *this;
}

Date & StructDate::subDate(int days) {
  if (days < 0) return addDate(-days);
  // цикл по месяцам
  while (days > 0) {
    if (days < d) {
      // конец цикла: месяц изменять больше не нужно
      d -= days;
      days = 0;
    } else {
      // переходим к последнему числу предыдущего месяца,
      // при этом, возможно, требуется сменить год
      if (--m < JANUARY) {
        m = DECEMBER;
        y--;
      }
      days -= d;
      d = daysInMonth(m, y);
    }
  }
  return *this;
}

// Сдвиг на определенное число месяцев осуществляется
// прямыми вычислениями. Возможно, потребуется коррекция даты

Date & StructDate::addMonth(int months) {
  if (months < 0) return subMonth(-months);
  // Изменение месяца/года
  y += months / 12;
  m += months % 12;
  if (m > DECEMBER) {
    m -= 12; y++;
  }
  // возможная коррекция даты в случае, если текущее число 
  // выходит за пределы текущего месяца
  int limit = daysInMonth(m, y);
  if (d > limit) d = limit;
  return *this;
}

Date & StructDate::subMonth(int months) {
  if (months < 0) return addMonth(-months);
  // Изменение месяца/года
  y -= months / 12;
  m -= months % 12;
  if (m < JANUARY) {
    m += 12; y--;
  }
  // возможная коррекция даты в случае, если текущее число 
  // выходит за пределы текущего месяца
  int limit = daysInMonth(m, y);
  if (d > limit) d = limit;
  return *this;
}

// Функции сдвига года меняют только год. Коррекция
// даты может понадобиться только в случае 29 февраля

Date & StructDate::addYear(int years) {
  y += years;
  if (d == 29 && m == FEBRUARY && !leapYear(y))
    d = 28;
  return *this;
}

Date & StructDate::subYear(int years) {
  y -= years;
  if (d == 29 && m == FEBRUARY && !leapYear(y))
    d = 28;
  return *this;
}

// Оператор присваивания использует для аргумента только
// методы, определенные в абстрактном типе данных. Поэтому
// даная реализация присваивания не зависит от конкретного
// представления аргумента.

Date & StructDate::operator = (const Date & date) {
  d = date.getDate();
  m = date.getMonth();
  y = date.getYear();
  return *this;
}

// Операторы сравнения дат также используют только методы
// абстрактного типа данных для аргументов. Реализованы только
// три оператора сравнения, реализация остальных используется та,
// которая была определена в классе Date.

bool StructDate::operator < (const Date & date) const {
  int date_d = date.getDate();
  int date_m = date.getMonth();
  int date_y = date.getYear();
  return y < date_y ||
        (y == date_y && (m < date_m ||
                        (m == date_m && d < date_d)));
}

bool StructDate::operator == (const Date & date) const {
  return y == date.getYear() && m == date.getMonth() && d == date.getDate();
}

bool StructDate::operator > (const Date & date) const {
  int date_d = date.getDate();
  int date_m = date.getMonth();
  int date_y = date.getYear();
  return y > date_y ||
        (y == date_y && (m > date_m ||
                        (m == date_m && d > date_d)));
}
