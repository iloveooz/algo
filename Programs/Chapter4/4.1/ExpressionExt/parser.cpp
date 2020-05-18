/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.1. ������������� ���������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : parser.cpp                                       *
*  �������� : �������� �������� ������ Parser ��� �������      *
*             ��������� � ���������� ��������������� ������    *
***************************************************************/

#include "parser.h"
#include "list.h"
#include "liststack.h"

using namespace std;

StackFactory<Expression*> * Parser::stExprFactory = new ListStackFactory<Expression*>;
StackFactory<LexOperator*> * Parser::stOperFactory = new ListStackFactory<LexOperator*>;

//===============================================================
// ������� "����������" �������� �� ������
//===============================================================
void Parser::doOperator(
       Stack<Expression*> *operands,      // ���� ��������� �������� �������
       Stack<LexOperator*> *operators     // ���� ����������
               ) {
  // �������� ��� �������� ����������� �� ����� ���������:
  Expression *op2 = **operands;  operands->pop();
  Expression *op1 = **operands;  operands->pop();
  // ���� �������� ������� �� ����� ��������:
  LexOperator * op = **operators;
  char opSign[2] = { op->getOperSign(), 0 };
  operators->pop();
  delete op;
  // � �������� ���������� "����������" �������� �������� �����
  // ����, ���������� ���� �������� � ��� ���������
  operands->push(new Binary(string(opSign), op1, op2));
}

//===============================================================
// ������� "����������" ����� �������� �������� �� �����������
//===============================================================
void Parser::doOperators(
       Stack<Expression*> *operands,      // ���� ���������
       Stack<LexOperator*> *operators,    // ���� ����������
       int minPrio                        // ��������� ���������
                ) {
  while (!operators->empty() &&
         (**operators)->getPrio() >= minPrio) {
    doOperator(operands, operators);
  }
}

//===============================================================
// �������� ������� ������� ������ � ���������� ������ ���������
//===============================================================
Expression * Parser::parse(const string & source) {
  // ��������� ��� �������� "����������" ������ �������
  const int WAIT_OPERAND = 1;
  const int WAIT_OPERATOR = 2;

  // ����� ��������� � �������� ��������� ����������� �������
  // � ������� "������" �� ������������ ������. �����
  // �������� "������ ������" ���� ��������� ����������
  // ��� ����� ��� ���������� ��� ��������� ���������� �������.
  Stack<Expression*> *operands = stExprFactory->newStack();
  Stack<LexOperator*> *operators = stOperFactory->newStack();
  // ����������� ���������� ���������:
  LexAnalizer analizer(source);
  // ������ ��������� �������
  int waitFlag = WAIT_OPERAND;

  try {
    // ���� �� �������� �������� ������
    while (analizer.hasMoreElements()) {
      Lexical *lex = *analizer;
      ++analizer;
      if (lex == NULL) {
        delete operands;
        delete operators;
        throw ParseException("����������� �������",
                             analizer.getCurrentPosition());
      }
      if (waitFlag == WAIT_OPERAND) {
        switch (lex->getLexClass()) {
          case Lexical::NUMBER:
            // ����� ������������� � ���� ��������������� ������
            // � ������������ � ���� ���������
            operands->push(new Integer(
                                  ((LexNumber*)lex)->getNumber()));
            waitFlag = WAIT_OPERATOR;
            delete lex;
            break;
          case Lexical::VARIABLE:
            // ���������� ������������� � ���� ��������������� ������
            // � ������������ � ���� ���������
            operands->push(new Variable(
                                  ((LexVariable*)lex)->getVariable()));
            waitFlag = WAIT_OPERATOR;
            delete lex;
            break;
          case Lexical::LEFTPAR:
            // ������ ������ ������������ � ���� ��������
            operators->push((LexOperator*)lex);
            break;
          default:
            // ������� ������������ ������ ��������������� �� ������
            delete lex;
            delete operands;
            delete operators;
            throw ParseException("�������� �������",
                                 analizer.getCurrentPosition());
        }
      } else {  // waitFlag == WAIT_OPERATOR
        switch (lex->getLexClass()) {
          case Lexical::RIGHTPAR:
            // ��������� ����������� ������ �������� "����������"
            // �������� � �������� ��������������� ����������� ������
            {doOperators(operands, operators, 1);
            LexOperator * op = **operators;
            operators->pop();
            delete op;
            delete lex;
            }
            break;
          case Lexical::OPERATOR:
            // ��������� �������� � ����������� �� ������ ��������
            doOperators(operands, operators, ((LexOperator*)lex)->getPrio());
            // ���� ��������� �������� ���������� � ���� ��������
            operators->push((LexOperator*)lex);
            waitFlag = WAIT_OPERAND;
            break;
          default:
            // ������� ������������ ������ ��������������� �� ������
            delete lex;
            delete operands;
            delete operators;
            throw ParseException("�������� ���� ��������",
                                 analizer.getCurrentPosition());
        }
      }
    }
    // ��������� ��������� ���������� � ����� ��������
    doOperators(operands, operators, 0);
    // ��������� � ��������� �������� � ����� ���������
    Expression * result = **operands;
    delete operands;
    delete operators;
    return result;
  } catch (StackUnderflow ex) {
    // ���������� ����� ��������������� �� ������ � ���������
    // ��������� ���������
    delete operands;
    delete operators;
    throw ParseException("������ � ��������� ��������� ���������",
                         analizer.getCurrentPosition());
  }
}
