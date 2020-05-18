/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.3. �������������� ������                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : simplifier.cpp                                   *
*  �������� : �������� �������� ������ Simplifier ���          *
*             ���������� ��������� �������� ��������           *
***************************************************************/

#include "expressionext.h"
#include "simplifier.h"

Constant * Simplifier::zero = new Integer(0);
Constant * Simplifier::one = new Integer(1);

void Simplifier::visit(Operator * opNode) {
  if (opNode->what() != BINARY) {
    // �������� ������ �������� ���������
    result = opNode;
  } else {
    Binary * binOperator = (Binary *)opNode;
    
    // �������� �������� �������� � �������� �� � �������
    // ��������� ���������� ��� ���� ���� �����������:
    Simplifier visitor1, visitor2;
    binOperator->getOperand1()->accept(visitor1);
    binOperator->getOperand2()->accept(visitor2);
    Expression * op1 = visitor1.getResult();
    Expression * op2 = visitor2.getResult();
    string oper = binOperator->getOperSign();

    // ������ ��������� ��������� ������� ������ ���������:
    // ������ 1: 0+� � 1*� �������� �� �
    if ((*op1 == *zero && oper == "+") || (*op1 == *one && oper == "*")) {
      result = op2;
    // ������ 2: �+0, e-0, e*1 � e/1 �������� �� �
    } else if ((*op2 == *zero && (oper == "+" || oper == "-")) || 
               (*op2 == *one && (oper == "*" || oper == "/"))) {
      result = op1;
    // ������ 3: �*0, 0*e � 0/e �������� �� ����
    } else if (((*op1 == *zero || *op2 == *zero) && oper == "*") ||
               ((*op1 == *zero && *op2 != *zero) && oper == "/")) {
      result = zero;
    // ������ 4: �������� - ���������; ���������� ����������
    } else if (op1->isConst() && op2->isConst()) {
      // ����������� ���������� ����� ��������� � ������ ���������
      Context empty;
      result = (new Binary(oper, op1, op2))->evaluate(empty);
    // ������ 5: �����. ���� �������� ������ �� �����
    //           �������� � ���������� ���������
    } else {
      result = new Binary(oper, op1, op2);
    }
  }
}
