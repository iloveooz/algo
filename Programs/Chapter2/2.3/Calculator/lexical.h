/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.3. Стеки и очереди                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : lexical.h                                        *
*  Описание : Определение классов Lexical и LexAnalyzer        *
***************************************************************/

#ifndef __LEXICAL_H
#define __LEXICAL_H

//==============================================================
// Класс Lexical представляет одну лексему
//==============================================================

class Lexical {
  int lexClass;    // Лексический класс
  int value;       // значение, представляющее лексему - целое или знак операции

public:

  // Лексические классы
  enum LexType {
    OPERAND = 1,   // операнд (целое)
    OPERATOR,      // знак операции
    LEFTPAR,       // левая (открывающая) скобка
    RIGHTPAR       // правая (закрывающая) скобка
  };

  // Конструктор (пустая лексема представлена нулем)
  Lexical(int lexClass = OPERAND, int value = 0) :
      lexClass(lexClass), value(value)
    {}

  // Конструктор копирования
  Lexical(const Lexical & lexeme) :
      lexClass(lexeme.lexClass), value(lexeme.value)
    {}

  // Функции доступа - только для чтения
  int getLexClass() const { return lexClass; }
  char getOperSign() const { return lexClass == OPERATOR ? (char)value : 0; }
  int getValue() const { return lexClass == OPERAND ? value : 0; }
};

//==============================================================
// Объект (итератор) LexAnalyzer генерирует последовательность лексем
//==============================================================

class LexAnalyzer {
  // указатель на анализируемый текст
  char * ptr;

private:

  // Функция сдвига указателя на первый непустой символ.
  void findSymbol();

public:

  // Конструктор устанавливает указатель на первый символ текста
  LexAnalyzer(char * src) : ptr(src) {}

  // Конструктор копирования просто дублирует указатель аргумента
  LexAnalyzer(const LexAnalyzer & analyzer) : ptr(analyzer.ptr) {}

  // Функция выдачи очередной лексемы
  Lexical next();

  // Есть ли еще лексемы?
  bool hasNext();
};

#endif
