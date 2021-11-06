/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.3. Словари, представленные списками и деревьями   *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : pair.h                                           *
*  Описание : Пара из ключа и значения, допускающая сравнение  *
*             по ключу                                         *
***************************************************************/

#ifndef __PAIR_H
#define __PAIR_H

#include <string>

using namespace std;

//==============================================================
// Класс Pair представляет элемент списка слов - пару из слова
// и связанного с ним объекта. Для сравнения пар предоставляются
// операторы сравнения, которые фактически сравнивают только
// первые элементы пар - слова.
//==============================================================

template <class Object>
struct Pair {
  string key;    // Ключ
  Object obj;    // Связанный объект

  // Конструкторы
  Pair() {}
  Pair(const string & _key) : key(_key) {}
  Pair(const string & _key, const Object & _obj) : key(_key), obj(_obj) {}
  Pair(const Pair & pair2) : key(pair2.key), obj(pair2.obj) {}

  // Оператор присваивания
  Pair<Object> & operator = (const Pair<Object> & src) {
    key = src.key;  obj = src.obj;
    return *this;
  }

  // Операторы сравнения:

  bool operator == (const Pair<Object> & pair2) const {
    return key == pair2.key;
  }

  bool operator != (const Pair<Object> & pair2) const {
    return key != pair2.key;
  }

  bool operator < (const Pair<Object> & pair2) const {
    return key < pair2.key;
  }

  bool operator <= (const Pair<Object> & pair2) const {
    return key <= pair2.key;
  }

  bool operator > (const Pair<Object> & pair2) const {
    return key > pair2.key;
  }

  bool operator >= (const Pair<Object> & pair2) const {
    return key >= pair2.key;
  }
};

#endif
