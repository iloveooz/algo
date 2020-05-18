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

#ifndef __EXPRESSION_H
#define __EXPRESSION_H

#include <string>
#include <exception>
#include <set>
#include <iterator>
#include <stdio.h>

class Expression;
class Integer;
class Variable;
class Operator;

#include "visitor.h"
#include "dictionary.h"

using namespace std;

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

//==============================================================
// Базовый класс для представления синтаксического дерева
// выражения. Подклассы этого класса реализуют разные частные
// случаи представления выражений.
//==============================================================

class Expression {
public :
  enum Type {
    INTEGER = 1,
    VARIABLE,
    OPERATOR
  };

  // Виртуальный деструктор
  virtual ~Expression() {}
  // Проверка типа выражения
  virtual Type what() const = 0;
  // Метод для построения синтаксического дерева выражения
  static Expression * parse(const string & source);
  // Оператор преобразования выражения в строковое представление
  virtual operator string () const = 0;
  // Операция копирования выражения
  virtual Expression * copy() const = 0;
  // Операции сравнения выражений
  virtual bool operator == (const Expression & src) const = 0;
  virtual bool operator != (const Expression & src) const { return !operator ==(src); }
  // Список переменных выражения
  virtual HashDictionary * allVariables() const = 0;
  // Операция посещения узла
  virtual void accept(Visitor & visitor) = 0;
};

//==============================================================
// Класс Integer представляет простейший тип выражения -
// целую константу.
//==============================================================

class Integer : public Expression {
  int value;

public :

  // Конструктор
  Integer(int value) : value(value) {}
  // Проверка типа
  Type what() const { return INTEGER; }
  // Функция доступа
  int getValue() const { return value; }
  // Оператор преобразования в строку
  operator string () const {
    char buffer[14] = {0};
    sprintf(buffer, value < 0 ? "(%d)" : "%d", value);
    return buffer;
  }
  // Операция копирования
  Expression * copy() const { return new Integer(value); }
  // Оператор сравнения выражений
  bool operator == (const Expression & src) const {
    return src.what() == INTEGER && value == ((const Integer &)src).getValue();
  }
  // Список переменных выражения
  HashDictionary * allVariables() const { return new HashDictionary(); }
  // Операция посещения узла
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// Класс Variable представляет простейший тип выражения -
// идентификатор переменной.
//==============================================================

class Variable : public Expression {
  string variable;

public :

  // Конструктор
  Variable(string ident) : variable(ident) {}
  // Проверка типа
  Type what() const { return VARIABLE; }
  // Функция доступа
  string getVariable() const { return variable; }
  // Оператор преобразования в строку
  operator string () const { return variable; }
  // Операция копирования
  Expression * copy() const { return new Variable(variable); }
  // Оператор сравнения выражений
  bool operator == (const Expression & src) const {
    return src.what() == VARIABLE && variable == ((const Variable &)src).getVariable();
  }
  // Список переменных выражения
  HashDictionary * allVariables() const {
    HashDictionary * s = new HashDictionary();
    s->add(variable);
    return s;
  }
  // Операция посещения узла
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// Класс Operator представляет выражение, состоящее из знака
// операции и двух операндов, каждый из которых в свою очередь
// является выражением
//==============================================================

class Operator : public Expression {
  char operSign;           // Знак операции
  Expression *operand1;    // Первый операнд
  Expression *operand2;    // Второй операнд

public :

  // Конструктор:
  Operator(char sign, Expression *op1, Expression *op2) 
     : operSign(sign), operand1(op1), operand2(op2) {}
  // Деструктор
  ~Operator() { delete operand1; delete operand2; }

  // Проверка типа
  Type what() const { return OPERATOR; }
  // Функции доступа:
  char getOperSign() const { return operSign; }
  Expression * getOperand1() const { return operand1; }
  Expression * getOperand2() const { return operand2; }

  // Оператор преобразования в строку
  operator string () const {
    return "(" + (string)*operand1 + operSign + (string)*operand2 + ')';
  }
  // Операция копирования
  Expression * copy() const {
    return new Operator(operSign, operand1->copy(), operand2->copy());
  }

  // Оператор сравнения выражений
  bool operator == (const Expression & src) const {
    return src.what() == OPERATOR && operSign == ((const Operator &)src).getOperSign() &&
           *operand1 == *((const Operator &)src).getOperand1() &&
           *operand2 == *((const Operator &)src).getOperand2();
  }

  // Список переменных выражения
  HashDictionary * allVariables() const {
    HashDictionary * s1 = operand1->allVariables();
    HashDictionary * s2 = operand2->allVariables();
    Iterator<string> *i = s2->keys();
    for (; i->hasMoreElements(); ++*i) {
      if (!s1->hasWord(**i)) s1->add(**i);
    }
    delete i;
    delete s2;
    return s1;
  }

  // Операция посещения узла
  void accept(Visitor & visitor) { visitor.visit(this); }
};

#endif
