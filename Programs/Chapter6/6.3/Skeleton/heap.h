/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.3. Определение остовных деревьев                  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : heap.h                                           *
*  Описание : Определение абстрактной пирамиды из элементов    *
***************************************************************/

#ifndef __HEAP_H
#define __HEAP_H

#include <exception>

using namespace std;

//==============================================================
// Классы HeapOverflow и HeapUnderflow определяют две
// исключительные ситуации, которые могут возникнуть при
// выполнении операции добавления элемента в пирамиду
// (HeapOverflow - переполнение) и удаления минимального
// элемента (HeapUnderflow - исчерпание).
//==============================================================

class HeapOverflow : public exception {
  char * reason;
public :
  HeapOverflow(char * message = "Heap overflow!") : reason(message) {}
  const char * what() const throw() { return reason; }
};

class HeapUnderflow : public exception {
  char * reason;
public :
  HeapUnderflow(char * message = "Heap underflow!") : reason(message) {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// Шаблон классов Heap определяет абстрактный интерфейс
// пирамиды: операции добавления нового элемента, доступ к
// минимальному элементу и его удаление из пирамиды.
// Все операции над пирамидой определены
// как абстрактные (чистые) функции.
//==============================================================

template <class Element>
class Heap {
public :
  // Удаление минимального элемента:
  virtual void remove() throw(HeapUnderflow) = 0;

  // Доступ к минимальному элементу:
  virtual Element & operator *() throw(HeapUnderflow) = 0;
  virtual const Element & operator *() const throw(HeapUnderflow) = 0;

  // Добавление нового элемента в пирамиду:
  virtual Heap<Element> & operator += (const Element & newElem) throw(HeapOverflow) = 0;

  // Проверка наличия элементов в пирамиде:
  virtual bool empty() const = 0;
};

#endif
