/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.3. �������������� ������                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : diff.cpp                                         *
*  �������� : �������� �������� ������ Diff ��� ����������     *
*             ������ ����������� ���������                     *
***************************************************************/

#include "expressionext.h"
#include "diff.h"

Constant * Diff::zero = new Integer(0);
Constant * Diff::one = new Integer(1);

void Diff::visit(Operator * opNode) {
  if (opNode->what() != BINARY) {
    // �������������� ������ �������� ���������
    result = opNode;
  } else {
    Binary * binOperator = (Binary *)opNode;
    
    // �������� �������� �������� � ��������� �� �����������
    // � ������� ��������� ���������� ��� ���� ���� �����������:
    Diff visitor1(variable), visitor2(variable);
    Expression * op1 = binOperator->getOperand1();
    op1->accept(visitor1);
    Expression * op1dash = visitor1.getResult();
    Expression * op2 = binOperator->getOperand2();
    op2->accept(visitor2);
    Expression * op2dash = visitor2.getResult();
    string oper = binOperator->getOperSign();

    // ������ ��������� ��������� ������� ������ ���������:
    // ������ 1: ����������� ����� � ��������
    if (oper == "+" || oper == "-") {
      result = new Binary(oper, op1dash, op2dash);
    // ������ 2: ����������� ������������
    } else if (oper == "*") {
      result = new Binary("+", new Binary("*", op1dash, op2),
                               new Binary("*", op1, op2dash));
    // ������ 3: ����������� ��������
    } else if (oper == "/") {
      result = new Binary("/",
                   new Binary("-", new Binary("*", op1dash, op2),
                                   new Binary("*", op1, op2dash)),
                   new Binary("*", op2, op2));
    // ��� ������ ������ �������� ��������� �� ���������
    } else {
      result = NULL;
    }
  }
}
