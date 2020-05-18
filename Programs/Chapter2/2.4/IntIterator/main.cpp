/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.4. Итераторы                                      *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : main.cpp                                      *
*  Описание    : Внутренние итераторы списка целых:            *
*                тестирующая функция                           *
***************************************************************/

#include <iostream>
#include "IntList.h"
#include "Summator.h"
#include "Comparator.h"
#include "NegCounter.h"

using namespace std;

// Функция суммирования элементов в списке
int sum(IntList & l) {
  Summator summator;
  l.traverse(summator);
  return summator.getSum();
}

// Функция суммирования элементов в списке в обратном порядке
int sumBack(IntList & l) {
  Summator summator;
  l.traverseBack(summator);
  return summator.getSum();
}

// Функция проверки наличия заданного элемента в списке
bool hasElement(IntList & l, int value) {
  Comparator comp(value);
  l.traverse(comp);
  return comp.hasFound();
}

// Функция подсчета количества отрицательных элементов
int negatives(IntList & l) {
  NegativeCounter counter;
  l.traverse(counter);
  return counter.getCounter();
}

int main() {
  IntList list;         // Создан новый пустой список
  // Добавляем в список элементы
  list.addLast(5);
  list.addLast(2);
  list.addLast(15);
  list.addLast(-3);
  list.addLast(8);

  // 1. Проверяем суммирование элементов с помощью внутреннего итератора
  cout << "Sum of the list elements: " << sum(list) << endl;
  //    То же самое в обратном порядке
  cout << "Sum of the list elements taken in reverse: " << sumBack(list) << endl;

  // 2. Проверяем поиск элемента в списке
  cout << "Searching element 2: " 
       << (hasElement(list, 2) ? "found" : "not found")
       << endl;
  cout << "Searching element 3: " 
       << (hasElement(list, 3) ? "found" : "not found")
       << endl;

  // 3. Проверяем функцию подсчета количества отрицательных элементов
  cout << "Number of negative elements: " << negatives(list) << endl;

  return 0;
}
