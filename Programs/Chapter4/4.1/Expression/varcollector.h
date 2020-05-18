/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.1. ������������� ���������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : varcollector.h                                   *
*  �������� : ����������� �������� ���������� ��� �������      *
*             ������ � ����� ���������� � ���������� ��������� *
***************************************************************/

#ifndef __VAR_COLLECTOR_H
#define __VAR_COLLECTOR_H

class VariableCollector : public Visitor {
  // ������� ����������
  HashDictionary dict;

public :
  // ���������� ����������� ���������� � �������. ������������
  // ����, ����������� ���������� - ��� ���� ���� Variable
  void visit(Integer * intNode) {}
  void visit(Variable * varNode) { dict.add(varNode->getVariable()); }
  void visit(Operator * opNode) {
    opNode->getOperand1()->accept(*this);
    opNode->getOperand2()->accept(*this);
  }

  // ����� getResult() ������������ ������ � ���������� ������
  HashDictionary & getResult() { return dict; }
};

#endif
