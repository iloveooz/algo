/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.1. Абстрактные типы данных                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Тестовая функция для проверки двух представлений *
*             дат Григорианского календаря                     *
***************************************************************/

#include <iostream>
#include "structdate.h"
#include "daysdate.h"

using namespace std;

int main() {
  cout << "Today: " << StructDate().format() << endl;
  // Первая часть проверяет операции над датами, представленными в виде структуры
  StructDate dt1(21, JUNE, 2003);
  cout << "Should be 21-Jun-2003: " << dt1.format() << endl;
  cout << "Should be 1-Jul-9004: " << (dt1.addYear(7001) += 10).format() << endl;
  cout << "Should be 1-Jan-9004: " << dt1.subMonth(6).format() << endl;
  cout << "Should be 31-Dec-9003: " << (--dt1).format() << endl;
  cout << "Should be 29-Feb-9004: " << (dt1.addMonth(2)).format() << endl << endl;

  // Вторая часть проверяет операции над датами, представленными в виде счетчика дней
  DaysDate dt2(21, JUNE, 2003);
  cout << "Should be 21-Jun-2003: " << dt2.format() << endl;
  cout << "Should be 1-Jul-9004: " << (dt2.addYear(7001) += 10).format() << endl;
  cout << "Should be 1-Jan-9004: " << dt2.subMonth(6).format() << endl;
  cout << "Should be 31-Dec-9003: " << (--dt2).format() << endl;
  cout << "Should be 29-Feb-9004: " << (dt2.addMonth(2)).format() << endl;

  return 0;
}
