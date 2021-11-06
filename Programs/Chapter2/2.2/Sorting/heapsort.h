/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.2. Сортировка и поиск в массивах                  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : heapsort.h                                       *
*  Описание : Функции сортировки элементов массива методом     *
*             пирамидальной сортировки                         *
***************************************************************/

#ifndef __HEAP_SORT_H
#define __HEAP_SORT_H

//-------------------------------------------------------------
// Шаблон heapSort задает функцию сортировки элементов
// массива методом пирамидальной сортировки.
//   - Key - класс, задающий тип элементов массива;
//   - array - упорядочиваемый массив;
//   - low, high - индексы, задающие диапазон сортировки;
//-------------------------------------------------------------

template <class Key>
void heapSort(Key * array, int low, int high) {
  // Предполагается, что в начале работы low <= high
  // В результате сортировки получается упорядоченный фрагмент
  // массива в диапазоне от low до high
  int heapLength = 1;

  // 1. Выстраивание пирамиды
  while (heapLength <= high-low) {
    // Элемент с индексом low+heapLength включается в пирамиду
    int ndx = low + heapLength;
    Key elem = array[ndx];
    while (ndx > low && elem > array[(ndx-low-1)/2]) {
      array[ndx] = array[(ndx-low-1)/2];
      ndx = (ndx-low-1)/2;
    }
    array[ndx] = elem;
    heapLength++;
  }

  // 2. Упорядочивание элементов
  while (heapLength > 1) {
    heapLength--;
    Key elem = array[low + heapLength];
    array[low + heapLength] = array[low];
    int ndx = low;
    while (2*(ndx-low) < heapLength-1) {
      int child1 = low + 2*(ndx-low) + 1,
          child2 = low + 2*(ndx-low) + 2;
      if (child2 <= low + heapLength - 1 &&
          array[child2] > array[child1]) {
        child1 = child2;
      }
      if (elem > array[child1]) break;
      array[ndx] = array[child1];
      ndx = child1;
    }
    array[ndx] = elem;
  }
}

#endif
