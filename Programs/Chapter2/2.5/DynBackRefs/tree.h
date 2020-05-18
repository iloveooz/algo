/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.5. Прохождение деревьев                           *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : tree.h                                           *
*  Описание : Определение шаблона классов для представления    *
*             деревьев с динамической обратной ссылкой         *
***************************************************************/

#ifndef __TREE_H
#define __TREE_H

#include <stdlib.h>
#include <iostream>
#include "actor.h"

using namespace std;

//**************************************************************
// Определение класса Tree
//**************************************************************

template <class T>
class Tree {

protected:

  // Описание структуры узла со ссылками на левое и правое пооддеревья
  struct Node {
    T item;         // значение, содержащееся в узле
    Node *left;     // указатель на левое поддерево
    Node *right;    // указатель на правое поддерево
    bool flag;      // флажок для обхода

    // Конструктор узла
    Node(T i, Node *l = NULL, Node *r = NULL) :
        item(i), left(l), right(r), flag(false) {}
  };

  // Дерево реализовано в виде указателя на корневой узел.
  Node *root;

public :

  // Класс Analizer играет вспомогательную роль - это основа для
  // построения классов, которые строят узлы дерева по некоторому
  // представлению дерева. Виртаульная функция parse организует 
  // построение узлов дерева.
  class Analizer {
  public :
    virtual Node * parse() = 0;
  };

  // Конструктор "по умолчанию" создает пустое дерево
  Tree() : root(NULL) {}

  // Следующий конструктор строит дерево из некоторой другой структуры
  // с помощью объекта класса Analizer
  Tree(Analizer & a) : root(a.parse()) {}

  // Деструктор должен освободить память, занятую узлами дерева
  ~Tree() { deleteSubtree(root); }

  // Печать строкового изображения дерева в выходной поток out.
  void print(ostream & out) { printRec(out, root); out << endl; }

  // Обход узлов дерева с динамическим обращением ссылок  
  void traverseWithInversion(Actor<T> & actor);

private :

  //-----------------------------------------------------------
  // Следующие рекурсивные функции представляют собой 
  // рекурсивные тела основных интерфейсных методов
  //-----------------------------------------------------------

  // Рекурсивная функция для освобождения памяти
  void deleteSubtree(Node *node);

  // Рекурсивная функция для вывода изображения дерева в выходной поток
  void printRec(ostream & out, Node * root);
}; // конец класса Tree

// Тела методов класса

// Рекурсивная функция для освобождения памяти
template <class T>
void Tree<T>::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
  }
}

// Рекурсивная функция для вывода изображения дерева в выходной поток
template <class T>
void Tree<T>::printRec(ostream & out, Node *root) {
  // Изображение дерева заключается в круглые скобки.
  out << '(';
  if (root) {
    // Для узлов дерева должна быть определена (или переопределена)
    // операция вывода в выходной поток <<
    out << root->item;
    printRec(out, root->left);
    printRec(out, root->right);
  }
  out << ')';
}

// Обход узлов дерева с динамическим обращением ссылок  
template <class T>
void Tree<T>::traverseWithInversion(Actor<T> & actor) {
  Node *processed = NULL;   // указатель вверх по дереву
  Node *current = root;     // указатель на текущую вершину
  bool down = true;         // направление движения
  // Цикл обхода узлов закончится, когда при движении вверх
  // окажется, что уже все узлы пройдены
  while (down || processed != NULL) {
    if (down) {
      if (current == NULL) {
        // меняем направление движения
        down = false;
      } else {
        // спускаемся вниз по дереву на один шаг
        Node *w = current->left;
        current->left = processed;
        processed = current;
        current = w;
      }
    } else {
      if (processed->flag) {
        // восстанавливаем указатель и продвигаемся вверх по дереву
        processed->flag = false;
        Node *w = processed->right;
        processed->right = current;
        current = processed;
        processed = w;
      } else {
        // посещаем вершину при переходе из левого поддерева в правое
        actor.action(processed->item);
        // переходим к обработке правого поддерева
        Node *w = processed->right;
        processed->flag = true;
        processed->right = processed->left;
        processed->left = current;
        current = w;
        // снова двигаемся вниз
        down = true;
      }
    }
  }
}

#endif

