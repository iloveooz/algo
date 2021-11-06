/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.3. Стеки и очереди                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : list.h                                           *
*  Описание : Определение шаблона для связанного списка        *
*             элементов                                        *
***************************************************************/

#ifndef __LIST_H
#define __LIST_H

#include <stdlib.h>

//**************************************************************
// Шаблон классов List. Исключительные ситуации в этом примере
// для простоты игнорируются.
//**************************************************************

template <class T>
class List {

/* Структура ListItem - это класс, представляющий одно звено списка,
   связанное со следующим звеном указателем 'next'.
*/
  struct ListItem {
    T item;           // Элемент списка
    ListItem *next;   // Указатель на следующий элемент
    // Конструктор 
    ListItem(const T & i, ListItem *n = NULL) { item = i; next = n; }
  };

  int count;             // Счетчик числа элементов
  ListItem *first;       // Указатель на первый элемент
  ListItem *last;        // Указатель на последний элемент

public:

  // Конструктор "по умолчанию" создает пустой список
  List() : count(0), first(NULL), last(NULL) {}

  // Конструктор копирования создает копию списка-аргумента
  List(const List<T> & src) { *this = src; }

  // Деструктор списка
  virtual ~List() { destroy(); }

  // Доступ к голове списка
  T & head();
  const T & head() const;

  // Доступ к концу списка
  T & tail();
  const T & tail() const;

  // Добавление элементов из списка к концу данного
  List<T> & operator = (const List<T> & src);

  // Добавление элемента в голову списка
  void addFirst(const T & item);

  // Добавление элемента в конец списка
  void addLast(const T & item);

  // Удаление элемента из головы списка
  void remove();

  // Количество элементов списка
  int getCount() const { return count; }

protected:

  // Уничтожение элементов списка
  virtual void destroy();
};

// Функции доступа к голове списка
template <class T>
T & List<T>::head() {
  return first->item; 
}

template <class T>
const T & List<T>::head() const {
  return first->item; 
}

// Функции доступа к концу списка
template <class T>
T & List<T>::tail() {
  return last->item; 
}

template <class T>
const T & List<T>::tail() const {
  return last->item; 
}

// Опреатор присваивания разрушает текущий список и
// добавляет все элементы аргумента в конец этого списка
template <class T>
List<T> & List<T>::operator = (const List<T> & src) {
  destroy();
  for (ListItem *cur = src.first; cur;  cur = cur->next) {
    // каждый элемент добавляется с помощью метода addLast
    addLast(cur->item);
  }
  return *this;
}

// Добавление элемента в голову списка
template <class T>
void List<T>::addFirst(const T & item) {
  // Создание элемента
  ListItem *newItem = new ListItem(item, first);
  if (!first) {
    // Новый элемент - единственный
    last = newItem;
  }
  first = newItem;
  count++;
}

// Добавление элемента в конец списка
template <class T>
void List<T>::addLast(const T & item) {
  // Создание элемента
  ListItem *newItem = new ListItem(item);
  if (!last) {
    // Новый элемент - единственный
    first = newItem;
  } else {
    // Новый элемент - присоединяется к концу списка
    last->next = newItem;
  }
  last = newItem;
  count++;
}

// Удаление первого элемента
template <class T>
void List<T>::remove() {
  ListItem *itemToDelete = first;
  first = first->next;    // второй элемент становится первым
  count--;
  delete itemToDelete;
}

// Уничтожение списка: все элементы необходимо разрушить
template <class T>
void List<T>::destroy() {
  ListItem *current = NULL;  // Ссылка на элемент, подлежащий уничтожению
  ListItem *next = first;    // Ссылка на следующий элемент
  while (next) {
    current = next;     // этот элемент будет уничтожен
    next = next->next;  // перейти к следующему элементу
    delete current;     // уничтожить текущий элемент
  }
  count = 0;
  first = last = NULL;
}

#endif
