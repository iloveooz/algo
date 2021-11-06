/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.2. Хеширование и поиск в хеш-таблицах             *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : wordsiterator.h                                  *
*  Описание : Итератор, выдающий слова из заданного текста     *
***************************************************************/

#ifndef __WORDS_ITERATOR_H
#define __WORDS_ITERATOR_H

#include <string.h>
#include "iterator.h"

//==============================================================
// Класс WordsIterator представляет собой простой итератор слов,
// на которые делит заданный текст стандартная функция Си strtok.
// Словом считается любая последовательность символов,
// отделенная от других слов разделителями: знаками препинания,
// пробелами и пр.
//===============================================================

class WordsIterator : public Iterator<char *>{

private:

  char * words;          // Для хранения и обработки исходного текста
  char * nextWord;       // Указатель на очередное слово
  char * delimeters;     // Массив символов-разделителей

public:

  //-------------------------------------------------------------
  // Конструктор
  //-------------------------------------------------------------
  WordsIterator(char * phrase,
                char * delim = " ,.!?;:-()\'\"\n\t\f")
    // Исходный текст сохраняется в буфере и обрабатывается
    // стандартной функцией strtok.
    : words(new char[strlen(phrase)+1]),
      delimeters(delim)
  {
    strcpy(words, phrase);
    nextWord = strtok(words, delimeters);
  }

  //-------------------------------------------------------------
  // Функция проверки наличия следующего слова
  //-------------------------------------------------------------
  bool hasMoreElements() const { return nextWord != NULL; }

  //-------------------------------------------------------------
  // Сдвиг итератора на слово вперед
  //-------------------------------------------------------------
  Iterator<char *> & operator ++() {
    nextWord = strtok(NULL, delimeters);
    return *this;
  }

  //-------------------------------------------------------------
  // Доступ к очередному слову
  //-------------------------------------------------------------
  typedef char * pchar;
  const pchar & operator *() const { return nextWord; }
  pchar & operator *() { return nextWord; }
};

#endif
