/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.3. Словари, представленные списками и деревьями   *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : actor.h                                          *
*  Описание : Интерфейс, определяющий действие, выполняемое    *
*             при внутренней итерации некоторой структуры      *
***************************************************************/

#ifndef __ACTOR_H
#define __ACTOR_H

//==============================================================
// Класс, представляющий действие, выполняемое при внутренней
// итерации структуры
//==============================================================

template <class Object>
class Actor {
public :
  // Виртуальное действие над элементом
  virtual void action(Object &) = 0;
};

#endif
