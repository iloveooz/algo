/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.1. Абстрактные типы данных                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : daysdate.h                                       *
*  Описание : Реализация арифметики дат для представления даты *
*             в виде счетчика дней - описание класса           *
***************************************************************/

#ifndef __DAYS_DATE_H
#define __DAYS_DATE_H

#include "date.h"

//==============================================================
// В этом классе дата Григорианского календаря реализуется в виде 
// счетчика дней, прошедших с начала 1600 года
// (от 31 декабря 1599 года). Правильными датами считаются даты в
// диапазоне от 1 января 1600 года до 31 декабря 9999 года.
//==============================================================

class DaysDate : public Date {
  // Счетчик дней, прошедших с 31 декабря 1599 года
  long days;

public:

  // Конструктор создает "сегодняшнюю" дату.
  DaysDate();

  // Конструктор копирования
  DaysDate(const DaysDate & date) { days = date.days; }

  // Конструктор даты "по полям"
  DaysDate(int d, int m, int year);

  // Функции, подлежащие переопределению или доопределению.

  // Функции доступа к полям
  void setDate(int day);
  int getDate() const;
  void setMonth(int month);
  int getMonth() const;
  void setYear(int year);
  int getYear() const;

  // Функции сдвига даты
  Date & addDate(int days = 1);
  Date & subDate(int days = 1);
  Date & addMonth(int months = 1);
  Date & subMonth(int months = 1);
  Date & addYear(int years = 1);
  Date & subYear(int years = 1);

  // Оператор присваивания
  Date & operator = (const Date & date);

  // Опреаторы сравнения
  bool operator < (const Date & date) const;
  bool operator == (const Date & date) const;
  bool operator > (const Date & date) const;
  bool operator <= (const Date & date) const;
  bool operator != (const Date & date) const;
  bool operator >= (const Date & date) const;
};

#endif
