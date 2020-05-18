/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.2. Об одном способе вычисления конечных сумм      *
*                                                              *
*  Автор    : А. Кубенский                                     *
*  Файл     : main.cpp                                         *
*  Описание : Проверка системы обмена сообщениями для          *
*             вычисления конечных сумм                         *
***************************************************************/

#include <iostream>
#include "emember.h"
#include "fibmember.h"
#include "fibmember1.h"
#include "lnmember.h"
#include "sum.h"

using namespace std;

int main() {
  // 1. Вычисление приближенного значения числа е
  EMemberFactory eFactory;
  cout << "Approximate value for e = " << sum(eFactory, 10) << endl;

  // 2. Вычисление суммы первых членов последовательности Фибоначчи
  FibMemberFactory fibFactory;
  cout << "Fibonacci sum of 10 numbers = " << sum(fibFactory, 10) << endl;

  // 3. Вычисление приближенного значения натурального логарифма числа 2
  LnMemberFactory lnFactory;
  cout << "Approximate value for ln 2 = " << sum(lnFactory, 100) << endl;

  // 4. Вычисление суммы первых членов последовательности Фибоначчи
  //    (оптимизированный вариант)
  FibMemberFactory1 fibFactory1;
  cout << "Fibonacci sum of 10 numbers = " << sum(fibFactory1, 10) << endl;

  return 0;
}
