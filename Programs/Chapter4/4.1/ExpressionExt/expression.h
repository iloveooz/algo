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

class Expression;
class Constant;
class Variable;
class Operator;

#include "visitor.h"

using namespace std;

const string VARIABLE = "var";

class OutOfRangeException : public exception {
  char * reason;
public :
  OutOfRangeException(char * message = "Index is out of range") : reason(message) {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// ������� ����� ��� ������������� ��������������� ������
// ���������. ��������� ����� ������ ��������� ������ �������
// ������ ������������� ���������.
//==============================================================

class Expression {
public :

  // ����������� ����������
  virtual ~Expression() {}
  // �������� ���� ���������
  virtual string what() const = 0;
  virtual bool isConst() const = 0;
  virtual bool isVariable() const = 0;
  virtual bool isOperator() const = 0;
  // �������� �������������� ��������� � ��������� �������������
  virtual operator string () const = 0;
  // �������� ��������� ���������
  virtual bool operator == (const Expression & src) const = 0;
  virtual bool operator != (const Expression & src) const { return !operator ==(src); }
  // �������� ��������� ����
  virtual void accept(Visitor & visitor) = 0;
};

//==============================================================
// ����������� ����� Constant ������������ ������� ����������� 
// ��������� - �����, ������������ � ������ ���������.
//==============================================================

class Constant : public Expression {
public :
  bool isConst() const { return true; }
  bool isVariable() const { return false; }
  bool isOperator() const { return false; }
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
  bool isConst() const { return false; }
  bool isVariable() const { return true; }
  bool isOperator() const { return false; }
  string what() const { return VARIABLE; }

  // ������� �������
  string getVariable() const { return variable; }

  // �������� �������������� � ������
  operator string () const { return variable; }

  // �������� ��������� ���������
  bool operator == (const Expression & src) const {
    return src.what() == VARIABLE && variable == ((const Variable &)src).getVariable();
  }

  // �������� ��������� ����
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// ����� Operator ������������ ���������, ��������� �� �����
// �������� � ���������, ������ �� ������� � ���� �������
// �������� ����������. ��� - ���� ����������� �����
//==============================================================

class Operator : public Expression {
protected:

  string operSign;         // ���� ��������
  Expression **operands;   // ��������
  int arity;               // ���������� ��������� � ��������

  typedef Expression * PExpression;

public :

  // �����������:
  Operator(string sign, Expression **ops, int arity);
  // ����������
  ~Operator();

  // �������� ����
  bool isConst() const { return false; }
  bool isVariable() const { return false; }
  bool isOperator() const { return true; }

  // ������� �������:
  string getOperSign() const { return operSign; }
  Expression * operator [] (int i) const;
  int getArity() const { return arity; }

  // �������� �������������� � ������
  operator string () const;

  // �������� ��������� ���������
  bool operator == (const Expression & src) const;
};

#endif
