/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.1. Абстрактная система распределения памяти       *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : digitsort.h                                      *
*  Описание : Функции сортировки элементов массива методом     *
*             цифровой сортировки                              *
***************************************************************/

#ifndef __DIGIT_SORT_H
#define __DIGIT_SORT_H

#include <alloc.h>

template <class Key>
struct Elem;

//==============================================================
// Класс ListBuffer представляет буферный пул памяти для 
// организации в нем списков ключей (для цифровой сортировки).
//==============================================================
template <class Key>
class ListBuffer {
  Elem<Key> * buffer;   // Указатель на буфер
  int size;             // Размер буфера
  int freePtr;          // Указатель первого свободного элемента

  static ListBuffer<Key> * singleton;

  // Конструктор:
  ListBuffer(int n) {
    buffer = (Elem<Key>*)calloc(size = n, sizeof(Elem<Key>));
    clear();
  }

public :

  static ListBuffer<Key> * getInstance() {
    return singleton;
  }

  static void setNewBuffer(int n) {
    singleton = new ListBuffer<Key>(n);
  }

  // Деструктор:
  ~ListBuffer() { free(buffer); }

  // Очистка памяти.
  void clear() {
    freePtr = 0;
  }

  // Операция выделения элемента свободной части буфера
  Elem<Key> * get() {
    return & buffer[freePtr++];
  }
};

template <class Key>
ListBuffer<Key> * ListBuffer<Key>::singleton = NULL;

//==============================================================
// Класс Elem представляет элемент списка ключей,
// формируемого для выполнения цифровой сортировки.
//==============================================================
template <class Key>
struct Elem {
  Key value;         // Сам элемент
  Elem<Key> * next;  // Указатель следующего элемента в пуле памяти
  
  // Конструкторы:
  Elem() { next = NULL; }   // По умолчанию следующий элемент остутствует
  Elem(const Elem<Key> & src) : value(src.value), next(src.next) {}
  Elem(const Key & val, Elem<Key> * n = NULL) : value(val), next(n) {}

  // Оператор присваивания:
  Elem<Key> & operator = (const Elem<Key> & src) {
    value = src.value; next = src.next;
    return *this;
  }

  // Запрос памяти
  void * operator new(size_t sz) {
    return ListBuffer<Key>::getInstance()->get();
  }
};

//==============================================================
// Класс KeyList представляет список ключей, хранящийся в
// буферном пуле памяти.
//==============================================================
template <class Key>
class KeyList {
  Elem<Key> * first;    // Указатель на первый элемент списка
  Elem<Key> * last;     // Указатель на послений элемент списка

public :

  // Конструктор
  KeyList() : first(NULL), last(NULL) {}

  // Операция добавления нового элемента в конец списка
  void addKey(const Key & key) {
    // Запрашиваем свободный элемент у пула памяти
    Elem<Key> * newElem = new Elem<Key>(key);
    // Присоединяем новый элемент к уже имеющемуся списку
    if (first == NULL) {
      first = newElem;
    } else {
      last->next = newElem;
    }
    last = newElem;
  }

  // Операция toArray переносит все элементы списка во фрагмент
  // массива array, начиная с элемента с индексом from.
  // В качестве результата функция выдает индекс первого элемента
  // массива, следующего за перенесенным фрагментом
  int toArray(Key * array, int from) {
    // Организуем просмотр элементов с помощью указателя ptr.
    Elem<Key> * ptr = first;
    while (ptr != NULL) {
      array[from++] = ptr->value;
      ptr = ptr->next;
    }
    return from;
  }

  // Функция очистки списка просто "заземляет" указатели
  // на первый и последний элементы списка.
  void clear() { first = last = NULL; }
};

//-------------------------------------------------------------
// Шаблон digitSort задает функцию сортировки элементов
// массива методом цифровой сортировки.
//   - Key - класс, задающий тип элементов массива;
//   - array - упорядочиваемый массив;
//   - low, high - индексы, задающие диапазон сортировки;
//-------------------------------------------------------------

template <class Key>
void digitSort(Key * array, int low, int high) {
  // Предполагается, что в начале работы low <= high
  // В результате сортировки получается упорядоченный фрагмент
  // массива в диапазоне от low до high
  int n = high - low + 1;               // Длина массива
  int listNumber = array[low].power();  // Количество списков ключей
  int passes = array[low].length();     // Количество проходов по массиву

  ListBuffer<Key>::setNewBuffer(n);

  // Организуем массив списков ключей:
  KeyList<Key> * lists = new KeyList<Key>[listNumber];

  // Цикл по проходам по массиву (digit - номер "цифры"):
  for (int digit = passes-1; digit >= 0; digit--) {
    // Помещение ключей из массива в соответствующие списки
    for (int i = low; i <= high; i++) {
      lists[array[i][digit]].addKey(array[i]);
    }
    // Обратное слияние списков в массив и очищение списков
    int start = low;
    for (int i = 0; i < listNumber; i++) {
      start = lists[i].toArray(array, start);
      lists[i].clear();
    }
    // Очистка буфера
    ListBuffer<Key>::getInstance()->clear();
  }
}

#endif
