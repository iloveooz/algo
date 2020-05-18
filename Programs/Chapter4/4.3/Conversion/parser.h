/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.3. �������������� ������                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : parser.h                                         *
*  �������� : �������� ������ ��� ������� � ����������         *
*             ��������������� ������ ���������                 *
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

class Parser {
public :
  // ����� ��� ���������� ��������������� ������ ���������
  static Expression * parse(const string & source);

private :
  //=============================================================
  // ���������� stExprFactory � stOperFactory ������ �������
  // ������ ��� ��������� ����� ��������� (����� ���������������
  // ������) � ����� �������� (�������� ������ LexOperator)
  //=============================================================
  static StackFactory<Expression*> * stExprFactory;
  static StackFactory<LexOperator*> * stOperFactory;

  static void doOperator(
       Stack<Expression*> *operands,      // ���� ��������� �������� �������
       Stack<LexOperator*> *operators     // ���� ����������
               );

  static void doOperators(
       Stack<Expression*> *operands,      // ���� ���������
       Stack<LexOperator*> *operators,    // ���� ����������
       int minPrio                        // ��������� ���������
                );
};

#endif
