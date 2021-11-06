/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.1. Абстрактная система распределения памяти       *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Тестовая функция, проверяющая работу алгоритма   *
*             распределения памяти и цифровой сортировки       *
***************************************************************/

#include <iostream>
#include "digitsort.h"

using namespace std;

template <class Element>
void printArray(Element * array, int low, int high) {
  for (int i = low; i <= high; i++) {
    cout << array[i] << ", ";
  }
  cout << endl;
}

class IntKey {
  friend ostream & operator << (ostream & out, const IntKey & v);

  int value;
public :
  IntKey(int v = 0) : value(v) {}
  IntKey(const IntKey & key) : value(key.value) {}
  int getValue() { return value; }
  int length() { return 8; }
  int power() { return 16; }
  int operator [] (int i) const { return (value >> (4*(7-i))) & 15; }
};

ostream & operator << (ostream & out, const IntKey & v) {
  return out << v.value;
}

int main() {
  // Заполненяем массив test случайными значениями и выводим их
  int len = 100;
  IntKey test[len];
  int seed = 13;
  for (int i = 0; i < len; i++) {
    test[i] = IntKey(seed = (837*seed + 1079) & 0x7FFFFFFF);
  }
  printArray<IntKey>(test, 0, len-1);
  cout << endl;

  // Сортируем массив методом цифровой сортировки и выводим результат
  digitSort<IntKey>(test, 0, len-1);
  printArray<IntKey>(test, 0, len-1);

  return 0;
}
