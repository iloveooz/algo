/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.2. Поиск кратчайших путей                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : listqueue.h                                      *
*  Описание : Шаблон классов для реализации очереди в виде     *
*             списка элементов.                                *
***************************************************************/

#ifndef __LIST_QUEUE_H
#define __LIST_QUEUE_H

#include "queue.h"
#include "queuefactory.h"
#include "circularlist.h"

//==============================================================
// Определение класса основано на представлении очереди в виде 
// циклического списка элементов очереди.
//==============================================================

template<class T>
class ListQueue : public Queue<T> {
  CircularList<T> list;    // Базовый список

public :

  // Конструктор "по умолчанию" создает пустую очередь
  ListQueue() : list() {}

  // Конструктор "копирования" использует операцию присваивания списков
  ListQueue(const ListQueue & src) { list = src.list; }

  // Виртуальный деструктор
  virtual ~ListQueue() {}

  // Добавление нового элемента происходит в конец кольцевого списка
  void enqueue(const T & item) { 
    list.insertTail(item); 
  }

  // Удаление элемента из списка
  void dequeue();

  // Проверка пустоты очереди сводится к проверке пустоты списка
  bool empty() const { return list.empty(); }

  // Функции доступа к голове и хвосту очереди
  T & head();
  const T & head() const;
  T & tail();
  const T & tail() const;
};

// Функции, не определенные "inline", "переименовывают" 
// исключительную ситуацию, возникающую при обработке списка, 
// в ситуацию, естественную для операций с очередью.

template <class T>
void ListQueue<T>::dequeue() {
  try {
    list.removeHead();
  } catch (EmptyException) {
    throw QueueUnderflow();
  }
}

template <class T>
T & ListQueue<T>::head() {
  try {
    return list.head();
  } catch (EmptyException) {
    throw QueueUnderflow();
  }
}

template <class T>
const T & ListQueue<T>::head() const {
  try {
    return list.head();
  } catch (EmptyException) {
    throw QueueUnderflow();
  }
}

template <class T>
T & ListQueue<T>::tail() {
  try {
    return list.tail();
  } catch (EmptyException e) {
    throw QueueUnderflow();
  }
}

template <class T>
const T & ListQueue<T>::tail() const {
  try {
    return list.tail();
  } catch (EmptyException e) {
    throw QueueUnderflow();
  }
}

//==============================================================
// Фабрика порождения очередей типа ListQueue наследует
// абстрактной фабрике очередей QueueFactory
//==============================================================

template <class T>
class ListQueueFactory : public QueueFactory<T> {
public:
  // Аргумент игнорируется.
  Queue<T> *newQueue(int size = 100) { return new ListQueue<T>; }
};

#endif
