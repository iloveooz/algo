/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.2. Хеширование и поиск в хеш-таблицах             *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Тестирование словаря, представленного в виде     *
*             хеш-таблицы                                      *
***************************************************************/

#include "dictionary.h"
#include "wordsiterator.h"
#include "hashtable.h"
#include <iostream>

using namespace std;

//===============================================================
// Функция twice ищет в заданном предложении слово, встречающееся
// более одного раза. Если такое слово есть - функция его выдает,
// если такого слова нет - функция выдает пустое слово
//===============================================================

string twice(const char * text) {
  // Определяем словарь для исходного текста
  HashDictionary dict;

  // Итератор слов текста будет считать разделителями пробелы,
  // знаки препинания, кавычки, скобки и другие "пустые" символы
  for (WordsIterator iterator(text);
       iterator.hasMoreElements();
       ++iterator) {
    // Выберем очередное слово и преобразуем его к нижнему регистру букв.
    string nextWord = strlwr((*iterator));
    if (dict.hasWord(nextWord)) {
      return nextWord;       // слово уже встречалось
    } else {
      dict.add(nextWord);    // добавляем новое слово
    }
  }
  return string();           // в предложении нет одинаковых слов
}

int wordsCounter(const char * text, const char * word) {
  HashTable<int> dict;

  for (WordsIterator iterator(text);
       iterator.hasMoreElements();
       ++iterator) {
    // Выберем очередное слово и преобразуем его к нижнему регистру букв.
    const char * nextWord = strlwr((*iterator));
    int * counter = dict.find(nextWord);
    if (counter == NULL) {
      dict.add(nextWord, new int(1));
    } else {
      ++*counter;
    }
  }
  int * counter = dict.find(word);
  return counter ? *counter : 0;
}

int main() {
  char * text1 = "It was many and many a year ago,\n"
                 "In a kingdom by the sea,\n"
                 "That a maiden there lived whom you may know\n"
                 "By the name of Annabel Lee.";
  char * text2 = "I know the only thing that I know nothing!";
  char * word = "a";

  cout << "Twice: " << twice(text1) << endl;
  cout << "Twice: " << twice(text2) << endl;
  cout << "The \"" << word << "\" word has " << wordsCounter(text1, word)
       << " entrances in the text \"" << text1 << "\"\n";

  return 0;
}
