/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.5. Прохождение деревьев                           *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : tree.h                                           *
*  Описание : Определение шаблона классов для представления    *
*             деревьев с обратной ссылкой                      *
***************************************************************/

#ifndef __TREE_H
#define __TREE_H

#include <stdlib.h>
#include <iostream>
#include "iterator.h"
#include <exception>

using namespace std;

//==============================================================
// Класс, определяющий исключительную ситуацию NoElementException,
// которая может возникать при попытках доступа к очередному 
// элементу итератора после завершения итерации.
//==============================================================

class NoElementException : public exception {
  char * reason;
public:
  NoElementException() : reason("Iterator: No current element exists") {}
  const char * what() const throw() { return reason; }
};

//**************************************************************
// Определение класса Tree
//**************************************************************

template <class T>
class Tree {

protected:

  // Описание структуры узла со ссылками на сына и брата
  struct Node {
    T item;         // значение, содержащееся в узле
    Node *son;      // указатель на сына
    Node *brother;  // указатель на брата
    bool youngest;  // признак "самого младшего брата"

    // Конструктор узла
    Node(T i, Node *s = NULL, Node *b = NULL) {
      item = i; son = s; setBrother(b);
    }

    void setBrother(Node *b) {
      brother = b;
      youngest = (b == NULL);  // узел младший, если отсутствует ссылка на брата
    }
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

  // Класс BackRefIterator является реализацией внешнего итератора для 
  // обхода дерева "в глубину" с использованием обратных ссылок.
  class BackRefIterator : public Iterator<T> {
    Node* curNode;    // текущий узел при обходе

  public:
    // Конструктор итератора инициирует ссылку на текущий узел
    BackRefIterator(Tree<T> & t) { curNode = t.root; }

    // Проверка конца итерации - это проверка наличия очередного элемента.
    bool hasMoreElements() const { return curNode != NULL; }

    // Переход к следующему элементу состоит в сдвиге указателя на текущий узел
    Iterator<T> & operator ++ ();

    // Доступ к очередному (текущему) узлу.
    const T & operator *() const;
    T & operator *();
  };
  friend class BackRefIterator;

  // Конструктор "по умолчанию" создает пустое дерево
  Tree() : root(NULL) {}

  // Следующий конструктор строит дерево из некоторой другой структуры
  // с помощью объекта класса Analizer
  Tree(Analizer & a) : root(a.parse()) {}

  // Деструктор должен освободить память, занятую узлами дерева
  ~Tree() { deleteSubtree(root); }

  // Печать строкового изображения дерева в выходной поток out.
  void print(ostream & out) { printRec(out, root); out << endl; }

  // Функция построения внешнего итератора BreadthFirst:
  BackRefIterator * iteratorBR() { return new BackRefIterator(*this); }

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

// Переход к следующему узлу дерева.
template <class T>
Iterator<T> & Tree<T>::BackRefIterator::operator ++ () {
  if (curNode != NULL) {
    // Ищем следующий элемент
    if (curNode->son) {
      curNode = curNode->son;
    } else {
      while (curNode != NULL && curNode->youngest) {
        curNode = curNode->brother;   // переход к родительскому узлу
      }
      if (curNode != NULL) curNode = curNode->brother;  // переход к брату
    }
  }
  return *this;
}

// Доступ к очередному узлу.
template <class T>
T & Tree<T>::BackRefIterator::operator *() {
  if (curNode == NULL) {
    throw NoElementException();
  }
  return curNode->item;
}

template <class T>
const T & Tree<T>::BackRefIterator::operator *() const {
  if (curNode == NULL) {
    throw NoElementException();
  }
  return curNode->item;
}

// Рекурсивная функция для освобождения памяти
template <class T>
void Tree<T>::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->son);
    if (!node->youngest) deleteSubtree(node->brother);
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
    if (root->youngest) out << '\'';
    for (Node * son = root->son; son; son = (son->youngest ? NULL : son->brother)) {
      printRec(out, son);
    }
  }
  out << ')';
}

#endif

