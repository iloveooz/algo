/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.1. Представление выражений                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Проверка различных операций над представлением   *
*             выражений в виде синтаксического дерева          *
***************************************************************/

#include <string>
#include <iostream>
#include "expression.h"
#include "dictionary.h"
#include "varcollector.h"
#include "copier.h"

using namespace std;

//==============================================================
// Тестирование функций parse и (string) для выражения
//==============================================================

int main() {
  // Сначала преобразуем строку в синтаксическое дерево выражения
  Expression * expr = Expression::parse("(a + b)*(c + d) + 1 + 2*a");

  // А потом преобразуем это дерево в строку и выводим его.
  cout << (string)*expr << endl;
  // Копируем выражение и проверяем, что при уничтожении исходного
  // выражения его копия по-прежнему существует
  Expression * exprCopy = expr->copy();
  delete expr;
  cout << (string)*exprCopy << endl;

  // Сбор информации о переменных выражения с помощью прямого рекурсивного вызова
  HashDictionary * vars = exprCopy->allVariables();

  // Печать результата
  cout << *vars << endl;

  delete vars;

  // Сбор информации о переменных выражения с помощью посетителя
  VariableCollector collector;
  exprCopy->accept(collector);

  // Печать результата
  cout << collector.getResult() << endl;

  // Теперь строим копию выражения с помощью посетителя:
  Copier copier;
  exprCopy->accept(copier);
  Expression * copy2 = copier.getResult();

  // Проверяем совпадение с помощью операции сравнения
  cout << "Expression is " << (*copy2 == *exprCopy ? "equal" : "not equal") << " to its copy" << endl;

  delete exprCopy;

  // Печатаем новую копию
  cout << (string)*copy2 << endl;

  return 0;
}
