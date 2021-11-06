/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.2. Поиск кратчайших путей                         *
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

// Добавление целых из заданного диапазона
Set & Set::addScale(int from, int to) {
  if (from < minElem || to > maxElem) {
    throw out_of_range("Cannot add an element: it is out of range");
  } else if (from <= to) {
    // "Адрес" первого элемента
    int wordFrom = (from - minElem) >> 4;
    int bitFrom = (from - minElem) & 15;
    // "Адрес" последнего элемента
    int wordTo = (to - minElem) >> 4;
    int bitTo = (to - minElem) & 15;
    for (int i = wordFrom + 1; i < wordTo; i++) {
      elems[i] = 0xFFFF;
    }
    if (wordFrom == wordTo) {
      elems[wordFrom] |= (0xFFFF << bitFrom) & ~(0xFFFF << (bitTo+1));
    } else {
      elems[wordFrom] |= (0xFFFF << bitFrom);
      elems[wordTo] |= ~(0xFFFF << (bitTo+1));
    }
  }
  return *this;
}

// Удаление целых из заданного диапазона
Set & Set::remScale(int from, int to) {
  if (from < minElem || to > maxElem) {
    throw out_of_range("Cannot add an element: it is out of range");
  } else if (from <= to) {
    // "Адрес" первого элемента
    int wordFrom = (from - minElem) >> 4;
    int bitFrom = (from - minElem) & 15;
    // "Адрес" последнего элемента
    int wordTo = (to - minElem) >> 4;
    int bitTo = (to - minElem) & 15;
    for (int i = wordFrom + 1; i < wordTo; i++) {
      elems[i] = 0;
    }
    if (wordFrom == wordTo) {
      elems[wordFrom] &= ~(0xFFFF << bitFrom) | (0xFFFF << bitTo);
    } else {
      elems[wordFrom] &= ~(0xFFFF << bitFrom);
      elems[wordTo] &= (0xFFFF << bitTo);
    }
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

// Подсчет числа элементов множества
int Set::card() const {
  int c = 0;
  for (int i = 0;  i < numWords;  i++) {
    WORD elem = elems[i];
    while (elem != 0) {
      c += (elem & 1);
      elem >>= 1;
    }
  }
  return c;
}

// Проверка пустоты множества
bool Set::empty() const {
  for (int i = 0;  i < numWords;  i++) {
    if (elems[i]) return false;
  }
  return true;
}


Iterator<int> & Set::SetIterator::operator ++() {
  if (left == 0) return *this;
  --left;
  while (++nextBit < 16 && ((set->elems)[nextWord] & (1 << nextBit)) == 0) ;
  if (nextBit < 16) return *this;
  while (++nextWord < set->numWords && (set->elems)[nextWord] == 0) ;
  nextBit = -1;
  while (++nextBit < 16 && ((set->elems)[nextWord] & (1 << nextBit)) == 0) ;
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
