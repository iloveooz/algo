/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.2. Вычисления по формулам                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : expressionext.cpp                                *
*  Описание : Реализация операций вычисления значения          *
*             выражений для узлов типа Binary и UnaryFunction  *
***************************************************************/

#include "expressionext.h"

Constant * Binary::evaluate(const Context & ctx) const {
  Integer * value1 = (Integer*)getOperand1()->evaluate(ctx);
  Integer * value2 = (Integer*)getOperand2()->evaluate(ctx);
  if (value1 == NULL || value2 == NULL) return NULL;
  switch (operSign[0]) {
    case '+': return new Integer(value1->getValue() + value2->getValue());
    case '-': return new Integer(value1->getValue() - value2->getValue());
    case '*': return new Integer(value1->getValue() * value2->getValue());
    case '/': return new Integer(value1->getValue() / value2->getValue());
    case '%': return new Integer(value1->getValue() % value2->getValue());
  }
  return NULL;
}

Constant * UnaryFunction::evaluate(const Context & ctx) const {
  Integer * argValue = (Integer*)getOperand()->evaluate(ctx);
  if (argValue == NULL) return NULL;
  if (operSign == "abs") {
    return argValue->getValue() < 0 ?
           new Integer(-argValue->getValue()) :
           argValue;
  } else if (operSign == "sign") {
    return new Integer(argValue->getValue() < 0 ? -1 :
                       argValue->getValue() > 0 ? 1 : 0);
  } else if (operSign == "sqr") {
    int arg = argValue->getValue();
    return new Integer(arg * arg);
  } else {
    return NULL;
  }
}

