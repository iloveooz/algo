/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.3. Определение остовных деревьев                  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : arrayhelp.h                                      *
*  Описание : Реализация пирамиды в виде массива элементов     *
***************************************************************/

#ifndef __ARRAY_HEAP_H
#define __ARRAY_HEAP_H

#include "heap.h"

//==============================================================
// Шаблон классов, реализующий пирамиду в виде массива элементов,
// в котором потомки элемента с индексом i расположены в массиве
// в элементах с индексами 2*i+1 и 2*i+2.
//
// Параметр шаблона Element должен иметь конструктор по умолчанию,
// конструктор копирования и над элементами должны быть
// определены стандартные операции сравнения
//==============================================================

template <class Element>
class ArrayHeap : public Heap<Element> {

  Element * array;    // Указатель на массив элементов
  int maxSize, size;  // Размер массива и размер пирамиды

public :
  // Конструкторы:
  ArrayHeap(int maxSize) : maxSize(maxSize), size(0), array(new Element[maxSize]) {}
  ArrayHeap(const ArrayHeap & src);

  // Удаление минимального элемента
  void remove() throw(HeapUnderflow);

  // Доступ к минимальному элементу
  Element & operator *() throw(HeapUnderflow);
  const Element & operator *() const throw(HeapUnderflow);

  // Добавление нового элемента
  Heap<Element> & operator += (const Element & newElem) throw(HeapOverflow);

  // Проверка числа элементов
  bool empty() const { return size == 0; }
  int count() const { return size; }
};

//==============================================================
// Конструктор копирования
//==============================================================
template <class Element>
ArrayHeap<Element>::ArrayHeap(const ArrayHeap & src)
    : maxSize(src.maxSize), size(src.size), array(new Element[maxSize]) {
  for (int i = 0; i < maxSize; i++) array[i] = src.array[i];
}

//==============================================================
// Удаление минимального элемента: на место первого элемента
// записывается элемент из конца массива и "проталкивается"
// вниз по пирамиде
//==============================================================
template <class Element>
void ArrayHeap<Element>::remove() throw(HeapUnderflow) {
  // Проверка на корректность операции
  if (size == 0) throw HeapUnderflow();

  // Число элементов в пирамиде уменьшается
  if (--size == 0) return;

  // Запоминаем последний элемент массива для "проталкивания"
  Element e = array[size];

  // Цикл "проталкивания": current - индекс текущего элемента
  int current = 0;
  for (;;) {
    // максимальный из индексов потомков текущего элемента:
    int elder = 2*(current + 1);

    // Если потомков нет, то "проталкивание" прекращается:
    if (size < elder) break; else
    // Если потомок только один, то его индекс на единицу меньше
    if (size == elder) {
      elder--;
    // Если потомков два, то выбираем индекс элемента с меньшим значением
    } else {
      if (array[elder-1] < array[elder]) elder--;
    }

    // Сравниваем текущий элемент с минимальным из потомков
    // и продвигаем его вниз, если необходимо
    if (e <= array[elder]) break;
    array[current] = array[elder];
    current = elder;
  }
  // "Проталкиваемый" элемент помещается на свое место:
  array[current] = e;
}

//==============================================================
// Доступ к минимальному элементу - первому элементу массива
//==============================================================
template <class Element>
Element & ArrayHeap<Element>::operator *() throw(HeapUnderflow) {
  if (size == 0) throw HeapUnderflow();
  return *array; 
}

template <class Element>
const Element & ArrayHeap<Element>::operator *() const throw(HeapUnderflow) {
  if (size == 0) throw HeapUnderflow();
  return *array;
}

//==============================================================
// Добавление нового элемента в массив: новый элемент помещается
// в конец массива и затем "проталкивается" наверх,
// пока не займет свое место
//==============================================================
template <class Element>
Heap<Element> & ArrayHeap<Element>::operator += (const Element & newElem) throw(HeapOverflow) {
  // Проверка свободного места в массиве:
  if (size == maxSize) throw HeapOverflow();
  // Цикл проталкивания начинается с конца массива
  int current = size++;
  while (current > 0) {
    // Индекс предка текущего элемента
    int next = (current-1) / 2;
    if (array[next] > newElem) {
      // Элемент-предок спускается вниз
      array[current] = array[next];
      current = next;
    } else {
      // "Проталкивание" закончено
      break;
    }
  }
  // Новый элемент занимает свое место
  array[current] = newElem;
  return *this;
}

#endif
