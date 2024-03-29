/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.3. Деревья                                        *
*                                                              *
*  Автор    : A.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Тестовая функция для определения функции         *
*             определения количества элементов на заданном     *
*             уровне дерева.                                   *
***************************************************************/

#include <iostream>
#include "tree.h"

using namespace std;

//-----------------------------------------------------------------------
// Тестовая функция строит дерево и вычисляет его высоту (должно быть 4)
// и число узлов находящихся на 3-м уровне (должно быть 3).
//-----------------------------------------------------------------------

int main() {
  Tree<int> tree1;  // пустое дерево

  tree1.add(12);
  tree1.add(5);
  tree1.add(3);
  tree1.add(10);
  tree1.add(7);
  tree1.add(11);
  tree1.add(6);
  tree1.add(9);
  
  // Дерево построено

  cout << "Tree height : " << tree1.height() << endl 
       << "There are " << tree1.nodesOnLevel(3) << " nodes on the 3rd level" << endl;
  return 0;
}
