/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.1. Массивы                                        *
*                                                              *
*  Автор    : A.Кубенский                                      *
*  Файл     : dynarray.h                                       *
*  Описание : Определение шаблона классов DynArray             *
***************************************************************/

#ifndef __DYN_ARRAY_H
#define __DYN_ARRAY_H

#include <stdexcept>     // стандартные исключительные ситуации

using namespace std;

template <class Elem>
class DynArray {
  int size;        // текущий размер массива (количество элементов)
  int maxSize;     // размер отведенной памяти
  Elem *array;     // сам массив (размера maxSize)

public :
  // Конструктор нового массива. Аргументы указывают, сколько памяти
  // надо отвести под его элементы, и сколько всего памяти заказывается.
  // Еще один дополнительный аргумент содержит массив для
  // начальной инициализации элементов
  DynArray(int sz = 0, int maxSz = 0, Elem *iniArray = NULL);

  // Конструктор копирования
  DynArray(const DynArray<Elem> & a) {
    size = maxSize = 0;
    *this = a;
  }

  // Деструктор – освобождает занятую ранее память.
  ~DynArray() { delete[] array; }

  // Операция идексации
  Elem & operator [] (int i);

  // Операция поэлементного копирования
  DynArray<Elem> & operator = (const DynArray<Elem> & a);

  // Изменение текущего размера массива. Аргумент delta задает
  // размер изменения (положительный – увеличение размера;
  // отрицательный - уменьшение)
  void resize(int delta);

  // Добавление нового элемента с возможным расширением массива
  void add(const Elem & e);

private:

  // Операция расширения массива
  void enlarge(int delta);

  // Операция уменьшения размера массива
  void shrink(int delta);
};     // Конец определения класса DynArray

// Далее следуют реализации функций-членов класса DynArray
// Реализация конструктора
template <class Elem>
DynArray<Elem>::DynArray(int sz, int maxSz, Elem *iniArray) {
  if ((size = sz) < 0) {
    throw out_of_range("DynArray constructor : Negative array size");
  }
  maxSize = (maxSz < sz ? sz : maxSz);
  array = new Elem[maxSize];      // отведение памяти
  if (iniArray) {                 // копирование элементов
    for (int i = 0; i < size; i++)
      array[i] = iniArray[i];
  }
}

// Реализация операции индексации
template <class Elem>
Elem & DynArray<Elem>::operator [] (int i) {
  if (i < 0 || i >= size) {
    throw out_of_range("operator [] : Array index is out of range");
  }
  return array[i];
}

// Реализация операции присваивания (поэлементного копирования)
template <class Elem>
DynArray<Elem> & DynArray<Elem>::operator = (const DynArray<Elem> & a) {
  resize(a.size - size);
  for (int i = 0; i < size; i++)
    array[i] = a.array[i];
  return *this;
}

// Реализация операции изменения текущего размера массива
template <class Elem>
void DynArray<Elem>::resize(int delta) {
  if (delta > 0) enlarge(delta);        // увеличение размера массива
  else if (delta < 0) shrink(-delta);   // уменьшение размера массива
}

// Реализация операции добавления элемента
template <class Elem>
void DynArray<Elem>::add(const Elem & e) {
  resize(1);
  array[size-1] = e;
}

// Реализация операции расширения массива
template <class Elem>
void DynArray<Elem>::enlarge(int delta) {
  if ((size += delta) > maxSize) {   // необходимо заказать новую память
    maxSize = size;
    Elem *newArray = new Elem[maxSize];
    // копируем элементы
    for (int i =0;  i < size - delta;  i++)
      newArray[i] = array[i];
    array = newArray;
  }
}

// Реализация операции уменьшения размера массива
template <class Elem>
void DynArray<Elem>::shrink(int delta) {
  size = (delta > size ? 0 : size - delta);
}

#endif

