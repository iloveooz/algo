/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.3. Стеки и очереди                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : liststack.h                                      *
*  Описание : Реализация стека в виде связанного списка        *
*             элементов                                        *
***************************************************************/

#ifndef __LIST_STACK_H
#define __LIST_STACK_H

#include "list.h"            // Определение списка
#include "stack.h"           // Определение абстрактного стека
#include "stackfactory.h"    // Определение абстрактной "фабрики" стеков

//==============================================================
// Шаблон классов ListStack - это реализация абстрактного
// стека в виде связанного списка элементов стека.
//==============================================================

template <class T>
class ListStack : public Stack<T> {
  // Представление стека - список элементов типа Т
  List<T> stack;

public:

  // Конструкторы стека.

  // Конструктор "по умолчанию" создает пустой список:
  ListStack() : stack() {}

  // Конструктор копирования копирует список
  ListStack(const ListStack & stk) : stack(stk.stack) {}

  // Реализация абстрактной функции записи в стек: 
  // новый элемент присоединяется к началу списка
  void push(const T & e) { stack.addFirst(e); }

  // Реализация абстрактной функции выталкивания из стека: 
  // элемент удаляется из начала списка
  void pop();

  // Реализация функции проверки стека на пустоту
  bool empty() { return stack.getCount() == 0; }

  // Реализация функции доступа к вершине стека: 
  // доступ осуществляется к первому элементу списка.
  T & top();
  const T & top() const;
};

template <class T>
void ListStack<T>::pop() {
  try {
    // удаление элемента из головы списка
    stack.remove(); 
  } catch (...) {
    // Попытка доступа к значению по пустому указателю вызывает
    // исключительную ситуацию StackUnderflow
    throw StackUnderflow();
  }
}

template <class T>
T & ListStack<T>::top() {
  try {
    // доступ к первому элементу списка
    return stack.head();
  } catch (...) {
    // Попытка доступа к значению по пустому указателю вызывает
    // исключительную ситуацию StackUnderflow
    throw StackUnderflow();
  }
}

template <class T>
const T & ListStack<T>::top() const {
  try {
    // доступ к первому элементу списка
    return stack.head();
  } catch (...) {
    // Попытка доступа к значению по пустому указателю вызывает
    // исключительную ситуацию StackUnderflow
    throw StackUnderflow();
  }
}

//==============================================================
// Фабрика стеков ListStackFactory реализует абстрактную фабрику
// стеков SatckFactory
//==============================================================

template <class T>
class ListStackFactory : public StackFactory<T> {
public:
  // Аргумент в данном случае игнорируется
  Stack<T> *newStack(int size = 100) { return new ListStack<T>(); }
};

#endif

