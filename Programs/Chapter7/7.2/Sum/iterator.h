/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.2. Об одном способе вычисления конечных сумм      *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : Iterator.h                                    *
*  Описание    : Описание абстрактного итератора с удалением   *
*                элементов                                     *
***************************************************************/

#ifndef __ITERATOR_H
#define __ITERATOR_H

template <class Element>
class Iterator {
public :
  virtual ~Iterator() {}
  virtual bool hasMoreElements() const = 0;
  virtual Iterator<Element> & operator ++() = 0;
  virtual const Element & operator *() const = 0;
  virtual Element & operator *() = 0;
  virtual void remove() {}
};

#endif
