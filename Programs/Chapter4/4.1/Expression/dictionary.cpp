/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.1. Представление выражений                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : dictionary.cpp                                   *
*  Описание : Реализация словаря, представленного в виде       *
*             хеш-таблицы                                      *
***************************************************************/

#include <string>
#include <iostream>
#include "dictionary.h"

using namespace std;

Iterator<string> & HashDictionary::KeysIterator::operator ++() {
  while (++pos < LENGTH && dict[pos] == NULL) {
//    cout << "pos=" << pos << ", contains:NULL" << endl;
  }
//  cout << "pos=" << pos << (pos < LENGTH ? string(", contains:") + *dict[pos] : "") << endl;
  return *this;
}

int HashDictionary::hash(const string & str) {
  int sum = 0;
  for (int i = 0; i < str.length(); i++) {
    sum += str[i] + i;
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

ostream & operator << (ostream & out, HashDictionary & dict) {
  bool printed = false;
  for (int i = 0; i < LENGTH; i++) {
    if (dict.dict[i]) {
      out << (printed ? ", " : "[") << *dict.dict[i];
      printed = true;
    }
  }
  return out << (printed ? "]" : "[]");
}
