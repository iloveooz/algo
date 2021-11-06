/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.3. Стеки и очереди                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : lexical.cpp                                      *
*  Описание : Определение методов класса анализатора.          *
***************************************************************/

#include <ctype.h>
#include <stdio.h>
#include "lexical.h"

//==============================================================
// Скрытая функция findSymbol сдвигает текущую позицию анализа
// на следующий непустой символ (если он существует)
//==============================================================

void LexAnalyzer::findSymbol() {
  while (*ptr != 0 && isspace(*ptr)) {
    ptr++;
  }
}

//==============================================================
// Функция 'next' ищет следующую лексему в тексте и создает
// соответствующий объект класса Lexical.
//==============================================================

Lexical LexAnalyzer::next() {
  // Сдвиг указателя и проверка следующего символа
  if (hasNext()) {
    char c = *ptr;
    if (isdigit(c)) {
      // сканируем целое число
      int v;
      if (sscanf(ptr, "%d", &v) == 0) v = 0;
      while (isdigit(*++ptr)) ;
      return Lexical(Lexical::OPERAND, v);
    } else if (c == '(') {
      // обнаружена левая скобка
      ptr++;
      return Lexical(Lexical::LEFTPAR);
    } else if (c == ')') {
      // это правая скобка
      ptr++;
      return Lexical(Lexical::RIGHTPAR);
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      // знак операции
      ptr++;
      return Lexical(Lexical::OPERATOR, c);
    }
  }
  // ничего не найдено; возвращаем пустую лексему
  return Lexical();
}

//==============================================================
// Функция 'hasNext' проверяет, есть ли еще хотя бы
// один непустой символ в тексте.
//==============================================================

bool LexAnalyzer::hasNext() {
  findSymbol();
  return *ptr != 0;
}
