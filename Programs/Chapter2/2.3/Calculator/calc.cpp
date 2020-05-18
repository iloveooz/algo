/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.3. ����� � �������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : calc.cpp                                         *
*  �������� : ������� ��� ���������� �������� ��������� ��     *
*             ���� ������                                      *
***************************************************************/

#include "lexical.h"    // ������ ������������ �������
#include "operator.h"   // ������������� �������������� ����������
#include "stack.h"
#include "stackfactory.h"
#include "calc.h"

// ����������, �������������� ����������� ������� ���
// �������� ������ ����� �������� � ����������.

extern StackFactory<int> * stackIntFactory;
extern StackFactory<Operator> * stackOpFactory;

//==============================================================
// ������� doOperator ��������� ���� �� �������� (+, -, * ��� /),
// ������� ��������� �� ������� ����� ����������, ��� �����
// ������ ����������, ������� ������������� � ������� ����� ��������.
// ��������� ���������� ������� � ���� ��������.
//==============================================================

void doOperator(
          Stack<int> & operands,         // ���� ���������
          Stack<Operator> & operators    // ���� ��������
         ) {
  int op2 = operands.top();       // ������ (������) �������
  operands.pop();
  int op1 = operands.top();       // ����� (������) �������
  operands.pop();
  char opSign = operators.top().getSign();  // ���� ��������
  operators.pop();
  // ���������� �������� � ������ ���������� � ���� ��������:
  switch (opSign) {
    case '+': 
      operands.push(op1 + op2);
      break;
    case '-':
      operands.push(op1 - op2);
      break;
    case '*':
      operands.push(op1 * op2);
      break;
    case '/':
      operands.push(op1 / op2);
      break;
  }
}

//==============================================================
// ������� doOperators ��������� ��� ��������, ����� �������
// ��������� �� ������� ����� ����������. ���������� ������������,
// ����� ���� ���������� ����� ���� ��� �� ��� ������� ��������
// �������� � ����� ������ �����������, ��� �������� ��������� minPrio.
//==============================================================

void doOperators(
          Stack<int> & operands,       // ���� ���������
          Stack<Operator> & operators, // ���� ����������
          int minPrio                  // ��������� ���������
         ) {
  // ���� ���������� ��������:
  while (!operators.empty() && 
         operators.top().getPrio() >= minPrio) {
    doOperator(operands, operators);
  }
}

//==============================================================
// ������� exprValue ��������� �������� ��������� � ������
// ����������. ��� ���������� ����������� ���������� ���
// ��������� �������� ���������, ������ � ������ ��������.
//==============================================================

int exprValue(char * expr) {
  // �������� ������ ��������� � �������� � ������� ��������������� "������"
  Stack<int> * operands = stackIntFactory->newStack();
  Stack<Operator> * operators = stackOpFactory->newStack();
  // ����������� ����������:
  LexAnalyzer analyzer(expr);

  try {
    // ���� ������� �� �������� ������� ������
    while (analyzer.hasNext()) {
      Lexical lex = analyzer.next();  // ��������� �������
      switch (lex.getLexClass()) {
        case Lexical::OPERAND:
          // �������� �������� ������������ � ���� ���������
          operands->push(lex.getValue());
          break;
        case Lexical::RIGHTPAR:
          // ��� ����������� ������ ������ ��� ��������, ����������� 
          // � ����� �������� ���� ��������������� ����� ������, �����������.
          // ����� ������ ������������� �� �����
          doOperators(*operands, *operators, 1);
          operators->pop();
          break;
        case Lexical::OPERATOR:
          // ��� ����������� ����� �������� ����������� ��� ��������,
          // ������� ����� �� ��� ������� ���������, ����� ������� 
          // ��������� � ����� ��������.
          { Operator newOp(lex.getOperSign());
            doOperators(*operands, *operators, newOp.getPrio());
            operators->push(newOp); 
          }
          break;
        case Lexical::LEFTPAR:
          // ����� ������ ������ ������������ � ���� ��������.
          operators->push(Operator('('));
          break;
      }
    }
    // ������ ��������� ��������, �������� ��������� ��������,
    // ����� �������, ��������, ��� ��������� � ����� ��������.
    doOperators(*operands, *operators, 0);
    // ��������� ���������� ��������� �� ������� ����� ���������.
    int result = operands->top();
    // ���������� �����
    delete operands;
    delete operators;
    return result;
  } catch (StackOverflow) {
    // �������������� �������� StackOverflow ����� ����������, ����
    // ������� ����������� ������ ������� �����, � ���� ���������� ��
    // ������� ��� "����������" ����� ��������.
    delete operands;
    delete operators;
    throw WrongExpression();
  } catch (StackUnderflow) {
    // �������������� �������� StackUnderflow ����� ����������, ����
    // ��������� �������� ������.
    delete operands;
    delete operators;
    throw WrongExpression();
  }
}
