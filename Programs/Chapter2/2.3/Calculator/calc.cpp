/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.3. Стеки и очереди                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : calc.cpp                                         *
*  Описание : Функции для вычисления значения выражения на     *
*             двух стеках                                      *
***************************************************************/

#include "lexical.h"    // Классы лексического анализа
#include "operator.h"   // Представление арифметических операторов
#include "stack.h"
#include "stackfactory.h"
#include "calc.h"

// Переменные, представляющие абстрактные фабрики для
// создания стеков целых значений и операторов.

extern StackFactory<int> * stackIntFactory;
extern StackFactory<Operator> * stackOpFactory;

//==============================================================
// Функция doOperator выполняет одно из действий (+, -, * или /),
// которое находится на вершине стека операторов, над двумя
// целыми значениями, которые выталкиваются с вершины стека значений.
// Результат помещается обратно в стек значений.
//==============================================================

void doOperator(
          Stack<int> & operands,         // стек операндов
          Stack<Operator> & operators    // стек операций
         ) {
  int op2 = operands.top();       // правый (второй) операнд
  operands.pop();
  int op1 = operands.top();       // левый (первый) операнд
  operands.pop();
  char opSign = operators.top().getSign();  // знак операции
  operators.pop();
  // выполнение операции и запись результата в стек значений:
  switch (opSign) {
    case '+': 
      operands.push(op1 + op2);
      break;
    case '-':
      operands.push(op1 - op2);
      break;
    case '*':
      operands.push(op1 * op2);
      break;
    case '/':
      operands.push(op1 / op2);
      break;
  }
}

//==============================================================
// Функция doOperators выполняет ряд операций, знаки которых
// находятся на вершине стека операторов. Вычисления прекращаются,
// когда стек операторов будет пуст или на его вершине окажется
// оператор с более низким приоритетом, чем заданный приоритет minPrio.
//==============================================================

void doOperators(
          Stack<int> & operands,       // стек операндов
          Stack<Operator> & operators, // стек операторов
          int minPrio                  // граничный приоритет
         ) {
  // цикл выполнения операций:
  while (!operators.empty() && 
         operators.top().getPrio() >= minPrio) {
    doOperator(operands, operators);
  }
}

//==============================================================
// Функция exprValue вычисляет значение выражения с целыми
// операндами. Она использует лексический анализатор для
// получения значений операндов, скобок и знаков операций.
//==============================================================

int exprValue(char * expr) {
  // Создание стеков операндов и операций с помощью соответствующих "фабрик"
  Stack<int> * operands = stackIntFactory->newStack();
  Stack<Operator> * operators = stackOpFactory->newStack();
  // Лексический анализатор:
  LexAnalyzer analyzer(expr);

  try {
    // Цикл анализа по лексемам входной строки
    while (analyzer.hasNext()) {
      Lexical lex = analyzer.next();  // очередная лексема
      switch (lex.getLexClass()) {
        case Lexical::OPERAND:
          // значение операнда записывается в стек операндов
          operands->push(lex.getValue());
          break;
        case Lexical::RIGHTPAR:
          // При обнаружении правой скобки все операции, находящиеся 
          // в стеке операций выше соответствующей левой скобки, выполняются.
          // Левая скобка вычеркивается из стека
          doOperators(*operands, *operators, 1);
          operators->pop();
          break;
        case Lexical::OPERATOR:
          // При обнаружении знака операции выполняются все операции,
          // имеющие такой же или больший приоритет, знаки которых 
          // находятся в стеке операций.
          { Operator newOp(lex.getOperSign());
            doOperators(*operands, *operators, newOp.getPrio());
            operators->push(newOp); 
          }
          break;
        case Lexical::LEFTPAR:
          // Левая скобка просто записывается в стек операций.
          operators->push(Operator('('));
          break;
      }
    }
    // Анализ выражения закончен, осталось выполнить операции,
    // знаки которых, возможно, еще находятся в стеке операций.
    doOperators(*operands, *operators, 0);
    // Результат вычислений находится на вершине стека операндов.
    int result = operands->top();
    // Уничтожаем стеки
    delete operands;
    delete operators;
    return result;
  } catch (StackOverflow) {
    // Исключительная ситуация StackOverflow может возникнуть, если
    // уровень вложенности скобок слишком велик, и стек операторов не
    // вмещает все "отложенные" знаки операций.
    delete operands;
    delete operators;
    throw WrongExpression();
  } catch (StackUnderflow) {
    // Исключительная ситуация StackUnderflow может возникнуть, если
    // выражение содержит ошибку.
    delete operands;
    delete operators;
    throw WrongExpression();
  }
}
