/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.3. �������������� ������                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : substitutor.h                                    *
*  �������� : �������� ���������� ����� ���������������        *
*             ������ ��������� ��� ���������� ��� ��������     *
***************************************************************/

#ifndef __SUBSTITUTOR_H
#define __SUBSTITUTOR_H

#include "visitor.h"

//===============================================================
// ����� Substitutor ���������� ����������, ������� ��������
// ������ ����������� � ��������� ������ ���������� �� ���������
// ��������� �������� � ��� ���������.
//===============================================================
class Substitutor : public Visitor {
  Context * context;     // �������� ����������
  Expression * result;   // ��������� ����������

public :
  // �����������:
  Substitutor(Context * ctx) : context(ctx), result(NULL) {}
  // ������ ����������
  Expression * getResult() const { return result; }
  // �������� ��������� �����
  void visit(Constant * cNode) { result = cNode; }
  void visit(Variable * varNode) {
    Expression * substitution = context->find(varNode->getVariable());
    result = substitution ? substitution : varNode;
  }
  void visit(Operator * opNode);
};

#endif
