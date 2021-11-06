/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.3. Распределение памяти блоками переменной длины  *
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

class Expression;
class Constant;
class Variable;
class Operator;

#include "visitor.h"
#include "context.h"
#include "bilistmemory.h"

using namespace std;

extern BiListMemory * memoryManagement;

const string VARIABLE = "var";

class OutOfRangeException : public exception {
  char * reason;
public :
  OutOfRangeException(char * message = "Index is out of range") : reason(message) {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// Базовый класс для представления синтаксического дерева
// выражения. Подклассы этого класса реализуют разные частные
// случаи представления выражений.
//==============================================================

class Expression {
public :

  // Виртуальный деструктор
  virtual ~Expression() {}
  // Проверка типа выражения
  virtual string what() const = 0;
  virtual bool isConst() const = 0;
  virtual bool isVariable() const = 0;
  virtual bool isOperator() const = 0;
  // Оператор преобразования выражения в строковое представление
  virtual operator string () const = 0;
  // Операции сравнения выражений
  virtual bool operator == (const Expression & src) const = 0;
  virtual bool operator != (const Expression & src) const { return !operator ==(src); }
  // Операция вычисления значений переменной в заданном контексте
  virtual Constant * evaluate(const Context & ctx) const = 0;
  // Операция посещения узла
  virtual void accept(Visitor & visitor) = 0;
  void * operator new(size_t sz) { return memoryManagement->get(sz); }
  void operator delete(void * ptr) { memoryManagement->release(ptr); }
};

//==============================================================
// Абстрактный класс Constant представляет понятие абстрактной 
// константы - целые, вещественные и другие константы.
//==============================================================

class Constant : public Expression {
public :
  bool isConst() const { return true; }
  bool isVariable() const { return false; }
  bool isOperator() const { return false; }
  // Операция вычисления значений переменной в заданном контексте
  Constant * evaluate(const Context & ctx) const { return (Constant*) this; }
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
  bool isConst() const { return false; }
  bool isVariable() const { return true; }
  bool isOperator() const { return false; }
  string what() const { return VARIABLE; }

  // Функция доступа
  string getVariable() const { return variable; }

  // Оператор преобразования в строку
  operator string () const { return variable; }

  // Оператор сравнения выражений
  bool operator == (const Expression & src) const {
    return src.what() == VARIABLE && variable == ((const Variable &)src).getVariable();
  }

  // Операция вычисления значений переменной в заданном контексте
  Constant * evaluate(const Context & ctx) const {
    Expression * result = ctx.find(variable);
    if (result == NULL || !result->isConst()) return NULL;
    return (Constant *) result;
  }

  // Операция посещения узла
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// Класс Operator представляет выражение, состоящее из знака
// операции и операндов, каждый из которых в свою очередь
// является выражением. Это - тоже абстрактный класс
//==============================================================

class Operator : public Expression {
protected:

  string operSign;         // Знак операции
  Expression **operands;   // Операнды
  int arity;               // Количество операндов в операции

  typedef Expression * PExpression;

public :

  // Конструктор:
  Operator(string sign, Expression **ops, int arity);
  // Деструктор
  ~Operator();

  // Проверка типа
  bool isConst() const { return false; }
  bool isVariable() const { return false; }
  bool isOperator() const { return true; }

  // Функции доступа:
  string getOperSign() const { return operSign; }
  Expression * operator [] (int i) const;
  int getArity() const { return arity; }

  // Оператор преобразования в строку
  operator string () const;

  // Оператор сравнения выражений
  bool operator == (const Expression & src) const;

  // Создание копии узла с тем же знаком операции, но другими операндами
  virtual Expression * copyWithNewArgs(Expression** newOperands) const = 0;
};

#endif
