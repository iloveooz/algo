/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.2. Списки                                         *
*                                                              *
*  Автор    : A.Кубенский                                      *
*  Файл     : IntList.h                                        *
*  Описание : Список целых: определение класса                 *
***************************************************************/

#ifndef __INT_LIST
#define __INT_LIST

#include <stdlib.h>

//**************************************************************
// Класс IntList
//**************************************************************

class IntList {
/* класс ListItem представляет элемент списка, связанный со 
   следующим с помощью поля next
*/
  struct ListItem {
    int item;         // значение элемента списка
    ListItem *next;   // указатель на следующий элемент списка

    // Конструктор для создания нового элемента
    ListItem(int i, ListItem *n = NULL) { item = i; next = n; }
  };

  int count;             // счетчик числа элементов
  ListItem *first;       // первый элемент списка
  ListItem *last;        // последний элемент списка

public :

  // Конструктор "по умолчанию" - создание пустого списка
  IntList() { count = 0; first = last = NULL; }

  // Конструктор "копирования" – создание копии имеющегося списка
  IntList(const IntList & src);

  // Деструктор списка
  ~IntList();

  // Доступ к первому элементу списка
  int head() const { return first->item; }
  int & head() { return first->item; }

  // Доступ к последнему элементу списка
  int tail() const { return last->item; }
  int & tail() { return last->item; }

  // Добавить элементы в конец списка
  void addLast(const IntList & src);

  // Добавить один элемент в начало списка
  void addFirst(int item);

  // Добивать один элемент в конец списка
  void addLast(int item);

  // Удалить первый элемент 
  int removeFirst();

  // Удаление заданного элемента
  bool remove(int n);

  // Searching and removing an element
  void insert(int n);

  // количество элементов списка
  int getCount() { return count; }

  // Printing all the elements to the standard output stream
  void printAll();
};    // Конец определения класса IntList

#endif
