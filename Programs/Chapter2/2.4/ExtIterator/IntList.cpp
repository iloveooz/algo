/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.4. Итераторы                                      *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : IntList.cpp                                   *
*  Описание    : Список целых: реализация методов класса       *
***************************************************************/

#include "IntList.h"

// Деструктор списка: все элементы списка уничтожаются
IntList::~IntList() {
  ListItem *current = NULL;  // Элемент, подлежащий уничтожению
  ListItem *next = first;    // Следующий элемент
  while (next) {
    current = next;     // запоминаем ссылку для уничтожения элемента
    next = next->next;  // переходим к следующему элементу
    delete current;     // уничтожаем текущий элемент
  }
}

  // Добавление элемента в конец списка
void IntList::addLast(int item) {
  // Создание нового элемента списка
  ListItem *newItem = new ListItem(item);
  if (!last) {
    // Новый элемент - первый (и единственный) в списке
    first = newItem;
  } else {
    // Присоединяем новый элемент к концу списка
    last->next = newItem;
  }
  // Новый элемент - последний в списке
  last = newItem;
  count++;
}
