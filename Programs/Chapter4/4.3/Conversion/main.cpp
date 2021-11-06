/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.3. Преобразование формул                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Проверка различных операций над представлением   *
*             выражений в виде синтаксического дерева          *
***************************************************************/

#include <string>
#include <iostream>
#include "parser.h"
#include "expression.h"
#include "substitutor.h"
#include "simplifier.h"
#include "diff.h"

using namespace std;

//==============================================================
// Тестирование функций parse и (string) для выражения
//==============================================================

int main() {
  // Построим дерево формулы для кинетической энергии
  Expression * energy0 = Parser::parse("m * v * v / 2");
  cout << "Initial expression: " << (string)*energy0 << endl;

  // Создадим контекст, в котором переменной v соотвествует формула
  Context speed;
  speed.add("v", Parser::parse("v0 + a*t"));
  cout << "Substitution " << (string)*speed.find("v") << " instead of variable v" << endl;

  // Посетитель substitutor использует построенный контекст для замены
  Substitutor substitutor(&speed);
  energy0->accept(substitutor);

  // Берем новую формулу и печатаем ее
  Expression * energy1 = substitutor.getResult();
  cout << "Result: " << (string)*energy1 << endl;

  // Подставляем 0 вместо переменной v0
  speed.add("v0", Parser::parse("0")); 
  cout << "After substitution 0 instead of v0" << endl;

  energy1->accept(substitutor); 
  Expression * energy2 = substitutor.getResult(); 
  cout << (string)*energy2 << endl;

  // Упрощаем результат подстановки
  Simplifier simplifier;
  energy2->accept(simplifier);
  Expression * energy3 = simplifier.getResult(); 
  cout << "After simplification: " << (string)*energy3 << endl;

  // Делаем еще одну подстановку: нуль вместо переменной a...
  speed.add("a", Parser::parse("0"));
  energy3->accept(substitutor);
  Expression * energy4 = substitutor.getResult(); 
  cout << "0 substituted instead of \'a\': " << (string)*energy4 << endl;

  // ...и упрощаем полученное выражение
  energy4->accept(simplifier);
  cout << "After the last simplification: " 
       << (string)*simplifier.getResult() << endl << endl;

  // Наконец, продифференцируем некоторое выражение...
  Expression * beforeDiff = Parser::parse("(x+1)/(x-1)");
  Diff dasher("x");
  beforeDiff->accept(dasher);
  Expression * afterDiff = dasher.getResult();
  cout << "Before derivative evaluation: " << (string)*beforeDiff << endl
       << "After derivative evaluation: " << (string)*afterDiff << endl;

  // ... и упростим его
  afterDiff->accept(simplifier);
  cout << "after its simplification: " << (string)*simplifier.getResult() << endl;

  return 0;
}
