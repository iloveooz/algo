/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.2. Распределение памяти блоками постоянной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Тестовая функция, проверяющая работу алгоритма   *
*             распределения памяти                             *
***************************************************************/

#include <iostream>
#include "treedictionary.h"

using namespace std;

int main() {
  // Заводим словарь на не более, чем 100 слов
  TreeDictionary d(100);
  // Определяем некоторый набор слов
  string text[] = {
    string("when"), string("we"), string("speak"), string("of"),
    string("free"), string("software"), string("we"), string("are"),
    string("referring"), string("to"), string("freedom"), string("not"),
    string("price"),
  };
  // Заносим слова в словарь
  for (int i = 0; i < sizeof(text)/sizeof(string); i++) {
    d.addWord(text[i]);
  }
  // Выводим слова в алфавитном порядке
  cout << d;
}
