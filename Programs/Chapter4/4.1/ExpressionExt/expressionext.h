/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.1. Представление выражений                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : expression.h                                     *
*  Описание : Описание структуры синтасического дерева и       *
*             некоторых операций над ним                       *
***************************************************************/

#ifndef __EXPRESSION_EXT_H
#define __EXPRESSION_EXT_H

#include <string>
#include <exception>
#include <stdio.h>

using namespace std;

#include "expression.h"

const string INTEGER = "int";
const string DOUBLE = "double";
const string BINARY = "binary";
const string UNARY_FUNCTION = "unary function";

//==============================================================
// Класс Integer представляет простейший тип выражения -
// целую константу.
//==============================================================

class Integer : public Constant {
  int value;

public :

  // Конструктор
  Integer(int value) : value(value) {}

  // Проверка типа
  string what() const { return INTEGER; }

  // Функция доступа
  int getValue() const { return value; }

  // Оператор преобразования в строку
  operator string () const {
    char buffer[14] = {0};
    sprintf(buffer, value < 0 ? "(%d)" : "%d", value);
    return buffer;
  }

  // Оператор сравнения выражений
  bool operator == (const Expression & src) const {
    return src.what() == INTEGER && value == ((const Integer &)src).getValue();
  }

  // Операция посещения узла
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// Класс Double представляет еще один простейший тип выражения -
// вещественную константу.
//==============================================================

class Double : public Constant {
  double value;

public :

  // Конструктор
  Double(double value) : value(value) {}

  // Проверка типа
  string what() const { return DOUBLE; }

  // Функция доступа
  double getValue() const { return value; }

  // Оператор преобразования в строку
  operator string () const {
    char buffer[25] = {0};
    sprintf(buffer, "%24e", value);
    return buffer;
  }

  // Оператор сравнения выражений
  bool operator == (const Expression & src) const {
    return src.what() == DOUBLE && value == ((const Double &)src).getValue();
  }

  // Операция посещения узла
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// Класс Binary представляет выражение, состоящее из знака
// операции и двух операндов, каждый из которых в свою очередь
// является выражением
//==============================================================

class Binary : public Operator {
public :

  // Конструктор:
  Binary(string sign, Expression *op1, Expression *op2) 
     : Operator(sign, &op1, 2) {}

  // Проверка типа
  string what() const { return BINARY; }

  // Функции доступа:
  Expression * getOperand1() const { return (*this)[0]; }
  Expression * getOperand2() const { return (*this)[1]; }

  // Оператор преобразования в строку
  operator string () const {
    return "(" + (string)*(operands[0]) + operSign + (string)*(operands[1]) + ')';
  }

  // Операция посещения узла
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// Класс UnaryFunction представляет выражение, состоящее из
// имени функции и ее аргумента, который в свою очередь
// является выражением
//==============================================================

class UnaryFunction : public Operator {
public :

  // Конструктор:
  UnaryFunction(string sign, Expression *op) 
     : Operator(sign, &op, 1) {}

  // Проверка типа
  string what() const { return UNARY_FUNCTION; }

  // Функции доступа:
  Expression * getOperand() const { return (*this)[0]; }

  // Операция посещения узла
  void accept(Visitor & visitor) { visitor.visit(this); }
};

#endif
