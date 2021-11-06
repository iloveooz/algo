/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.4. Итераторы                                      *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : main.cpp                                      *
*  Описание    : Внешние итераторы списка целых:               *
*                тестирующая функция                           *
***************************************************************/

#include <iostream>
#include "Iterator.h"
#include "IntList.h"

using namespace std;

// Распечатка всех элементов списка
void printList(IntList & ls) {
  cout << "[";
  Iterator<int> *i = ls.iterator();
  for (; i->hasMoreElements(); i->nextElement()) {
    cout << i->getCurrent() << " ";
  }  
  cout << "]" << endl;
  delete i;
}

// Функция для подсчета среднего арифметического элементов списка
double average(IntList & list) {
  double sum = 0, count = 0;
  Iterator<int> *i = list.iterator();
  for (; i->hasMoreElements(); i->nextElement()) {
    sum += i->getCurrent();
    count++;
  }
  delete i;
  return sum / count;
}

// Подсчет количества элементов списка, равных заданному
int countElements(IntList & ls, const int value) {
  int count = 0;
  Iterator<int> *i = ls.iterator();
  for (; i->hasMoreElements(); i->nextElement()) {
    if (value == i->getCurrent()) count++;
  }
  delete i;
  return count;
}

// Подсчет максимального количества совпадающих элементов списка
int maxEqualElements(IntList & ls) {
  int max = 0;
  Iterator<int> *i = ls.iterator();
  for (; i->hasMoreElements(); i->nextElement()) {
    int current = countElements(ls, i->getCurrent());
    if (current > max) max = current;
  }
  delete i;
  return max;
}

// Удаление из списка всех элементов, равных заданному
void removeElements(IntList & ls, const int el) {
  Iterator<int> *i = ls.iterator();
  while (i->hasMoreElements()) {
    if (el == i->getCurrent())
      i->remove();
    else
      i->nextElement();
  }
  delete i;
}

// Вставка нового значения в упорядоченный список
void insert(IntList & ls, const int val) {
  IntList::MyIterator *i = ls.iterator();
  for (; i->hasMoreElements() && i->getCurrent() < val; i->nextElement()) ;
  if (i->hasMoreElements())
    i->insertBefore(val);
  else
    ls.addLast(val);
  delete i;
}

// Сортировка списка пузырьком
IntList * bubbleSort(IntList & ls) {
  IntList * newList = new IntList();
  IntList::MyIterator *i = ls.iterator();
  for (; i->hasMoreElements(); i->nextElement())  {
    insert(*newList, i->getCurrent());
  }
  delete i;
  return newList;
}

int main() {
  IntList list;         // Создан новый пустой список
  // Добавляем в список элементы
  list.addLast(5);
  list.addLast(2);
  list.addLast(8);
  list.addLast(8);
  list.addLast(5);
  list.addLast(15);
  list.addLast(-3);
  list.addLast(5);
  cout << "The following elements are entered into the list:" << endl;
  printList(list);

  // 1. Проверяем вычисление среднего значения с помощью внешнего итератора
  cout << "Average of the list elements: " << average(list) << endl;

  // 2. Проверяем вычисление максимального количества совпадающих элементов
  cout << "Maximum of the equal list elements: " << maxEqualElements(list) << endl;

  // 3. Удаляем элемент 8
  removeElements(list, 8);
  cout << "List after removing the '8' values from the list:" << endl;
  printList(list);

  // 4. Сортировка списка
  IntList * sortedList = bubbleSort(list);
  cout << "The list after the sorting:" << endl;
  printList(*sortedList);
  delete sortedList;

  return 0;
}
