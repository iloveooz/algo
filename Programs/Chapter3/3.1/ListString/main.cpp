/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.1. Способы представления строк                    *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Тест некоторых операций над строками, представ-  *
*             ленными в виде списка строковых элементов        *
***************************************************************/

#include "ListString.h"
#include <iostream>

using namespace std;

int main() {
  // Сначала создается некоторая строка
  ListString s("We all live in a yellow submarine!");

  // Созданная строка выводится в стандартный символьный поток
  // после неявного преобразования ее к стандартному представлению
  cout << "Before insertion: " << s << endl;

  // Вычисляется длина строки
  int len = s.length();

  // В строку вставляются новые фрагменты
  s.insert(len-1, ", yellow submarine");
  s.insert(len-1, ", yellow submarine");

  // Копируем то, что получилось
  ListString s1 = s;

  // Вырезаем слово из строки
  ListString word = s.substr(17, 23);

  // Теперь в конец добавим еще несколько символов.
  // Смотрим, как меняется структура строки
  ((cout << "String: [" << (char*)s << "] has the structure: ") <<= s) << endl;
  s += " Yeah!";
  ((cout << "String: [" << (char*)s << "] has the structure: ") <<= s) << endl;
  s += " Yeah!";
  ((cout << "String: [" << (char*)s << "] has the structure: ") <<= s) << endl;
  s += " Yeah!";
  ((cout << "String: [" << (char*)s << "] has the structure: ") <<= s) << endl;

  // Распечатываем некоторые результаты
  cout << "After insertion: " << (char*)s << endl;
  cout << "Before appending: " << (char*)s1 << endl;
  cout << "A word from the string: " << (char*)word << endl;

  return 0;
}
