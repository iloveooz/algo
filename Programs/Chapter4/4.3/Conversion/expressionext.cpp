/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.3. �������������� ������                          *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : expressionext.cpp                                *
*  �������� : ���������� �������� ���������� ��������          *
*             ��������� ��� ����� ���� Binary � UnaryFunction  *
***************************************************************/

#include "expressionext.h"

Constant * Binary::evaluate(const Context & ctx) const {
  Expression * value1 = getOperand1()->evaluate(ctx);
  Expression * value2 = getOperand2()->evaluate(ctx);
  if (value1 == NULL || value2 == NULL) return NULL;
  if (value1->what() != INTEGER || value2->what() != INTEGER) return NULL;
  switch (operSign[0]) {
    case '+': return new Integer(
      ((Integer*)value1)->getValue() + ((Integer*)value2)->getValue());
    case '-': return new Integer(
      ((Integer*)value1)->getValue() - ((Integer*)value2)->getValue());
    case '*': return new Integer(
      ((Integer*)value1)->getValue() * ((Integer*)value2)->getValue());
    case '/': return new Integer(
      ((Integer*)value1)->getValue() / ((Integer*)value2)->getValue());
    case '%': return new Integer(
      ((Integer*)value1)->getValue() % ((Integer*)value2)->getValue());
  }
  return NULL;
}

Constant * UnaryFunction::evaluate(const Context & ctx) const {
  Expression * argValue = getOperand()->evaluate(ctx);
  if (argValue == NULL || argValue->what() != INTEGER) return NULL;
  if (operSign == "abs") {
    return ((Integer*)argValue)->getValue() < 0 ?
           new Integer(-((Integer*)argValue)->getValue()) :
           (Integer*)argValue;
  } else if (operSign == "sign") {
    return new Integer(((Integer*)argValue)->getValue() < 0 ? -1 :
                       ((Integer*)argValue)->getValue() > 0 ? 1 : 0);
  } else if (operSign == "sqr") {
    int arg = ((Integer*)argValue)->getValue();
    return new Integer(arg * arg);
  } else {
    return NULL;
  }
}
