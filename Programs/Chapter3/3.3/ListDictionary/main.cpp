/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.3. Словари, представленные списками и деревьями   *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Проверка работы словаря, представленного списком *
***************************************************************/

#include <string>
#include <iostream>
#include "listdictionary.h"
#include "wordsiterator.h"
#include "pair.h"
#include "iterator.h"

using namespace std;

//==============================================================
// Функция frequentWord находит в заданном тексте слово,
// повторяющееся в нем максимальное число раз. В результате
// работы функция выдает пару из найденного слова и
// числа его повторений в тексте.
//==============================================================

Pair<int> frequentWord(char * text) {
  WordsIterator iterator(text);  // Итератор слов текста
  ListDictionary<int> dict;      // Словарь со счетчиками слов
  
  // 1. Занесение слов в словарь
  while (iterator.hasMoreElements()) {
    // Выбор очередного слова:
    char * token = strlwr(*iterator);
    // Ищем в словаре это слово и запоминаем связанный с ним счетчик:
    int * wordCounter = dict.find(token);
    if (wordCounter == NULL) {
      // Слова еще не было; заносим его в словарь со счетчиком = 1
      dict.add(token, 1);
    } else {
      // Слово уже было; увеличиваем значение счетчика на 1
      ++*wordCounter;
    }
    // переходим к следующему слову
    ++iterator;
  }
  
  // 2. Выбор слова с максимальной частотой
  Pair<int> maxPair("", 0);         // пара с максимальным числом повторений
  Iterator<Pair<int> > *i = dict.iterator(); // итератор словаря
  while (i->hasMoreElements()) {
    Pair<int> &nextPair = **i;
    // Сравниваем счетчики двух пар
    if (nextPair.obj > maxPair.obj) {
      maxPair = nextPair;
    }
    // переходим к следующей паре
    ++*i;
  }
  delete i;
  
  // 3. Выдача результата
  return maxPair;
}

//==============================================================
// Тестирование функции frequentWord и работы словаря.
// Для анализа дан фрагмент стихотворения Эдгара По "Ворон"
//==============================================================

int main() {
  char * text =
    "Deep into that darkness peering, long I stood there wondering, fearing,\n"
    "Doubting, dreaming dreams no mortal ever dared to dream before;\n"
    "But the silence was unbroken, and the stillness gave no token,\n"
    "And the only word there spoken was the whispered word, \"Lenore?\"\n"
    "That I whispered, and the echo murmured back the word, \"Lenore!\"\n"
    "Merely this and nothing more.\n";
  Pair<int> maximum = frequentWord(text);
  cout << "Word " << maximum.key << " has " << maximum.obj << " entrances in the text\n" << text;

  return 0;
}
