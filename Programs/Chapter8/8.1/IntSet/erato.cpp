/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.1. Еще о представлении множеств                   *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : erato.cpp                                        *
*  Описание : Реализация алгоритма вычисления последовательно- *
*             сти простых чисел с помощью "решета Эратосфена"  *
***************************************************************/

#include "erato.h"

SmartPtr<IntSet> filter(int n, const SmartPtr<IntSet> & set) {
  return SmartPtr<IntSet>(new Filter(n, set));
}

SmartPtr<IntSet> sieve(int max, const SmartPtr<IntSet> & set) {
  int first = **set->elements();
  SmartPtr<IntSet> result = set;
  if (first * first <= max) {
    result = add(sieve(max, filter(first, set)), first);
  }
  return result;
}
