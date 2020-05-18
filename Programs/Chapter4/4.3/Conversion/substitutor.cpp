/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.3. �������������� ������                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : substitutor.cpp                                  *
*  �������� : �������� �������� ������ Substitutor ���         *
*             ���������� ����������� ��������� ������ ����     *
*             ��������� ��������� ����������                   *
***************************************************************/

#include "expressionext.h"
#include "substitutor.h"

void Substitutor::visit(Operator * opNode) {
  int nOps = opNode->getArity();
  Expression ** newOperands = new Expression*[nOps];
  for (int i = 0; i < nOps; i++) {
    Substitutor opSubs(context);
    (*opNode)[i]->accept(opSubs);
    newOperands[i] = opSubs.getResult();
  }
  result = opNode->copyWithNewArgs(newOperands);
}
