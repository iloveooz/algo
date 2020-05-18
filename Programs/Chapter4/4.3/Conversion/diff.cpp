/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.3. Преобразование формул                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : diff.cpp                                         *
*  Описание : Описание операций класса Diff для вычисления     *
*             первой производной выражения                     *
***************************************************************/

#include "expressionext.h"
#include "diff.h"

Constant * Diff::zero = new Integer(0);
Constant * Diff::one = new Integer(1);

void Diff::visit(Operator * opNode) {
  if (opNode->what() != BINARY) {
    // Дифференцируем только бинарные операторы
    result = opNode;
  } else {
    Binary * binOperator = (Binary *)opNode;
    
    // Выделяем операнды операции и вычисляем их производные
    // с помощью созданных специально для этой цели посетителей:
    Diff visitor1(variable), visitor2(variable);
    Expression * op1 = binOperator->getOperand1();
    op1->accept(visitor1);
    Expression * op1dash = visitor1.getResult();
    Expression * op2 = binOperator->getOperand2();
    op2->accept(visitor2);
    Expression * op2dash = visitor2.getResult();
    string oper = binOperator->getOperSign();

    // Теперь разбираем отдельные частные случаи упрощений:
    // Случай 1: производная суммы и разности
    if (oper == "+" || oper == "-") {
      result = new Binary(oper, op1dash, op2dash);
    // Случай 2: производная произведения
    } else if (oper == "*") {
      result = new Binary("+", new Binary("*", op1dash, op2),
                               new Binary("*", op1, op2dash));
    // Случай 3: производная частного
    } else if (oper == "/") {
      result = new Binary("/",
                   new Binary("-", new Binary("*", op1dash, op2),
                                   new Binary("*", op1, op2dash)),
                   new Binary("*", op2, op2));
    // Для других знаков операций результат не определен
    } else {
      result = NULL;
    }
  }
}
