/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.5. Прохождение деревьев                           *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : main.cpp                                         *
*  Описание : Функция проверки работы алгоритма обхода узлов   *
*             дерева с динамическим обращением ссылок.         *
***************************************************************/

#include "actor.h"
#include "tree.h"
#include "charAnalizer.h"
#include <iostream>

using namespace std;

// Действие, определенное классом Printer, производит вывод
// содержимого узла дерева в стандартный выходной поток.
class Printer : public Actor<char> {
public :
  void action(char & c) { cout << c; }
};

int main() {
  // Задаем строковое представление дерева из символов в соответствии
  // с тем, как это предписано правилами класса CharAnalizer
  CharAnalizer analizer("(A(B(D(G()())(H()()))())(C(E()())(F(I()())())))");
  // Строим дерево из символов
  Tree<char> t(analizer);
  // Контрольная печать дерева
  cout << "Tree structure expressed in parantheses:" << endl;
  t.print(cout);
  cout << endl;

  // Печать содержимого узлов дерева в порядке левостороннего обхода
  // с помощью внутреннего итератора с обращением ссылок traverseWithInversion
  Printer p;
  cout << "Tree nodes in left infix order (internal iterator using references inversion):" << endl;
  t.traverseWithInversion(p);
  cout << endl << endl;

  // Контрольная печать дерева после работы алгоритма обхода
  cout << "Tree structure again after traverse algorithm working:" << endl;
  t.print(cout);
  cout << endl;

  return 0;
}
