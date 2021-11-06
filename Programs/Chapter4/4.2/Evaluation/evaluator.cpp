/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.2. Вычисления по формулам                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : evaluator.cpp                                    *
*  Описание : Описание операций класса Evaluator для           *
*             вычисления значения выражения, представленного   *
*             в виде синнтаксического дерева                   *
***************************************************************/

#include "expressionext.h"
#include "evaluator.h"

void Evaluator::visit(Operator * opNode) {
  if (opNode->what() == BINARY) {
    Evaluator ev1(context);
    Evaluator ev2(context);
    ((Binary*)opNode)->getOperand1()->accept(ev1);
    ((Binary*)opNode)->getOperand2()->accept(ev2);
    Integer * value1 = (Integer*)ev1.getResult();
    Integer * value2 = (Integer*)ev2.getResult();
    if (value1 != NULL && value2 != NULL) {
      switch (((Binary*)opNode)->getOperSign()[0]) {
        case '+': 
          result = new Integer(value1->getValue() + value2->getValue());
          break;
        case '-': 
          result = new Integer(value1->getValue() - value2->getValue());
          break;
        case '*': 
          result = new Integer(value1->getValue() * value2->getValue());
          break;
        case '/': 
          result = new Integer(value1->getValue() / value2->getValue());
          break;
        case '%': 
          result = new Integer(value1->getValue() % value2->getValue());
          break;
      }
    }
  } else if (opNode->what() == UNARY_FUNCTION) {
    ((UnaryFunction*)opNode)->getOperand()->accept(*this);
    if (result == NULL) return;
    Integer * argValue = (Integer*)result;
    string operSign = ((Binary*)opNode)->getOperSign();
    if (operSign == "abs") {
      result = argValue->getValue() < 0 ?
           new Integer(-argValue->getValue()) :
           argValue;
    } else if (operSign == "sign") {
      result = new Integer(argValue->getValue() < 0 ? -1 :
                           argValue->getValue() > 0 ? 1 : 0);
    } else if (operSign == "sqr") {
      int arg = argValue->getValue();
      result = new Integer(arg * arg);
    } else {
      result = NULL;
    }
  }
}
