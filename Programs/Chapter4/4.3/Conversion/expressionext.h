/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.3. �������������� ������                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : expressionext.h                                  *
*  �������� : �������� ��������� ��������� ���������� �����    *
*             �������������� ������ � �������� ��� ����        *
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
// ����� Integer ������������ ���������� ��� ��������� -
// ����� ���������.
//==============================================================

class Integer : public Constant {
  int value;

public :

  // �����������
  Integer(int value) : value(value) {}

  // �������� ����
  string what() const { return INTEGER; }

  // ������� �������
  int getValue() const { return value; }

  // �������� �������������� � ������
  operator string () const {
    char buffer[14] = {0};
    sprintf(buffer, value < 0 ? "(%d)" : "%d", value);
    return buffer;
  }

  // �������� ��������� ���������
  bool operator == (const Expression & src) const {
    return src.what() == INTEGER && value == ((const Integer &)src).getValue();
  }

  // �������� ��������� ����
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// ����� Double ������������ ��� ���� ���������� ��� ��������� -
// ������������ ���������.
//==============================================================

class Double : public Constant {
  double value;

public :

  // �����������
  Double(double value) : value(value) {}

  // �������� ����
  string what() const { return DOUBLE; }

  // ������� �������
  double getValue() const { return value; }

  // �������� �������������� � ������
  operator string () const {
    char buffer[25] = {0};
    sprintf(buffer, "%24e", value);
    return buffer;
  }

  // �������� ��������� ���������
  bool operator == (const Expression & src) const {
    return src.what() == DOUBLE && value == ((const Double &)src).getValue();
  }

  // �������� ��������� ����
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// ����� Binary ������������ ���������, ��������� �� �����
// �������� � ���� ���������, ������ �� ������� � ���� �������
// �������� ����������
//==============================================================

class Binary : public Operator {
public :

  // �����������:
  Binary(string sign, Expression *op1, Expression *op2) 
     : Operator(sign, &op1, 2) {}

  // �������� ����
  string what() const { return BINARY; }

  // ������� �������:
  Expression * getOperand1() const { return (*this)[0]; }
  Expression * getOperand2() const { return (*this)[1]; }

  // �������� �������������� � ������
  operator string () const {
    return "(" + (string)*(operands[0]) + operSign + (string)*(operands[1]) + ')';
  }

  // �������� ���������� �������� ���������� � �������� ���������
  Constant * evaluate(const Context & ctx) const;

  // �������� ����� ���� � ��� �� ������ ��������, �� ������� ����������
  Expression * copyWithNewArgs(Expression** newOperands) const {
    return new Binary(operSign, newOperands[0], newOperands[1]);
  }

  // �������� ��������� ����
  void accept(Visitor & visitor) { visitor.visit(this); }
};

//==============================================================
// ����� UnaryFunction ������������ ���������, ��������� ��
// ����� ������� � �� ���������, ������� � ���� �������
// �������� ����������
//==============================================================

class UnaryFunction : public Operator {
public :

  // �����������:
  UnaryFunction(string sign, Expression *op) 
     : Operator(sign, &op, 1) {}

  // �������� ����
  string what() const { return UNARY_FUNCTION; }

  // ������� �������:
  Expression * getOperand() const { return (*this)[0]; }

  // �������� ���������� �������� ���������� � �������� ���������
  Constant * evaluate(const Context & ctx) const;

  // �������� ����� ���� � ��� �� ������ ��������, �� ������� ����������
  Expression * copyWithNewArgs(Expression** newOperands) const {
    return new UnaryFunction(operSign, *newOperands);
  }

  // �������� ��������� ����
  void accept(Visitor & visitor) { visitor.visit(this); }
};

#endif
