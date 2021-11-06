/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.2. Хеширование и поиск в хеш-таблицах             *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : dictionary.cpp                                   *
*  Описание : Реализация словаря, представленного в виде       *
*             хеш-таблицы                                      *
***************************************************************/

#include <string>
#include "dictionary.h"

int HashDictionary::code(char c) {
  return string("abcdefghijklmnopqrstuvwxyz").find(c) + 1;
}

int HashDictionary::hash(const string & str) {
  int sum = 0;
  for (int i = 0; i < str.length(); i++) {
    sum += code(str[i]) + i;
  }
  return (P * sum + Q) % LENGTH;
}

int HashDictionary::findPos(const string & word) const {
  int i = hash(word);  // текущий индекс слова в словаре
  for (int counter = 0; counter < LENGTH; counter++) {
    if (dict[i] == NULL || *dict[i] == word) {
      return i;        // слово или позиция для его вставки найдено
    } else if (++i == LENGTH) {
      i = 0;          // переход к следующему индексу
    }
  }
  return -1;           // перебраны все позиции в словаре!
}

void HashDictionary::add(const string & word) {
  int i = findPos(word);   // позиция слова в словаре
  if (i == -1) return;     // только в случае переполнения словаря!
  if (dict[i] == NULL) dict[i] = new string();
  *dict[i] = word;         // добавление слова или его перезапись
}

bool HashDictionary::hasWord(const string & word) const {
  int i = findPos(word);    // позиция слова в словаре
  return i != -1 && dict[i] != NULL;
}
