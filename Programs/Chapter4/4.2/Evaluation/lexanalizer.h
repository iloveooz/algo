/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.2. Вычисления по формулам                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : lexanalizer.h                                    *
*  Описание : Лексический анализатор для анализа выражения     *
***************************************************************/

#ifndef __LEX_ANALIZER_H
#define __LEX_ANALIZER_H

#include <string>
#include "lexical.h"
#include "iterator.h"

using namespace std;

typedef Lexical * PLexical;

class LexAnalizer : public Iterator<PLexical> {
  string src;
  int srcLen;
  int ptr;
  PLexical nextLexema;

public :
  // Конструктор
  LexAnalizer(const string & source) : src(source), ptr(0), srcLen(source.length()), nextLexema(NULL) {
    getNextLexema();
  }

  // Функции, реализующие интерфейс итератора
  bool hasMoreElements() const { return nextLexema != NULL; }
  // Предполагается, что итератор производит объекты класса Lexical
  PLexical & operator *() { return nextLexema; }
  const PLexical & operator *() const { return nextLexema; }
  Iterator<PLexical> & operator ++() { getNextLexema(); return *this; }
  // Текущая позиция при анализе строки:
  int getCurrentPosition() const { return ptr; }

private :
  void getNextLexema();
};

#endif
