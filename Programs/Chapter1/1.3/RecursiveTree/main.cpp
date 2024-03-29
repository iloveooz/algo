/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.3. Деревья                                        *
*                                                              *
*  Автор    : A.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Тестовая функция для определения высоты дерева,  *
*             заданного рекурсивно                             *
***************************************************************/

#include <iostream>
#include "tree.h"

using namespace std;

/************************************************************
 *
 * Создаем дерево высоты 4 следующей структуры и содержания:
 *
 *          ____________________ 1 _______________________
 *         /                     |                        \
 *         2          __________ 3 ___________            4
 *                   /                        \           |
 *                   5                 ______ 6 ______    7
 *                                    /       |       \ 
 *                                   8        9       10
 *************************************************************/

int main() {
  Tree<int> *tree = new Tree<int>(1,
     new Tree<int>(2, NULL, new Tree<int>(3,
       new Tree<int>(5, NULL, new Tree<int>(6,
           new Tree<int>(8, NULL, new Tree<int>(9, NULL, new Tree<int>(10))))),
                                        new Tree<int>(4,
                                          new Tree<int>(7)))));
  cout << "Tree height: " << tree->height() << endl;
  delete tree;
  return 0;
}
