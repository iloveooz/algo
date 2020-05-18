/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.6. Бинарные деревья поиска                        *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : words.h                                          *
*  Описание : Определение простейшей классовой оболочки для    *
*             представления строк                              *
***************************************************************/

#ifndef __WORDS_H
#define __WORDS_H

#include <string.h>
#include <iostream>

using namespace std;

class Word;    // Предварительное описание класса

// Объявление операторов, необходимых для сравнения слов
// и вывода слов в символьный выходной поток
bool operator < (const Word &, const Word &);
bool operator > (const Word &, const Word &);
bool operator <= (const Word &, const Word &);
bool operator >= (const Word &, const Word &);
bool operator == (const Word &, const Word &);
bool operator != (const Word &, const Word &);
ostream & operator << (ostream &, const Word &);

/***************************************************************
*  Определение класса для слова - указателя на неизменяемую    *
*  строку для сравнений и вывода в символьный поток            *
***************************************************************/
class Word {
  // Операторы сравнения и вывода слов в выходной поток
  // должны иметь доступ к внутренней структуре слова 
  friend bool operator < (const Word &, const Word &);
  friend bool operator > (const Word &, const Word &);
  friend bool operator <= (const Word &, const Word &);
  friend bool operator >= (const Word &, const Word &);
  friend bool operator == (const Word &, const Word &);
  friend bool operator != (const Word &, const Word &);
  friend ostream & operator << (ostream &, const Word &);

  const char * src;    // Указатель на строку

public:

  // Конструкторы слов
  Word() : src("") {}
  Word(const Word & w) : src(w.src) {}
  Word(char * s) : src(s) {}
};

#endif
