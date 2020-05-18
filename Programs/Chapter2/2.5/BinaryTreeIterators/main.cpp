/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.5. Прохождение деревьев                           *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : main.cpp                                         *
*  Описание : Функция проверки работы внешних итераторов       *
*             дерева.                                          *
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

  // Печать содержимого узлов дерева в порядке нисходящего обхода "в ширину".
  // Используется итератор BreadthFirst, полученный с помощью метода t.iteratorBF
  cout << "Tree nodes in breadth first order (external iterator using queue):" << endl;
  Iterator<char> * iBF = t.iteratorBF();
  for (; iBF->hasMoreElements(); ++*iBF) {
    cout << **iBF;
  }
  cout << endl << endl;
  delete iBF;

  // Печать содержимого узлов дерева в порядке левостороннего обхода
  // с помощью внутреннего итератора traverseInfixLeft
  Printer p;
  cout << "Tree nodes in left infix order (internal iterator using recursive function):" << endl;
  t.traverseInfixLeft(p);
  cout << endl << endl;

  // Печать содержимого узлов дерева в порядке нисходящего обхода с хранением 
  // узлов в стеке с помощью внутреннего итератора traverseUpDown
  cout << "Tree nodes in up-down order (internal iterator using stack):" << endl;
  t.traverseUpDown(p);
  cout << endl << endl;

  // Печать содержимого узлов дерева в порядке левостороннего обхода
  // с помощью внутреннего итератора traverseInfix
  cout << "Tree nodes in left infix order (internal iterator using stack):" << endl;
  t.traverseInfix(p);
  cout << endl;

  return 0;
}
