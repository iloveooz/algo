/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.1. Абстрактные типы данных                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : daysdate.cpp                                     *
*  Описание : Реализация арифметики дат для представления даты *
*             в виде счетчика дней                             *
***************************************************************/

#include <time.h>
#include "daysdate.h"

// Количества дней, прошедшие с начала года до первого числа 
// каждого месяца - для нормального и високосного годов.
static const int monthLength[2][12] = {
 { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
 { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 }
};

//==============================================================
// В данной реализации наиболее важными являются две следующие 
// функции преобразования представлений. Они дают возможность
// свободно переключаться между двумя основными способами
// представления дат - в виде структуры и в виде счетчика дней
//==============================================================

// Аргументы - поля даты, представленной в виде структуры. 
// Результат функции - счетчик дней.
static long convert(int d, int m, int y) {
  // Число полных лет, прошедших от начала 1600 года до года 'y'
  int year = y - 1600;
  // Общее количество дней в этих годах (високосные годы также учитываются)
  long days = year*365 + year/4 - year/100 + year/400;
  // Если год 'y' - високосный, то один день надо пока отнять
  bool leap = leapYear(y);
  if (leap) days--;
  // Наконец, добавляем число дней, прошедшее с начала года до начала 
  // заданного месяца и число дней, прошедшее в этом месяце
  return days + monthLength[leap][m-1] + d;
}

// 'days' в аргументе - это счетчик числа дней, прошедших с начала 1600 года.
// Функция преобразует его в тройку 'd', 'm', 'y' (день, месяц, год)
static void convert (long days, int & d, int & m, int & y) {
  // Сначала приблизительно вычислим год. Ошибка вычисления не может
  // составить более одного года для дат от 1600 до 9999 года.
  y = (int)(1600 + 4*days/(365*4 + 1)) + 1;
  // Теперь вычислим разницу между заданным счетчиком дней и
  // началом только что вычисленного года (1 января)
  int diff = (int)(days - convert(1, JANUARY, y) + 1);
  // Если разность отрицательна, то корректируем год и 
  // делаем разность положительной
  if (diff <= 0) y--;
  bool leap = leapYear(y);
  if (diff <= 0) diff += 365 + leap;
  // Теперь определяем номер месяца последовательным поиском в массиве
  for (m = JANUARY;
       m < DECEMBER && diff > monthLength[leap][m];
       m++)
    ;
  // Наконец, вычисляется дата.
  d = diff - monthLength[leap][m-1];
}

// Следующая функция производит коррекцию даты в том случае,
// когда заданного дня нет в заданном месяце заданного года
static void correctDate(int & d, int m, int y) {
  // Смотрим, какой день в месяце - последний
  int limit = daysInMonth(m, y);
  // Корректируем дату, если нужно
  if (d > limit) d = limit;
}

// Конструктор "по умолчанию" использует функции time
// и localtime для вычисления сегодняшней даты.
DaysDate::DaysDate() {
  time_t tm;
  time(&tm);
  struct tm * dt = localtime(&tm);
  days = convert(dt->tm_mday, dt->tm_mon + 1, dt->tm_year + 1900);
}

// Следующий конструктор просто конвертирует заданную дату в счетчик дней
DaysDate::DaysDate(int d, int m, int y) {
  days = convert(d, m, y);
}

//==============================================================
// Функции доступа к полям даты конвертируют счетчик дней в
// структуру из дня, месяца и года, после чего работают фактически
// с этой структурой, при необходимости конвертируя ее обратно в
// счетчик дней (для функций set...)
//==============================================================

void DaysDate::setDate(int day) {
  int d, m, y;
  convert(days, d, m, y);
  days = convert(day, m, y);
}

int DaysDate::getDate() const {
  int d, m, y;
  convert(days, d, m, y);
  return d;
}

void DaysDate::setMonth(int month) {
  int d, m, y;
  convert(days, d, m, y);
  correctDate(d, month, y);
  days = convert(d, month, y);
}

int DaysDate::getMonth() const {
  int d, m, y;
  convert(days, d, m, y);
  return m;
}

void DaysDate::setYear(int year) {
  int d, m, y;
  convert(days, d, m, y);
  correctDate(d, m, year);
  days = convert(d, m, year);
}

int DaysDate::getYear() const {
  int d, m, y;
  convert(days, d, m, y);
  return y;
}

//==============================================================
// Единственные две функции, которые могут воспользоваться
// преимуществом данного способа представления даты - это
// функции сдвига даты на определенное количество дней. Это
// единственные функции, не использующие конвертирования
// даты в структурное представление.
//==============================================================

Date & DaysDate::addDate(int days) {
  DaysDate::days += days;
  return *this;
}

Date & DaysDate::subDate(int days) {
  DaysDate::days -= days;
  return *this;
}

//==============================================================
// При сдвиге на определенное число месяцев может потребоваться 
// коррекция даты, если в новом месяце нет текущего дня.
//==============================================================

Date & DaysDate::addMonth(int months) {
  if (months < 0) return subMonth(-months);
  int d, m, y;
  // преобразование даты в структурное представление
  convert(days, d, m, y);
  // изменение номера года и месяца
  y += months / 12;
  m += months % 12;
  if (m > DECEMBER) {
    y++;
    m -= 12;
  }
  // возможная коррекция даты
  correctDate(d, m, y);
  // обратное преобразование даты в счетчик дней
  days = convert(d, m, y);
  return *this;
}

Date & DaysDate::subMonth(int months) {
  if (months < 0) return addMonth(-months);
  int d, m, y;
  // преобразование даты в структурное представление
  convert(days, d, m, y);
  // изменение номера года и месяца
  y -= months / 12;
  m -= months % 12;
  if (m < JANUARY) {
    y--;
    m += 12;
  }
  // возможная коррекция даты
  correctDate(d, m, y);
  // обратное преобразование даты в счетчик дней
  days = convert(d, m, y);
  return *this;
}

//==============================================================
// При сдвиге на определенное количество лет коррекция даты может
// потребоваться только в том случае, если дата - это 29 февраля.
//==============================================================

Date & DaysDate::addYear(int years) {
  int d, m, y;
  // преобразование даты в структурное представление
  convert(days, d, m, y);
  y += years;
  // возможная коррекция даты (из-за разницы между високосным и нормальным годом)
  if (d == 29 && m == FEBRUARY && !leapYear(y))
    d = 28;
  // обратное преобразование даты в счетчик дней
  days = convert(d, m, y);
  return *this;
}

Date & DaysDate::subYear(int years) {
  int d, m, y;
  // преобразование даты в структурное представление
  convert(days, d, m, y);
  y -= years;
  // возможная коррекция даты (из-за разницы между високосным и нормальным годом)
  if (d == 29 && m == FEBRUARY && !leapYear(y))
    d = 28;
  // обратное преобразование даты в счетчик дней
  days = convert(d, m, y);
  return *this;
}

//==============================================================
// Опреатор присваивания использует только абстрактные операции 
// над аргументом, что позволяет ему работать правильно при 
// любом представлении аргумента. Конечно, если бы аргументом
// могла бы быть только дата, представленная счетчиком дней,
// то оператор присваивания можно было бы реализовать гораздо проще.
//==============================================================

Date & DaysDate::operator = (const Date & date) {
  days = convert(date.getDate(), date.getMonth(), date.getYear());
  return *this;
}

//==============================================================
// Аналогично, операторы сравнения используют только абстрактные
// операции над датами-аргументами. В данном представлении даты
// реализованы все 6 операторов сравнения.
//==============================================================

bool DaysDate::operator < (const Date & date) const {
 return days < convert(date.getDate(), date.getMonth(), date.getYear());
}

bool DaysDate::operator == (const Date & date) const {
 return days == convert(date.getDate(), date.getMonth(), date.getYear());
}

bool DaysDate::operator > (const Date & date) const {
 return days > convert(date.getDate(), date.getMonth(), date.getYear());
}

bool DaysDate::operator <= (const Date & date) const {
 return days <= convert(date.getDate(), date.getMonth(), date.getYear());
}

bool DaysDate::operator != (const Date & date) const {
 return days != convert(date.getDate(), date.getMonth(), date.getYear());
}

bool DaysDate::operator >= (const Date & date) const {
 return days >= convert(date.getDate(), date.getMonth(), date.getYear());
}
