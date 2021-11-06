/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.2. Вычисления по формулам                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : parser.cpp                                       *
*  Описание : Описание операций класса Parser для анализа      *
*             выражения и построения синтаксического дерева    *
***************************************************************/

#include "parser.h"
#include "list.h"
#include "liststack.h"

using namespace std;

StackFactory<Expression*> * Parser::stExprFactory = new ListStackFactory<Expression*>;
StackFactory<LexOperator*> * Parser::stOperFactory = new ListStackFactory<LexOperator*>;

//===============================================================
// Функция "выполнения" операции на стеках
//===============================================================
void Parser::doOperator(
       Stack<Expression*> *operands,      // стек операндов содержит деревья
       Stack<LexOperator*> *operators     // стек операторов
               ) {
  // Операнды для операции извлекаются из стека операндов:
  Expression *op2 = **operands;  operands->pop();
  Expression *op1 = **operands;  operands->pop();
  // Знак операции берется из стека операций:
  LexOperator * op = **operators;
  char opSign[2] = { op->getOperSign(), 0 };
  operators->pop();
  delete op;
  // В качестве результата "выполнения" операции строится новый
  // узел, содержащий знак операции и два поддерева
  operands->push(new Binary(string(opSign), op1, op2));
}

//===============================================================
// Функция "выполнения" серии операций согласно их приоритетам
//===============================================================
void Parser::doOperators(
       Stack<Expression*> *operands,      // стек операндов
       Stack<LexOperator*> *operators,    // стек операторов
       int minPrio                        // граничный приоритет
                ) {
  while (!operators->empty() &&
         (**operators)->getPrio() >= minPrio) {
    doOperator(operands, operators);
  }
}

//===============================================================
// Основная функция анализа строки и построения дерева выражения
//===============================================================
Expression * Parser::parse(const string & source) {
  // Константы для значений "ожидаемого" класса лексемы
  const int WAIT_OPERAND = 1;
  const int WAIT_OPERATOR = 2;

  // Стеки операндов и операций создаются стандартным образом
  // с помощью "фабрик" по производству стеков. Чтобы
  // избежать "утечки памяти" надо аккуратно уничтожить
  // эти стеки при нормальном или аварийном завершении анализа.
  Stack<Expression*> *operands = stExprFactory->newStack();
  Stack<LexOperator*> *operators = stOperFactory->newStack();
  // лексический анализатор выражения:
  LexAnalizer analizer(source);
  // Флажок ожидаемой лексемы
  int waitFlag = WAIT_OPERAND;

  try {
    // Цикл по лексемам исходной строки
    while (analizer.hasMoreElements()) {
      Lexical *lex = *analizer;
      ++analizer;
      if (lex == NULL) {
        delete operands;
        delete operators;
        throw ParseException("Неизвестная лексема",
                             analizer.getCurrentPosition());
      }
      if (waitFlag == WAIT_OPERAND) {
        switch (lex->getLexClass()) {
          case Lexical::NUMBER:
            // число преобразуется в узел синтаксического дерева
            // и записывается в стек операндов
            operands->push(new Integer(
                                  ((LexNumber*)lex)->getNumber()));
            waitFlag = WAIT_OPERATOR;
            delete lex;
            break;
          case Lexical::VARIABLE:
            // переменная преобразуется в узел синтаксического дерева
            // и записывается в стек операндов
            operands->push(new Variable(
                                  ((LexVariable*)lex)->getVariable()));
            waitFlag = WAIT_OPERATOR;
            delete lex;
            break;
          case Lexical::LEFTPAR:
            // скобка просто записывается в стек операций
            operators->push((LexOperator*)lex);
            break;
          default:
            // лексема неожидаемого класса свидетельствует об ошибке
            delete lex;
            delete operands;
            delete operators;
            throw ParseException("Ожидался операнд",
                                 analizer.getCurrentPosition());
        }
      } else {  // waitFlag == WAIT_OPERATOR
        switch (lex->getLexClass()) {
          case Lexical::RIGHTPAR:
            // появление закрывающей скобки вызывает "выполнение"
            // операций и удаление соответствующей открывающей скобки
            {doOperators(operands, operators, 1);
            LexOperator * op = **operators;
            operators->pop();
            delete op;
            delete lex;
            }
            break;
          case Lexical::OPERATOR:
            // выполняем операции с приоритетом не меньше текущего
            doOperators(operands, operators, ((LexOperator*)lex)->getPrio());
            // знак очередной операции записываем в стек операций
            operators->push((LexOperator*)lex);
            waitFlag = WAIT_OPERAND;
            break;
          default:
            // лексема неожидаемого класса свидетельствует об ошибке
            delete lex;
            delete operands;
            delete operators;
            throw ParseException("Ожидался знак операции",
                                 analizer.getCurrentPosition());
        }
      }
    }
    // выполняем последние оставшиеся в стеке операции
    doOperators(operands, operators, 0);
    // результат – последнее значение в стеке операндов
    Expression * result = **operands;
    delete operands;
    delete operators;
    return result;
  } catch (StackUnderflow ex) {
    // исчерпание стека свидетельствует об ошибке в скобочной
    // структуре выражения
    delete operands;
    delete operators;
    throw ParseException("Ошибка в скобочной структуре выражения",
                         analizer.getCurrentPosition());
  }
}
