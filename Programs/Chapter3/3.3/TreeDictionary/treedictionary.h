/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.3. Словари, представленные списками и деревьями   *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : treedictionary.h                              *
*  Описание    : Словарь, реализованный в виде бинарного       *
*                дерева поиска                                 *
***************************************************************/

#ifndef __TREE_DICTIONARY_H
#define __TREE_DICTIONARY_H

#include <string>
#include "tree.h"
#include "pair.h"

using namespace std;

//==============================================================
// Определение шаблона TreeDictionary основано на бинарном
// дереве поиска, содержащем в узлах пары из строкового ключа и
// связанного с ним значения.
//==============================================================

template <class Object>
class TreeDictionary {
  // Дерево tree содержит упорядоченный список пар
  Tree<Pair<Object> > tree;

public :
  // Функция добавляет в дерево новую пару
  void add(string key, const Object & obj) {
    tree.insertLeaf(Pair<Object>(key, obj));
  }

  // Функция осуществляет поиск пары по ключу и удаляет
  // найденную пару, если она в списке была
  void remove(string key) {
    tree.remove(Pair<Object>(key));
  }

  // Функция поиска связанного объекта по ключу
  Object * find(string key) const {
    Pair<Object> * found = tree.search(Pair<Object>(key));
    return found ? &found->obj : NULL;
  }

  // Функция выдает внешний итератор пар, используя внешний
  // итератор упорядоченного списка
  Iterator<Pair<Object> > * iterator() const {
    return tree.iterator();
  }
};

#endif
