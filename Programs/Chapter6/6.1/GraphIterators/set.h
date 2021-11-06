/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.1. Обходы и поиск в графах                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : set.h                                            *
*  Описание : Определение класса Set с реализацией множества   *
*             в виде битовой шкалы                             *
***************************************************************/

#ifndef __SET_H
#define __SET_H

#include "iterator.h"

typedef unsigned short WORD;          // 16-битовое беззнаковое целое

class Set {

  // Операции над множествами: объединение, пересечение, разность, дополнение

  friend const Set & operator | (const Set & s1, const Set & s2);
  friend const Set & operator & (const Set & s1, const Set & s2);
  friend const Set & operator - (const Set & s1, const Set & s2);
  friend const Set & operator - (const Set & s);

  int minElem;    // нижняя граница шкалы
  int maxElem;    // верхняя граница шкалы
  WORD *elems;    // сама шкала
  int numWords;   // длина шкалы в словах (WORDs)

  class SetIterator : public Iterator<int> {
    // Множество:
    Set * set;
    // "Адрес" текущего элемента:
    int nextWord;
    int nextBit;
    // Количество непройденных элементов множества:
    int left;
  public :
    SetIterator(Set * set) : set(set), nextWord(-1), nextBit(15), left(set->card()+1) { ++*this; }
    bool hasMoreElements() const { return left > 0; }
    Iterator<int> & operator ++();
    const int & operator *() const { return nextWord*16 + nextBit + set->minElem; }
  };

public:
    
  // Конструктор
  Set(int min = 0, int max = 255);

  // Конструктор копирования
  Set(const Set & s);

  // Деструктор
  ~Set();

  // Проверка принадлежности элемента множеству
  bool has(int n) const;

  // Добавление элемента
  Set & operator |= (int n);

  // Добавление множества (объединение множеств)
  Set & operator |= (const Set & other);

  // Добавление целых из заданного диапазона
  Set & addScale(int from, int to);

  // Удаление целых из заданного диапазона
  Set & remScale(int from, int to);

  // Пересечение множеств
  Set & operator &= (const Set & other);

  // Удаление элемента из множества
  Set & operator -= (int n);

  // Удаление множества из множества (разность множеств)
  Set & operator -= (const Set & other);

  // Инверсия (нахождение дополнения) множества
  Set & inverse();

  // Количество элементов множества
  int card() const;

  // Проверка пустоты множества
  bool empty() const;

  // Итератор элементов
  Iterator<int> * iterator() { return new SetIterator(this); }
};

#endif
