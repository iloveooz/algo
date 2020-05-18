/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.3. Преобразование формул                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : simplifier.cpp                                   *
*  Описание : Описание операций класса Simplifier для          *
*             реализации упрощения бинарной операции           *
***************************************************************/

#include "expressionext.h"
#include "simplifier.h"

Constant * Simplifier::zero = new Integer(0);
Constant * Simplifier::one = new Integer(1);

void Simplifier::visit(Operator * opNode) {
  if (opNode->what() != BINARY) {
    // Упрощаем только бинарные операторы
    result = opNode;
  } else {
    Binary * binOperator = (Binary *)opNode;
    
    // Выделяем операнды операции и упрощаем их с помощью
    // созданных специально для этой цели посетителей:
    Simplifier visitor1, visitor2;
    binOperator->getOperand1()->accept(visitor1);
    binOperator->getOperand2()->accept(visitor2);
    Expression * op1 = visitor1.getResult();
    Expression * op2 = visitor2.getResult();
    string oper = binOperator->getOperSign();

    // Теперь разбираем отдельные частные случаи упрощений:
    // Случай 1: 0+е и 1*е заменяем на е
    if ((*op1 == *zero && oper == "+") || (*op1 == *one && oper == "*")) {
      result = op2;
    // Случай 2: е+0, e-0, e*1 и e/1 заменяем на е
    } else if ((*op2 == *zero && (oper == "+" || oper == "-")) || 
               (*op2 == *one && (oper == "*" || oper == "/"))) {
      result = op1;
    // Случай 3: е*0, 0*e и 0/e заменяем на ноль
    } else if (((*op1 == *zero || *op2 == *zero) && oper == "*") ||
               ((*op1 == *zero && *op2 != *zero) && oper == "/")) {
      result = zero;
    // Случай 4: операнды - константы; производим вычисления
    } else if (op1->isConst() && op2->isConst()) {
      // Константные вычисления можно проводить в пустом контексте
      Context empty;
      result = (new Binary(oper, op1, op2))->evaluate(empty);
    // Случай 5: общий. Узел строится заново из знака
    //           операции и упрощенных операндов
    } else {
      result = new Binary(oper, op1, op2);
    }
  }
}
