/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.3. Стеки и очереди                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : stack.h                                          *
*  Описание : Определение абстрактного стека                   *
***************************************************************/

#ifndef __STACK_H
#define __STACK_H

#include <exception>

using namespace std;

//==============================================================
// Классы StackOverflow и StackUnderflow представляют две
// исключительные ситуации, могущие возникнуть при работе со стеками.
//==============================================================

class StackOverflow : public exception {
  char * reason;
public :
  StackOverflow() : reason("Stack Overflow") {}
  const char * what() const throw() { return reason; }
};

class StackUnderflow : public exception {
  char * reason;
public:
  StackUnderflow() : reason("Stack Underflow") {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// Шаблон классов Stack представляет понятие абстрактного стека
//==============================================================

template <class T>
class Stack {
public:
  // Виртуальный деструктор для переопределения его в классах-наследниках
  virtual ~Stack() {}

  // Операции над абстрактным стеком.

  // Добавление нового элемента на вершину стека.
  virtual void push(const T & e) = 0;

  // Удаление элемента с вершины стека. 
  // Ситуация StackUnderflow может возникнуть, если такого элемента нет
  virtual void pop() = 0;

  // Проверка пустоты стека
  virtual bool empty() = 0;

  // Функции доступа к верхнему элементу стека.
  virtual T & top() = 0;
  virtual const T & top() const = 0;
};

#endif
