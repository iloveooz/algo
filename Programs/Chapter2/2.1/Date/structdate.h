/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.1. Абстрактные типы данных                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : structdate.h                                     *
*  Описание : Реализация календарной даты в виде структуры     *
*             из дня месяца и года (d, m, y)                   *
***************************************************************/

#ifndef __STRUCT_DATE_H
#define __STRUCT_DATE_H

#include <time.h>      // для функции time определения текущей даты
#include "date.h"

class StructDate : public Date {
  int d;    // номер дня 1-31
  int m;    // номер месяца 1-12 (JANUARY - DECEMBER)
  int y;    // номер года (1600-9999)

public:

  // Конструкторы

  StructDate(int d, int m, int y) {
    StructDate::d = d;
    StructDate::m = m;
    StructDate::y = y;
  }

  StructDate() {
    // Текущая дата берется с помощью функции 'time' из пакета TIME
    time_t tm;
    time(&tm);
    struct tm * dt = localtime(&tm);
    d = dt->tm_mday;
    m = dt->tm_mon + 1;
    y = dt->tm_year + 1900;
  }

  StructDate(const Date & date) {
    // Копирование реализовано через присваивание
    *this = date; 
  }

  //============================================================
  // Функции доступа, вообще говоря, реализуются непосредственным
  // обращением к соответствующим полям. Однако, при установке
  // месяца и года может также потребоваться коррекция дня.
  //============================================================

  void setDate(int day) { d = day; }
  int getDate() const { return d; }
  void setMonth(int month);
  int getMonth() const { return m; }
  void setYear(int year);
  int getYear() const { return y; }

  //============================================================
  // Функции сдвига дат
  //============================================================

  Date & addDate(int days = 1);
  Date & addMonth(int months = 1);
  Date & addYear(int years = 1);
  Date & subDate(int days = 1);
  Date & subMonth(int months = 1);
  Date & subYear(int years = 1);

  // Оператор присваивания реализован в соответствии с соглашениями
  // для данного оператора: он возвращает ссылку на измененную дату.

  Date & operator = (const Date & date);

  // Операторы сравнения дат используют лексикографический порядок дат

  bool operator < (const Date & date) const;
  bool operator == (const Date & date) const;
  bool operator > (const Date & date) const;
};

#endif
