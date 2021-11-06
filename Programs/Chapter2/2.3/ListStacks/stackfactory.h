/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.2. Стеки и очереди                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : stackfactory.h                                   *
*  Описание : Класс, определяющий абстрактную фабрику стеков   *
***************************************************************/

#ifndef __STACK_FACTORY_H
#define __STACK_FACTORY_H

#include "stack.h"

//==============================================================
// Класс StackFactory - это абстрактный класс для создания
// абстрактных стеков. Аргумент "виртуального конструктора"
// задает максимальный размер для ограниченных стеков
//==============================================================

template <class T>
class StackFactory {
public:
  // "Виртуальный конструктор стеков" - чистая функция
  virtual Stack<T> *newStack(int size = 100) = 0;
};

#endif
