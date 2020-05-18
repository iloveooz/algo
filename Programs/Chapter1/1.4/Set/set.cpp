/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.4. Множества                                      *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : set.cpp                                          *
*  Описание : Реализация класса Set                            *
***************************************************************/

// стандартная исключительная ситуация:
#include <stdexcept>

#include "set.h"

using namespace std;

// Конструктор
Set::Set(int min, int max) {
  // обеспечиваем min < max
  if (min > max) {
    minElem = max;
    maxElem = min;
  } else {
    minElem = min;
    maxElem = max;
  }
  int num = maxElem - minElem + 1;     // количество битов в шкале
  numWords = (num + 15) >> 4;          // количество слов (WORDs)
  elems = new WORD[numWords];
  // Обнуление шкалы:
  for (int i = 0; i < numWords; i++) {
    elems[i] = 0;
  }
}

// Конструктор копирования
Set::Set(const Set & s) {
  minElem = s.minElem;
  maxElem = s.maxElem;
  elems = new WORD[numWords = s.numWords];
  for (int i = 0;  i < numWords;  i++) {
    elems[i] = s.elems[i];
  }
}

// Деструктор
Set::~Set() {
  delete[] elems;
}

// Функция проверки принадлежности элемента множеству
bool Set::has(int n) const {
  if (n > maxElem || n < minElem)
    return false;    // элемент выходит за границы множества
  // "Адрес" элемента:
  int word = (n - minElem) >> 4;
  int bit = (n - minElem) & 15;
  return (elems[word] & (1 << bit)) != 0;
}

// Добавление элемента в множество
Set & Set::operator |= (int n) {
  if (n <= maxElem && n >= minElem) {
    // "Адрес" элемента:
    int word = (n - minElem) >> 4;
    int bit = (n - minElem) & 15;
    elems[word] |= (1 << bit);
  } else {
    throw out_of_range("Cannot add an element: it is out of range");
  }
  return *this;
}

// Добавление множества к множеству (объединение множеств)
Set & Set::operator |= (const Set & other) {
  if (other.minElem != minElem || other.maxElem != maxElem) {
    throw out_of_range("Sets incomparable");
  }
  for (int i = 0;  i < numWords;  i++) {
    elems[i] |= other.elems[i];
  }
  return *this;
}

// Пересечение множеств
Set & Set::operator &= (const Set & other) {
  if (other.minElem != minElem || other.maxElem != maxElem) {
    throw out_of_range("Sets incomparable");
  }
  for (int i = 0;  i < numWords;  i++) {
    elems[i] &= other.elems[i];
  }
  return *this;
}

// Удаление элемента из множества
Set & Set::operator -= (int n) {
  if (n <= maxElem && n >= minElem) {
    // "Адрес" элемента:
    int word = (n - minElem) >> 4;
    int bit = (n - minElem) & 15;
    elems[word] &= ~(1 << bit);
  }
  return *this;
}

// Удаление множества из множества (разность множеств)
Set & Set::operator -= (const Set & other) {
  if (other.minElem != minElem || other.maxElem != maxElem) {
    throw out_of_range("Sets incomparable");
  }
  for (int i = 0;  i < numWords;  i++) {
    elems[i] &= ~other.elems[i];
  }
  return *this;
}

// Инверсия (нахождение дополнения) множества
Set & Set::inverse() {
  for (int i = 0;  i < numWords;  i++) {
    elems[i] = ~elems[i];
  }
  return *this;
}

// Операции над множествами, реализованные в виде независимых
// операторов (вне определения класса)

// Объединение множеств
const Set & operator | (const Set & s1, const Set & s2) {
  return Set(s1) |= s2;
}

// Пересечение множеств
const Set & operator & (const Set & s1, const Set & s2) {
  return Set(s1) &= s2;
}

// Разность множеств
const Set & operator - (const Set & s1, const Set & s2) {
  return Set(s1) -= s2;
}

// Дополнение множества
const Set & operator - (const Set & s) {
  return Set(s).inverse();
}

