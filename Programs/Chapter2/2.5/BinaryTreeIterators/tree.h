/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.5. Прохождение деревьев                           *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : tree.h                                           *
*  Описание : Определение шаблона классов для представления    *
*             деревьев                                         *
***************************************************************/

#ifndef __TREE_H
#define __TREE_H

#include <stdlib.h>
#include <iostream>
#include "liststack.h"
#include "listqueue.h"
#include "iterator.h"
#include <exception>
#include "actor.h"

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
    Node *left;     // указатель на левое поддерево
    Node *right;    // указатель на правое поддерево

    // Конструктор узла
    Node(T i, Node *l = NULL, Node *r = NULL) {
      item = i; left = l; right = r;
    }
  };

  // Дерево реализовано в виде указателя на корневой узел.
  Node *root;

  // Фабрика очередей создается конструктором для генерации очередей,
  // необходимых для реализации внешнего итератора для обхода "в ширину"
  static QueueFactory<Node*> *queueFactory;

public :
  // Класс BreadthFirst является реализацией внешнего итератора для 
  // обхода дерева "в ширину". Для хранения промежуточных еще не
  // пройденных узлов он использует очередь указателей на узлы.
  class BreadthFirst : public Iterator<T> {
    Queue<Node*> *queue;    // Очередь непройденных поддеревьев

  public:
    // Конструктор итератора инициирует очередь...
    BreadthFirst(Tree<T> & t);
    // ...а деструктор - освобождает память, занятую нею.
    ~BreadthFirst() { delete queue; }

    // Проверка конца итерации - это проверка пустоты очереди.
    bool hasMoreElements() const { return !queue->empty(); }

    // Переход к следующему элементу состоит в том, что очередной
    // указатель извлекается из очереди, а его потомки ставятся в очередь.
    Iterator<T> & operator ++ ();

    // Доступ к очередному узлу - это доступ к узлу, стоящему в голове очереди.
    const T & operator *() const;
    T & operator *();
  };

  // Класс Analizer играет вспомогательную роль - это основа для
  // построения классов, которые строят узлы дерева по некоторому
  // представлению дерева. Виртаульная функция parse организует 
  // построение узлов дерева.
  class Analizer {
  public :
    virtual Node * parse() = 0;
  };

  // Конструктор "по умолчанию" создает пустое дерево
  Tree() : root (NULL) {}

  // Следующий конструктор строит дерево из некоторой другой структуры
  // с помощью объекта класса Analizer
  Tree(Analizer & a) : root(a.parse()) {}

  // Деструктор должен освободить память, занятую узлами дерева
  ~Tree() { deleteSubtree(root); }

  // Печать строкового изображения дерева в выходной поток out.
  void print(ostream & out) { printRec(out, root); out << endl; }

  // Левосторонний обход с помощью внутреннего итератора,
  // реализованного в виде вызва вспомогательной рекурсивной
  // процедуры, описанной ниже в виде метода этого же класса.
  void traverseInfixLeft(Actor<T> & a) {
    recTraverseInfixLeft(root, a);
  }

  // Внутренний итератор для нисходящего 
  // обхода с хранением узлов в стеке
  void traverseUpDown(Actor<T> & actor);

  // Внутренний итератор для левостороннего
  // обхода с хранением узлов в стеке
  void traverseInfix(Actor<T> & actor);

  // Функция построения внешнего итератора BreadthFirst:
  BreadthFirst * iteratorBF() { return new BreadthFirst(*this); }

private :

  //-----------------------------------------------------------
  // Следующие рекурсивные функции представляют собой 
  // рекурсивные тела основных интерфейсных методов
  //-----------------------------------------------------------

  // Рекурсивная функция для освобождения памяти
  void deleteSubtree(Node *node);

  // Рекурсивная функция для вывода изображения дерева в выходной поток
  void printRec(ostream & out, Node * root);

  // Рекурсивная функция для организации внутренней итерации в порядке
  // левостороннего обхода узлов дерева.
  void recTraverseInfixLeft(Node *pNode, Actor<T> & a);
}; // конец класса Tree

template <class T>
QueueFactory<Tree<T>::Node *> * Tree<T>::queueFactory = new ListQueueFactory<Node *>;

// Тела методов класса

// Конструктор итератора инициирует очередь.
template <class T>
Tree<T>::BreadthFirst::BreadthFirst(Tree<T> & t) {
  queue = queueFactory->newQueue();
  if (t.root) {
    queue->enqueue(t.root);
  }
}

// Переход к следующему элементу состоит в том, что очередной
// указатель извлекается из очереди, а его потомки ставятся в очередь.
template <class T>
Iterator<T> & Tree<T>::BreadthFirst::operator ++ () {
  if (!queue->empty()) {
    Node * next = queue->head();
    queue->dequeue();
    if (next->left) queue->enqueue(next->left);
    if (next->right) queue->enqueue(next->right);
  }
  return *this;
}

// Доступ к очередному узлу - это доступ к узлу, стоящему в голове очереди.
template <class T>
const T & Tree<T>::BreadthFirst::operator *() const {
  if (!queue->empty()) {
    Node * & element = queue->head();
    return element->item;
  } else {
    throw NoElementException();
  }
}

template <class T>
T & Tree<T>::BreadthFirst::operator *() {
  if (!queue->empty()) {
    Node * & element = queue->head();
    return element->item;
  } else {
    throw NoElementException();
  }
}

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

// Рекурсивная функция для организации внутренней итерации в порядке
// левостороннего обхода узлов дерева.
template <class T>
void Tree<T>::recTraverseInfixLeft(Node *pNode, Actor<T> & a) {
  if (pNode) {
    recTraverseInfixLeft(pNode->left, a);  // Обход левого поддерева
    a.action(pNode->item);                 // Обход узла
    recTraverseInfixLeft(pNode->right, a); // Обход правого поддерева
  }
}

// Внутренний итератор для нисходящего 
// обхода с хранением узлов в стеке
template <class T>
void Tree<T>::traverseUpDown(Actor<T> & actor) {
  // Стек для хранения узлов; для определенности считаем, что
  // в качестве реализации стека выбирается ListStack – стек,
  // реализованный в виде списка элементов.
  ListStack<Node*> stack;
  // Текущая вершина:
  Node *current = root;                       
  // Основной цикл
  for (;;) {
    //----------- Обходим текущую вершину
    actor.action(current->item);
    //----------- Переходим к следующему узлу
    if (current->right != NULL && current->left != NULL) {
      stack.push(current->right);
      current = current->left;
    } else if (current->left != NULL) {
      current = current->left;
    } else if (current->right != NULL) {
      current = current->right;
    } else try {
      //----------- или пытаемся извлечь очередную вершину из стека
      current = stack.top();
      stack.pop();
    } catch (StackUnderflow & ex) {
      //--------- Стек пуст, заканчиваем работу цикла и функции
      break;
    }
  }
}

// Внутренний итератор для левостороннего
// обхода с хранением узлов в стеке
template <class T>
void Tree<T>::traverseInfix(Actor<T> & actor) {
  // Стек для хранения информации
  ListStack<Node*> stack;
  // Текущая вершина
  Node *current = root;
  // Основной цикл
  bool stackEmpty = false;
  while (!stackEmpty) {
    //----------- Кладем в стек текущую вершину
    stack.push(current);
    //----------- Переходим к левому поддереву, если оно есть
    if (current->left != NULL) {
      current = current->left;
    }
    //----------- или извлекаем очередную вершину из стека
    else do {
      try {
        current = stack.top();
        stack.pop();
        //----------- и обходим текущую вершину
        actor.action(current->item);
      } catch (StackUnderflow & ex) {
        stackEmpty = true;
      }
    } while (!stackEmpty && (current = current->right) == NULL);
  }
}

#endif

