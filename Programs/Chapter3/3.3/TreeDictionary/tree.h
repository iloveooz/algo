/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.3. Словари, представленные списками и деревьями   *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : tree.h                                           *
*  Описание : Определение шаблона классов для представления    *
*             бинарных деревьев поиска                         *
***************************************************************/

#ifndef __TREE_H
#define __TREE_H

#include <stdlib.h>
#include <iostream>
#include "stack.h"
#include "stackfactory.h"
#include "liststack.h"
#include "iterator.h"

using namespace std;

//**************************************************************
// Определение класса Tree с операцией поиска по ключу
//**************************************************************

template <class T>
class Tree {

protected:

  // Описание структуры узла со ссылками на сына и брата
  struct Node {
    T key;          // ключ, содержащийся в узле
    Node *left;     // указатель на левое поддерево
    Node *right;    // указатель на правое поддерево

    // Конструктор узла
    Node(T k, Node *l = NULL, Node *r = NULL) {
      key = k; left = l; right = r;
    }
  };

  // Дерево реализовано в виде указателя на корневой узел.
  Node *root;

public :

  // Класс ExtIterator является реализацией внешнего итератора для 
  // левостороннего обхода дерева. Для хранения промежуточных еще не
  // пройденных узлов он использует стек указателей на узлы.
  class ExtIterator : public Iterator<T> {
    // Фабрика стеков необходима для генерации стеков,
    // используемых для реализации внешнего итератора
    // для левостороннего обхода дерева
    static StackFactory<Node*> *stackFactory;

    Stack<Node*> *stack;    // Стек отложенных поддеревьев
    Node * current;

  public:
    // Конструктор итератора инициирует стек...
    ExtIterator(const Tree<T> & t);
    // ...а деструктор - освобождает память, занятую им.
    ~ExtIterator() { delete stack; }

    // Проверка конца итерации.
    bool hasMoreElements() const { return current != NULL; }

    // Переход к следующему элементу состоит в том, что очередной
    // узел ищется либо среди потомков текущего узла, либо
    // извлекается из стека.
    Iterator<T> & operator ++ ();

    // Доступ к очередному узлу - это доступ к текущему узлу.
    const T & operator *() const { return current->key; }
    T & operator *() { return current->key; }

  protected:
    void pushLeftEdge(Node *node);
  };

  friend class ExtIterator;

  // Конструктор "по умолчанию" создает пустое дерево
  Tree() : root(NULL) {}

  // Деструктор должен освободить память, занятую узлами дерева
  ~Tree() { deleteSubtree(root); }

  // Функция поиска по ключу в бинарном дереве поиска
  T * search(const T & key) const;

  // Построение внешнего итератора узлов
  Iterator<T> *iterator() const { return new ExtIterator(*this); }

  // Вставка нового элемента в дерево, не нарушающая порядка
  // элементов. Вставка производится в лист дерева
  void insertLeaf(const T& elem);

  // Вставка нового элемента в дерево, не нарушающая порядка
  // элементов. Вставка производится в корень дерева
  void insertRoot(const T& elem);

  // Удаление элемента из дерева, не нарушающее порядка элементов
  void remove(const T & item);

private :

  //-----------------------------------------------------------
  // Следующие рекурсивные функции представляют собой 
  // рекурсивные тела основных интерфейсных методов
  //-----------------------------------------------------------

  // Рекурсивная функция для освобождения памяти
  void deleteSubtree(Node *node);

}; // конец класса Tree

template <class T>
StackFactory<Tree<T>::Node*> * Tree<T>::ExtIterator::stackFactory = 
    new ListStackFactory<Tree<T>::Node*>();

// Тела методов класса Tree::ExtIterator

template <class T>
Tree<T>::ExtIterator::ExtIterator(const Tree<T> & t) {
  stack = stackFactory->newStack();
  pushLeftEdge(t.root);
  ++*this;
}

template <class T>
Iterator<T> & Tree<T>::ExtIterator::operator ++ () {
  if (stack->empty()) {
    current = NULL;
  } else {
    current = **stack;
    stack->pop();
    pushLeftEdge(current->right);
  }
  return *this;
}

template <class T>
void Tree<T>::ExtIterator::pushLeftEdge(Node *node) {
  for (Node * current = node; current; current = current->left) {
    stack->push(current);
  }
}

// Тела методов класса Tree

// Рекурсивная функция для освобождения памяти
template <class T>
void Tree<T>::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
  }
}

// Функция поиска по ключу в бинарном дереве поиска
template <class T>
T * Tree<T>::search(const T & key) const {
  for (Node * current = root; current; ) {
    if (current->key == key) {            // узел найден
      return & current->key;
    } else if (current->key < key) {      // значение в корне меньше искомого
      current = current->right;           // переходим в правое поддерево
    } else {                              // значение в корне больше искомого
      current = current->left;            // переходим в левое поддерево
    }
  }
  return NULL;                            // узел не найден
}

// Линеаризация дерева с выдачей его содержимого в символьный поток
template <class T>
ostream & operator << (ostream & out, const Tree<T> & tree) {
  out << '[';
  Iterator<T> * it = tree.iterator();
  while (it->hasMoreElements()) {
    out << **it;    // Предполагается, что содержимое узла 
                    // может быть выведено в поток out
    ++*it;          // продвижение к следующему узлу
    if (it->hasMoreElements()) {
      out << ',';
    }
  }
  out << ']';
  delete it;
  return out;
}

// Вставка нового элемента в дерево, не нарушающая порядка
// элементов. Вставка производится в лист дерева
template <class T>
void Tree<T>::insertLeaf(const T& elem) {
  Node ** current = &root;
  while (*current != NULL) {
    if (elem < (*current)->key) {
      current = &(*current)->left;
    } else {
      current = &(*current)->right;
    }
  }
  *current = new Node(elem);
}

// Вставка нового элемента в дерево, не нарушающая порядка
// элементов. Вставка производится в корень дерева
template <class T>
void Tree<T>::insertRoot(const T& elem) {
  // Прежде всего создается новый узел и указатели
  // на позиции "меньше" и "больше"
  Node * current = root;
  root = new Node(elem);
  Node ** leftNode = & root->left;
  Node ** rightNode = & root->right;
  // Цикл просмотра узлов и размещения элементов в
  // поддеревьях нового корня дерева
  while (current) {
    if (current->key < elem) {
      *leftNode = current;
      leftNode = & current->right;
      current = current->right;
    } else {
      *rightNode = current;
      rightNode = & current->left;
      current = current->left;
    }
  }
  *leftNode = *rightNode = NULL;
}

// Удаление элемента из дерева, не нарушающее порядка элементов
template <class T>
void Tree<T>::remove(const T & item) {
  Node ** current = & root;  // указатель на удаляемый узел
  // 1. Поиск удаляемого узла
  while (*current != NULL && (*current)->key != item) {
    if ((*current)->key < item) {
      current = &(*current)->right;
    } else {
      current = &(*current)->left;
    }
  }

  // 2. Разбор простых случаев
  if (*current == NULL) return;           // удаляемое значение не найдено
  if ((*current)->left == NULL) {         // левое поддерево отсутствует
    *current = (*current)->right;
  } else if ((*current)->right == NULL) { // правое поддерево отсутствует
    *current = (*current)->left;
  } else {

  // 3. Разбор общего случая: оба поддерева не пусты
    // Цикл поиска узла заместителя в правом поддереве
    Node ** nodeToReplace = & (*current)->right;
    while ((*nodeToReplace)->left) {
      nodeToReplace = &(*nodeToReplace)->left;
    }
    // Замещение значения в удаляемом узле
    (*current)->key = (*nodeToReplace)->key;
    // Физическое удаление узла-заместителя из дерева
    *nodeToReplace = (*nodeToReplace)->right;
  }
}

#endif

