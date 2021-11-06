/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.5. Графы                                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : set.h                                            *
*  Описание : Определение класса Set с реализацией множества   *
*             в виде битовой шкалы                             *
***************************************************************/

#ifndef __SET_H
#define __SET_H

typedef unsigned short WORD;          // 16-битовое беззнаковое целое

class Set {

  int minElem;    // нижняя граница шкалы
  int maxElem;    // верхняя граница шкалы
  WORD *elems;    // сама шкала
  int numWords;   // длина шкалы в словах (WORDs)

  // Операции над множествами: объединение, пересечение, разность, дополнение

  friend const Set & operator | (const Set & s1, const Set & s2);
  friend const Set & operator & (const Set & s1, const Set & s2);
  friend const Set & operator - (const Set & s1, const Set & s2);
  friend const Set & operator - (const Set & s);

public:
    
  // Конструктор
  Set(int min = 0, int max = 255);

  // Конструктор копирования
  Set(const Set & s);

  // Деструктор
  ~Set();

  // Оператор присваивания
  Set & operator = (const Set & other);

  // Проверка принадлежности элемента множеству
  bool has(int n) const;

  // Добавление элемента
  Set & operator |= (int n);

  // Добавление множества (объединение множеств)
  Set & operator |= (const Set & other);

  // Пересечение множеств
  Set & operator &= (const Set & other);

  // Удаление элемента из множества
  Set & operator -= (int n);

  // Удаление множества из множества (разность множеств)
  Set & operator -= (const Set & other);

  // Инверсия (нахождение дополнения) множества
  Set & inverse();
};

#endif
