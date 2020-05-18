/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.2. Списки                                         *
*                                                              *
*  Автор    : A.Кубенский                                      *
*  Файл     : IntList.cpp                                      *
*  Описание : Список целых: реализация методов класса          *
***************************************************************/

#include <iostream>
#include "IntList.h"

using namespace std;

// Реализация конструктора копирования
IntList::IntList(const IntList & src) {
  count = 0;
  first = last = NULL;
  addLast(src);   // добавляет список src в конец списка this
}

// Реализация деструктора
IntList::~IntList() {
  ListItem *current = NULL; // указатель на элемент, подлежащий удалению
  ListItem *next = first;   // указатель на следующий элемент
  while (next) {            // пока есть еще элементы в списке
    current = next;
    next = next->next;      // переход к следующему элементу
    delete current;         // освобождение памяти
  }
}

// Добавление элементов заданного списка в конец определяемого
void IntList::addLast(const IntList & src) {
  for (ListItem *cur = src.first; cur;  cur = cur->next)
    addLast(cur->item);  // добавление одного элемента – см. ниже
}

// Добавление одного элемента в начало списка
void IntList::addFirst(int item) {
  // создаем новый элемент списка
  ListItem *newItem = new ListItem(item, first);
  if (!first) {
    // список был пуст – новый элемент будет и первым, и последним
    last = newItem;
  }
  first = newItem;
  count++;    // число элементов списка увеличилось.
}

// Добавление одного элемента в конец списка
void IntList::addLast(int item) {
  // создаем новый элемент списка
  ListItem *newItem = new ListItem(item);
  if (!last) {
    // список был пуст – новый элемент будет и первым, и последним
    first = newItem;
  } else {
    // новый элемент присоединяется к последнему элементу списка
    last->next = newItem;
  }
  last = newItem;
  count++;    // число элементов списка увеличилось.
}

// Удаление первого элемента из списка
int IntList::removeFirst() {
  int res = first->item;  // содержимое первого элемента
  first = first->next;    // второй элемент становится первым
  count--;                // число элементов списка уменьшилось
  return res;   // удаленный элемент возвращается в качестве результата
}

// Удаление заданного элемента
bool IntList::remove(int n) {
  ListItem *pred = 0,         // указатель на предыдущий элемент
           *current = first;  // указатель на текущий элемент
  while (current) {
    if (current->item == n) {
      if (pred) {            // корректируем ссылку на удаляемый элемент
        pred->next = current->next;
      }
      if (current == last) { // удаляется последний элемент
        last = pred;         // корректируем ссылку на последний элемент
      }
      delete current;        // освобождаем память
      count--;               // уменьшаем количество элементов
      return true;
    } else {                 // переходим к следующему элементу
      pred = current;
      current = current->next;
    }
  }
  // удаляемый элемент не найден
  return false;
}

// Вставка нового элемента в упорядоченный список
void IntList::insert(int n) {
  ListItem *pred = NULL,    // элемент, предшествующий вставляемому
           *succ = first;   // элемент, следующий за вставляемым
  while (succ != NULL && succ->item < n) { // поиск места вставки
    pred = succ; 
    succ = succ->next;
  }
  // генерируем новый элемент:
  ListItem *newItem = new ListItem(n, succ);
  if (succ == NULL) {      // вставляемый элемент – последний
    last = newItem;
  }
  // вставляем новый элемент в список
  if (pred == NULL) {
    first = newItem; 
  } else {
    pred->next = newItem;
  }
  count++;
}

// Вывод элементов списка в текстовом виде в стандартный выходной поток
void IntList::printAll() {
  ListItem *current = first;  // Указатель на элемент
  while (current) {
    cout << current->item << ' ';
    current = current->next;  // Переход к следующему элементу
  }
  cout << endl;
}
