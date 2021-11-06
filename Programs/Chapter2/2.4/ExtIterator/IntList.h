/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.4. Итераторы                                      *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : IntList.h                                     *
*  Описание    : Список целых: описание класса                 *
***************************************************************/

#ifndef __INT_LIST_H
#define __INT_LIST_H

#include <stdlib.h>
#include <exception>
#include "Iterator.h"

using namespace std;

//**************************************************************
// Описание класса IntList
//**************************************************************

class IntList {
/* Структура ListItem представляет элемент списка, 
   связанный со следующим элементом с помощью указателя 'next'.
*/
  struct ListItem {
    int item;         // Элемент списка
    ListItem *next;   // Указатель на следующий элемент

    // Конструктор элемента ListItem
    ListItem(int i, ListItem *n = NULL) { item = i; next = n; }
  };

  int count;             // Счетчик числа элементов
  ListItem *first;       // Указатель на первый элемент
  ListItem *last;        // Указатель на последний элемент

public:

  // Конструктор "умолчания" создает пустой список
  IntList() { count = 0; first = last = 0; }

  // Деструктор списка
  ~IntList();

  // Number of elements - a simple inline function
  int getCount() { return count; }

  // Добавление элемента в конец списка
  void addLast(int item);

  // Класс для исключительной ситуации, связанной с отсутствием элемента в списке
  class NoListElement : public exception {
    char * reason;
  public :
    NoListElement(char * msg = "") : reason(msg) {}
    const char * what() const throw() { return reason; }
  };

  // Класс, представляющий внешний итератор списка
  class MyIterator : public Iterator<int> {
    ListItem * curPos;   // Текущая позиция в списке
    ListItem ** pred;    // Ссылка на место, где хранится 
                         // указатель на этот элемент

  public :
    // Конструктор
    MyIterator(IntList & list) { curPos = *(pred = &list.first); }

    // Реализация функций интерфейса
    bool hasMoreElements() const { return curPos != NULL; }

    void nextElement() { if (curPos) curPos = *(pred = &curPos->next); }

    const int & getCurrent() const { return curPos->item; }

    int & getCurrent() { return curPos->item; }

    void remove() {
      if (!curPos)
        throw NoListElement("remove: no current element");
      *pred = curPos->next;
      delete curPos;
      curPos = *pred;
    }

    void insertBefore(int newValue) {
      ListItem * newItem = new ListItem(newValue, curPos);
      curPos = *pred = newItem;
    }

    void insertAfter(int newValue) {
      if (!curPos)
        throw NoListElement("insertAfter: no current element");
      ListItem * newItem = new ListItem(newValue, curPos->next);
      curPos = *(pred = &newItem->next);
    }
  };

  friend class MyIterator;

  // Метод iterator() порождает и выдает внешний итератор для этого списка
  MyIterator * iterator() { return new MyIterator(*this); }
};

#endif
