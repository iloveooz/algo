/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.1. Абстрактные типы данных                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : date.h                                           *
*  Описание : Определение абстрактного класса для              *
*             представления абстрактного типа данных Date      *
***************************************************************/

#ifndef __DATE_H
#define __DATE_H

// Номера месяцев, определенные с помощью мнемонических констант
enum Month {
  JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE,
  JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER,
};

//==============================================================
// Абстрактный класс Date определяет абстрактный тип данных
// 'Дата Григорианского календаря' и набор операции над датами
//==============================================================

class Date {

public:
  // Виртуальный пустой деструктор для переопределения в классах-наследниках
  virtual ~Date() {}

  // Функции доступа к "полям" даты.

  // Чтение/запись числа. Аргумент должен находиться в пределах от 1 
  // до последнего числа текущего месяца.
  virtual int getDate() const = 0;
  virtual void setDate(int day) = 0;

  // Чтение/запись месяца. Аргумент должен иметь значение от 1 до 12.
  virtual int getMonth() const = 0;
  virtual void setMonth(int month) = 0;

  // Чтение/запись года.   
  // Диапазон правильных дат определяется конкретной реализацией.
  // Он должен покрывать по крайней мере интервал между 1900 и 2100 годами.
  virtual int getYear() const = 0;
  virtual void setYear(int year) = 0;

  // Функции сдвига дат на определенный временной интервал.
  // Если месяц изменяется то число может быть скорректировано так, чтобы
  // оно не превышало количества дней в новом установленном месяце.
  virtual Date & addDate(int days = 1) = 0;
  virtual Date & subDate(int days = 1) = 0;
  virtual Date & addMonth(int months = 1) = 0;
  virtual Date & subMonth(int months = 1) = 0;
  virtual Date & addYear(int years = 1) = 0;
  virtual Date & subYear(int years = 1) = 0;

  // Присваивание создает копию даты
  virtual Date & operator = (const Date & date) = 0;

  // Следующие 4 оператора являются просто сокращениями для соответствующих функций сдвига.
  // Ввиду этого их реализации сделаны прямо в абстрактном классе
  // (в противоположность большинству других функций и операторов)
  virtual Date & operator += (int days) { return addDate(days); }
  virtual Date & operator -= (int days) { return subDate(days); }
  virtual Date & operator ++ () { return addDate(); }
  virtual Date & operator -- () { return subDate(); }

  // Все операторы сравнения определены друг через друга.
  // Это позволяет в реализации определить только "минимальный набор"
  // из трех операторов, например, <, <= и ==. Разумеется, каждая 
  // реализация вправе предъявить и полный набор всех операций.
  virtual bool operator < (const Date & date) const { return !(*this >= date); }
  virtual bool operator == (const Date & date) const { return !(*this != date); }
  virtual bool operator > (const Date & date) const { return !(*this <= date); }
  virtual bool operator <= (const Date & date) const { return !(*this > date); }
  virtual bool operator != (const Date & date) const { return !(*this == date); }
  virtual bool operator >= (const Date & date) const { return !(*this < date); }

  // Функция форматирования позволяет представить дату в виде строки.
  virtual const char * format() const;
};

// Заголовки общих фукнций над датами:
// определение високосности года и
bool leapYear(int year);
// вычисление числа дней в месяце
int daysInMonth(int month, int year);

#endif
