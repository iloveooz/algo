/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.3. Преобразование формул                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : substitutor.cpp                                  *
*  Описание : Описание операций класса Substitutor для         *
*             реализации подстановки выражения вместо всех     *
*             вхождений некоторой переменной                   *
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
