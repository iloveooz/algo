/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.3. Преобразование формул                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : parser.h                                         *
*  Описание : Описание класса для анализа и построения         *
*             синтаксического дерева выражения                 *
***************************************************************/

#ifndef __PARSER_H
#define __PARSER_H

#include <string>

using namespace std;

#include "expressionext.h"
#include "lexical.h"
#include "lexanalizer.h"
#include "stack.h"
#include "stackfactory.h"

//==============================================================
// Класс для представления исключительной ситуации, могущей
// возникнуть при анализе ошибочного выражения.
//==============================================================

class ParseException : public exception {
  char * reason;
  int position;
public :
  ParseException(char * message, int pos) : reason(message), position(pos) {}
  const char * what() const throw() { return reason; }
  int getPosition() const { return position; }
};

class Parser {
public :
  // Метод для построения синтаксического дерева выражения
  static Expression * parse(const string & source);

private :
  //=============================================================
  // Переменные stExprFactory и stOperFactory задают фабрики
  // стеков для генерации стека операндов (узлов синтаксического
  // дерева) и стека операций (значений класса LexOperator)
  //=============================================================
  static StackFactory<Expression*> * stExprFactory;
  static StackFactory<LexOperator*> * stOperFactory;

  static void doOperator(
       Stack<Expression*> *operands,      // стек операндов содержит деревья
       Stack<LexOperator*> *operators     // стек операторов
               );

  static void doOperators(
       Stack<Expression*> *operands,      // стек операндов
       Stack<LexOperator*> *operators,    // стек операторов
       int minPrio                        // граничный приоритет
                );
};

#endif
