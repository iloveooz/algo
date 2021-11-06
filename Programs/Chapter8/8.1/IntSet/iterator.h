/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.1. Еще о представлении множеств                   *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : iterator.h                                    *
*  Описание    : Описание абстрактного итератора               *
***************************************************************/

#ifndef __ITERATOR_H
#define __ITERATOR_H

template <class Element>
class Iterator {
public :
  virtual ~Iterator() {}
  virtual bool hasMoreElements() const = 0;
  virtual Iterator<Element> & operator ++() = 0;
  virtual Element operator *() = 0;
};

#endif
