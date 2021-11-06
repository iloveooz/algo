/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.3. Словари, представленные списками и деревьями   *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : sortedlist.h                                     *
*  Описание : Упорядоченный список объектов                    *
***************************************************************/

#ifndef __SORTED_LIST_H
#define __SORTED_LIST_H

#include "iterator.h"
#include "actor.h"

//=============================================================
// Класс SortedList представляет упорядоченный по возрастанию
// список произвольных объектов. Сравнение объектов производится
// согласно предоставляемым ими операторам сравнения объектов
//=============================================================

template <class Object>
class SortedList {

private :

  // Элемент списка состоит из объекта и ссылки на следующий элемент
  struct ListElem {
    Object item;       // Значение элемента списка
    ListElem *next;    // Ссылка на следующий элемент

    // Простой конструктор
    ListElem(const Object & i, ListElem * n = NULL) : item(i), next(n) {}
  };

  // Список представлен ссылкой на первый элемент...
  ListElem * first;
  // ...и счетчиком числа элементов
  int count;

  // Внутренний класс ForwardIterator реализует внешний итератор списка
  class ForwardIterator : public Iterator<Object> {
    // Ссылка на текущий элемент:
    ListElem * current;

  public :
    // Конструктор устанавливает указатель на первый элемнент списка
    ForwardIterator(SortedList<Object> * sl) : current(sl->first) {}

    // Итерация оканчивается, когда текущий указатель содержит пустую ссылку
    bool hasMoreElements() const { return current != NULL; }

    // Операция сдвига итеатора сводится к перемещению указателя на
    // следующий элемент списка
    Iterator<Object> & operator ++() {
      if (current) current = current->next;
      return *this;
    }

    // Доступ к итерируемому элементу - это доступ 
    // по текущему значению указателя в список
    Object & operator *() {
      if (current == NULL) throw "No more elements";
      return current->item;
    }
  };

  friend class ForwardIterator;

public :

  // Конструкторы
  SortedList() : first(NULL), count(0) {}
  SortedList(const SortedList & src) : first(NULL), count(0) {
    *this = src;
  }

  // Деструктор
  ~SortedList() { destroy(); }

  // число элементов списка
  int getCount() { return count; }

  // удалить все элементы, равные заданному
  bool remove(const Object & item);

  // вставить элемент в упорядоченный список
  void insert(const Object & item);

  // поиск первого элемента, равного заданному
  Object * find(const Object & item);

  // внешний итератор списка
  Iterator<Object> * iterator() { return new ForwardIterator(this); }

  // внутренний итератор списка
  void iterator(Actor<Object> & actor);

private :
  void destroy();
};

// Реализация методов для работы со списком

// удалить все элементы, равные заданному
template <class Object>
bool SortedList<Object>::remove(const Object & item) {
  ListElem ** current = &first;
  while (*current && item > (*current)->item) {
    current = &(*current)->next;
  }
  bool deleted = false;
  while (*current && item == (*current)->item) {
    ListElem *toDelete = *current;
    *current = (*current)->next;
    delete toDelete;
    deleted = true;
    count--;
  }
  return deleted;
}

template <class Object>
void SortedList<Object>::insert(const Object & item) {
  ListElem ** current = &first;
  while (*current && item > (*current)->item) {
    current = &(*current)->next;
  }
  *current = new ListElem(item, *current);
  count++;
}

template <class Object>
Object * SortedList<Object>::find(const Object & item) {
  ListElem * current = first;
  while (current && item > current->item) {
    current = current->next;
  }
  if (current && item == current->item) {
    return &current->item;
  } else {
    return NULL;
  }
}

template <class Object>
void SortedList<Object>::iterator(Actor<Object> & actor) {
  ListElem * current = first;
  while (current) {
    actor.action(current->item);
    current = current->next;
  }
}

template <class Object>
void SortedList<Object>::destroy() {
  ListElem * current = first;
  ListElem * pred;
  while (current) {
    pred = current;
    current = current->next;
    delete pred;
  }
  count = 0;
}

#endif
