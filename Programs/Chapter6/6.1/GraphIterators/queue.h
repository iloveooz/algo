/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.1. Обходы и поиск в графах                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : queue.h                                          *
*  Описание : Шаблон классов для определения абстрактной       *
*             очереди                                          *
***************************************************************/

#ifndef __QUEUE_H
#define __QUEUE_H

#include <exception>

using namespace std;

//==============================================================
// Классы QueueOverflow и QueueUnderflow представляют два
// основных источника исключительных ситуаций, возникающих
// при работе с очередью.
//==============================================================

class QueueOverflow : public exception {
  char * reason;
public:
  QueueOverflow() : reason("Queue Overflow") {}
  const char * what() const throw() { return reason; }
};

class QueueUnderflow : public exception {
  char * reason;
public:
  QueueUnderflow() : reason("Queue Underflow") {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// Шаблон классов Queue представляет понятие абстрактной очереди.
//==============================================================

template <class T>
class Queue {
public:
  // Виртуальный деструктор, нужный для его переопределения в классах-потомках
  virtual ~Queue() {}

  // Абстрактные операции с очередью.

  // Добавление нового элемента в очередь.
  virtual void enqueue(const T & e) = 0;

  // Удаление головного элемента. 
  // Исключительная ситуация QueueUnderflow может возникнуть,
  // если в очереди нет элементов.
  virtual void dequeue() = 0;

  // Проверка пустоты очереди
  virtual bool empty() const = 0;

  // Функции доступа на чтение и/или запись головного и/или хвостового элементов.
  virtual T & head() = 0;
  virtual const T & head() const = 0;
  virtual T & tail() = 0;
  virtual const T & tail() const = 0;
};

#endif
