/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.1. ������������� ���������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : copier.h                                         *
*  �������� : ����������� ���������� ��� �������� �����        *
*             ��������������� ������ ���������                 *
***************************************************************/

#ifndef __COPIER_H
#define __COPIER_H

class Copier : public Visitor {
  // ����������� ����� ���������
  Expression * copy;

public :
  // �����������
  Copier() : copy(NULL) {}
  // ���������� ������ ����� ���� � ���������� copy
  void visit(Integer * intNode) { copy = new Integer(intNode->getValue()); }
  void visit(Variable * varNode) { copy = new Variable(varNode->getVariable()); }
  void visit(Operator * opNode) {
    Copier op1Copier, op2Copier;
    opNode->getOperand1()->accept(op1Copier);
    opNode->getOperand2()->accept(op2Copier);
    copy = new Operator(opNode->getOperSign(), op1Copier.getResult(), op2Copier.getResult());
  }

  // ����� getResult() ������������ ������ � ���������� ������
  Expression * getResult() { return copy; }
};

#endif
