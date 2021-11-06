/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.1. Еще о представлении множеств                   *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : intset.cpp                                       *
*  Описание : Реализация множества натуральных чисел с помощью *
*             представления в виде характеристической функции  *
***************************************************************/

#include "intset.h"

void IntSet::IntSetIterator::findNext() {
  while (!currentSet->contains(currentElement)) {
    currentElement++;
  }
}

// Функция add возвращает множество с добавленным элементом
SmartPtr<IntSet> add(const SmartPtr<IntSet> & set, int n) {
  return SmartPtr<IntSet>(new SetPlusElement(set, n));
}

// Функция addRange возвращает множество с добавленными элементами
SmartPtr<IntSet> addRange(const SmartPtr<IntSet> & set, int min, int max) {
  return SmartPtr<IntSet>(new SetPlusRange(set, min, max));
}

// Функция remove возвращает множество с удаленным элементом
SmartPtr<IntSet> remove(const SmartPtr<IntSet> & set, int n) {
  return SmartPtr<IntSet>(new SetMinusElement(set, n));
}

// Функция removeRange возвращает множество с удаленными элементами
SmartPtr<IntSet> removeRange(const SmartPtr<IntSet> & set, int min, int max) {
  return SmartPtr<IntSet>(new SetMinusRange(set, min, max));
}

// Функция conjunct возвращает пересечение двух множеств
SmartPtr<IntSet> conjunct(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2) {
  return SmartPtr<IntSet>(new Conjunction(s1, s2));
}

// Функция disjunct возвращает объединение двух множеств
SmartPtr<IntSet> disjunct(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2) {
  return SmartPtr<IntSet>(new Disjunction(s1, s2));
}

// Функция inverse возвращает дополнение множества
SmartPtr<IntSet> inverse(const SmartPtr<IntSet> & s) {
  return SmartPtr<IntSet>(new Inversion(s));
}

// Функция diff выдает разность двух заданных множеств
SmartPtr<IntSet> diff(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2) {
  return SmartPtr<IntSet>(new Difference(s1, s2));
}
