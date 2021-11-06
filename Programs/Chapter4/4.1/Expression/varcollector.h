/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.1. Представление выражений                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : varcollector.h                                   *
*  Описание : Определение простого посетителя для решения      *
*             задачи о сборе информации о переменных выражения *
***************************************************************/

#ifndef __VAR_COLLECTOR_H
#define __VAR_COLLECTOR_H

class VariableCollector : public Visitor {
  // Словарь переменных
  HashDictionary dict;

public :
  // Посетители накапливают информацию в словаре. Единственный
  // узел, добавляющий переменные - это узел типа Variable
  void visit(Integer * intNode) {}
  void visit(Variable * varNode) { dict.add(varNode->getVariable()); }
  void visit(Operator * opNode) {
    opNode->getOperand1()->accept(*this);
    opNode->getOperand2()->accept(*this);
  }

  // Метод getResult() обеспечивает доступ к результату работы
  HashDictionary & getResult() { return dict; }
};

#endif
