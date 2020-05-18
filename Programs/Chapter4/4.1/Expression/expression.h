/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.1. ������������� ���������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : expression.h                                     *
*  �������� : �������� ��������� �������������� ������ �       *
*             ��������� �������� ��� ���                       *
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
// ����� ��� ������������� �������������� ��������, �������
// ���������� ��� ������� ���������� ���������.
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
// ������� ����� ��� ������������� ��������������� ������
// ���������. ��������� ����� ������ ��������� ������ �������
// ������ ������������� ���������.
//==============================================================

class Expression {
public :
  enum Type {
    INTEGER = 1,
    VARIABLE,
    OPERATOR
  };

  // ����������� ����������
  virtual ~Expression() {}
  // �������� ���� ���������
  virtual Type what() const = 0;
  // ����� ��� ���������� ��������������� ������ ���������
  static Expression * parse(const string & source);
  // �������� �������������� ��������� � ��������� �������������
  virtual operator string () const = 0;
  // �������� ����������� ���������
  virtual Expression * copy() const = 0;
  // �������� ��������� ���������
  virtual bool operator == (const Expression & src) const = 0;
  virtual bool operator != (const Expression & src) const { return !operator ==(src); }
  // ������ ���������� ���������
  virtual HashDictionary * allVariables() const = 0;
  // �������� ��������� ����
  virtual void accept(Visitor & visitor) = 0;
};

//==============================================================
// ����� Integer ������������ ���������� ��� ��������� -
// ����� ���������.
//==============================================================

class Integer : public Expression {
  int value;

public :

  // �����������
  Integer(int value) : value(value) {}
  // �������� ����
  Type what() const { return INTEGER; }
  // ������� �������
  int getValue() const { return value; }
  // �������� �������������� � ������
  operator string () const {
    char buffer[14] = {0};
    sprintf(buffer, value < 0 ? "(%d)" : "%d", value);
    return buffer;
  }
  // �������� �����������
  Expression * copy() const { return new Integer(value); }
  // �������� ��������� ���������
  bool operator == (const Expression & src) const {
    return src.what() == INTEGER && value == ((const Integer &)src).getValue();
  }
  // ������ ���������� ���������
  HashDictionary * allVariables() const { return new HashDictionary(); }
  // �������� ��������� ����
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// ����� Variable ������������ ���������� ��� ��������� -
// ������������� ����������.
//==============================================================

class Variable : public Expression {
  string variable;

public :

  // �����������
  Variable(string ident) : variable(ident) {}
  // �������� ����
  Type what() const { return VARIABLE; }
  // ������� �������
  string getVariable() const { return variable; }
  // �������� �������������� � ������
  operator string () const { return variable; }
  // �������� �����������
  Expression * copy() const { return new Variable(variable); }
  // �������� ��������� ���������
  bool operator == (const Expression & src) const {
    return src.what() == VARIABLE && variable == ((const Variable &)src).getVariable();
  }
  // ������ ���������� ���������
  HashDictionary * allVariables() const {
    HashDictionary * s = new HashDictionary();
    s->add(variable);
    return s;
  }
  // �������� ��������� ����
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// ����� Operator ������������ ���������, ��������� �� �����
// �������� � ���� ���������, ������ �� ������� � ���� �������
// �������� ����������
//==============================================================

class Operator : public Expression {
  char operSign;           // ���� ��������
  Expression *operand1;    // ������ �������
  Expression *operand2;    // ������ �������

public :

  // �����������:
  Operator(char sign, Expression *op1, Expression *op2) 
     : operSign(sign), operand1(op1), operand2(op2) {}
  // ����������
  ~Operator() { delete operand1; delete operand2; }

  // �������� ����
  Type what() const { return OPERATOR; }
  // ������� �������:
  char getOperSign() const { return operSign; }
  Expression * getOperand1() const { return operand1; }
  Expression * getOperand2() const { return operand2; }

  // �������� �������������� � ������
  operator string () const {
    return "(" + (string)*operand1 + operSign + (string)*operand2 + ')';
  }
  // �������� �����������
  Expression * copy() const {
    return new Operator(operSign, operand1->copy(), operand2->copy());
  }

  // �������� ��������� ���������
  bool operator == (const Expression & src) const {
    return src.what() == OPERATOR && operSign == ((const Operator &)src).getOperSign() &&
           *operand1 == *((const Operator &)src).getOperand1() &&
           *operand2 == *((const Operator &)src).getOperand2();
  }

  // ������ ���������� ���������
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

  // �������� ��������� ����
  void accept(Visitor & visitor) { visitor.visit(this); }
};

#endif
