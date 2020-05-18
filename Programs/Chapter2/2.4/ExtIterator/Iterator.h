/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.4. Итераторы                                      *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : Iterator.h                                    *
*  Описание    : Описание абстрактного итератора               *
***************************************************************/

#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <stdlib.h>

//**************************************************************
// Описание класса Iterator
//**************************************************************

template <class Element>
class Iterator {
public :
  virtual ~Iterator() {}
  virtual bool hasMoreElements() const = 0;
  virtual void nextElement() = 0;
  virtual const Element & getCurrent() const = 0;
  virtual Element & getCurrent() = 0;
  virtual void remove() = 0;
};

#endif
