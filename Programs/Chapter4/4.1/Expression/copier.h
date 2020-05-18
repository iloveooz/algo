/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.1. Представление выражений                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : copier.h                                         *
*  Описание : Определение посетителя для создания копии        *
*             синтаксического дерева выражения                 *
***************************************************************/

#ifndef __COPIER_H
#define __COPIER_H

class Copier : public Visitor {
  // Построенная копия выражения
  Expression * copy;

public :
  // Конструктор
  Copier() : copy(NULL) {}
  // Посетители строят копию узла в переменной copy
  void visit(Integer * intNode) { copy = new Integer(intNode->getValue()); }
  void visit(Variable * varNode) { copy = new Variable(varNode->getVariable()); }
  void visit(Operator * opNode) {
    Copier op1Copier, op2Copier;
    opNode->getOperand1()->accept(op1Copier);
    opNode->getOperand2()->accept(op2Copier);
    copy = new Operator(opNode->getOperSign(), op1Copier.getResult(), op2Copier.getResult());
  }

  // Метод getResult() обеспечивает доступ к результату работы
  Expression * getResult() { return copy; }
};

#endif
