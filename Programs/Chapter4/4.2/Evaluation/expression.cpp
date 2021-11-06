/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.2. Вычисления по формулам                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : expression.cpp                                   *
*  Описание : Реализация операций общего характера над         *
*             выражениями                                      *
***************************************************************/

#include <string>
#include <exception>

using namespace std;

#include "expression.h"

// Конструктор:
Operator::Operator(string sign, Expression **ops, int arity) 
   : operSign(sign), operands(new PExpression[arity]), arity(arity) {
  for (int i = 0; i < arity; i++) {
    operands[i] = ops[i];
  }
}

Operator::~Operator() {
  for (int i = 0; i < arity; i++) {
    delete operands[i];
  }
}

Expression * Operator::operator [] (int i) const {
  if (i < 0 || i >= arity) throw OutOfRangeException();
  return operands[i];
}

// Оператор преобразования в строку
Operator::operator string () const {
  string res = operSign + "(";
  for (int i = 0; i < arity-1; i++) {
    res += ((string)*(operands[i]) + ", ");
  }
  return res + (string)*(operands[arity-1]) + ")";
}

// Оператор сравнения выражений
bool Operator::operator == (const Expression & src) const {
  if (!src.isOperator() || arity != ((const Operator &)src).getArity())
    return false;
  for (int i = 0; i < arity; i++) {
    if (*operands[i] != *((const Operator &)src)[i]) return false;
  }
  return true;
}
