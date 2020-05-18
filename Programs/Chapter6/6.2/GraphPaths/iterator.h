/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.2. Поиск кратчайших путей                         *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : Iterator.h                                    *
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
  virtual const Element & operator *() const = 0;
};

#endif
