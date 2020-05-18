/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.3. �������, �������������� �������� � ���������   *
*                                                              *
*  �����    : A.Koubenski                                      *
*  ����     : tree.h                                           *
*  �������� : ����������� ������� ������� ��� �������������    *
*             �������� �������� ������                         *
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
// ����������� ������ Tree � ��������� ������ �� �����
//**************************************************************

template <class T>
class Tree {

protected:

  // �������� ��������� ���� �� �������� �� ���� � �����
  struct Node {
    T key;          // ����, ������������ � ����
    Node *left;     // ��������� �� ����� ���������
    Node *right;    // ��������� �� ������ ���������

    // ����������� ����
    Node(T k, Node *l = NULL, Node *r = NULL) {
      key = k; left = l; right = r;
    }
  };

  // ������ ����������� � ���� ��������� �� �������� ����.
  Node *root;

public :

  // ����� ExtIterator �������� ����������� �������� ��������� ��� 
  // �������������� ������ ������. ��� �������� ������������� ��� ��
  // ���������� ����� �� ���������� ���� ���������� �� ����.
  class ExtIterator : public Iterator<T> {
    // ������� ������ ���������� ��� ��������� ������,
    // ������������ ��� ���������� �������� ���������
    // ��� �������������� ������ ������
    static StackFactory<Node*> *stackFactory;

    Stack<Node*> *stack;    // ���� ���������� �����������
    Node * current;

  public:
    // ����������� ��������� ���������� ����...
    ExtIterator(const Tree<T> & t);
    // ...� ���������� - ����������� ������, ������� ��.
    ~ExtIterator() { delete stack; }

    // �������� ����� ��������.
    bool hasMoreElements() const { return current != NULL; }

    // ������� � ���������� �������� ������� � ���, ��� ���������
    // ���� ������ ���� ����� �������� �������� ����, ����
    // ����������� �� �����.
    Iterator<T> & operator ++ ();

    // ������ � ���������� ���� - ��� ������ � �������� ����.
    const T & operator *() const { return current->key; }
    T & operator *() { return current->key; }

  protected:
    void pushLeftEdge(Node *node);
  };

  friend class ExtIterator;

  // ����������� "�� ���������" ������� ������ ������
  Tree() : root(NULL) {}

  // ���������� ������ ���������� ������, ������� ������ ������
  ~Tree() { deleteSubtree(root); }

  // ������� ������ �� ����� � �������� ������ ������
  T * search(const T & key) const;

  // ���������� �������� ��������� �����
  Iterator<T> *iterator() const { return new ExtIterator(*this); }

  // ������� ������ �������� � ������, �� ���������� �������
  // ���������. ������� ������������ � ���� ������
  void insertLeaf(const T& elem);

  // ������� ������ �������� � ������, �� ���������� �������
  // ���������. ������� ������������ � ������ ������
  void insertRoot(const T& elem);

  // �������� �������� �� ������, �� ���������� ������� ���������
  void remove(const T & item);

private :

  //-----------------------------------------------------------
  // ��������� ����������� ������� ������������ ����� 
  // ����������� ���� �������� ������������ �������
  //-----------------------------------------------------------

  // ����������� ������� ��� ������������ ������
  void deleteSubtree(Node *node);

}; // ����� ������ Tree

template <class T>
StackFactory<Tree<T>::Node*> * Tree<T>::ExtIterator::stackFactory = 
    new ListStackFactory<Tree<T>::Node*>();

// ���� ������� ������ Tree::ExtIterator

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

// ���� ������� ������ Tree

// ����������� ������� ��� ������������ ������
template <class T>
void Tree<T>::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
  }
}

// ������� ������ �� ����� � �������� ������ ������
template <class T>
T * Tree<T>::search(const T & key) const {
  for (Node * current = root; current; ) {
    if (current->key == key) {            // ���� ������
      return & current->key;
    } else if (current->key < key) {      // �������� � ����� ������ ��������
      current = current->right;           // ��������� � ������ ���������
    } else {                              // �������� � ����� ������ ��������
      current = current->left;            // ��������� � ����� ���������
    }
  }
  return NULL;                            // ���� �� ������
}

// ������������ ������ � ������� ��� ����������� � ���������� �����
template <class T>
ostream & operator << (ostream & out, const Tree<T> & tree) {
  out << '[';
  Iterator<T> * it = tree.iterator();
  while (it->hasMoreElements()) {
    out << **it;    // ��������������, ��� ���������� ���� 
                    // ����� ���� �������� � ����� out
    ++*it;          // ����������� � ���������� ����
    if (it->hasMoreElements()) {
      out << ',';
    }
  }
  out << ']';
  delete it;
  return out;
}

// ������� ������ �������� � ������, �� ���������� �������
// ���������. ������� ������������ � ���� ������
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

// ������� ������ �������� � ������, �� ���������� �������
// ���������. ������� ������������ � ������ ������
template <class T>
void Tree<T>::insertRoot(const T& elem) {
  // ������ ����� ��������� ����� ���� � ���������
  // �� ������� "������" � "������"
  Node * current = root;
  root = new Node(elem);
  Node ** leftNode = & root->left;
  Node ** rightNode = & root->right;
  // ���� ��������� ����� � ���������� ��������� �
  // ����������� ������ ����� ������
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

// �������� �������� �� ������, �� ���������� ������� ���������
template <class T>
void Tree<T>::remove(const T & item) {
  Node ** current = & root;  // ��������� �� ��������� ����
  // 1. ����� ���������� ����
  while (*current != NULL && (*current)->key != item) {
    if ((*current)->key < item) {
      current = &(*current)->right;
    } else {
      current = &(*current)->left;
    }
  }

  // 2. ������ ������� �������
  if (*current == NULL) return;           // ��������� �������� �� �������
  if ((*current)->left == NULL) {         // ����� ��������� �����������
    *current = (*current)->right;
  } else if ((*current)->right == NULL) { // ������ ��������� �����������
    *current = (*current)->left;
  } else {

  // 3. ������ ������ ������: ��� ��������� �� �����
    // ���� ������ ���� ����������� � ������ ���������
    Node ** nodeToReplace = & (*current)->right;
    while ((*nodeToReplace)->left) {
      nodeToReplace = &(*nodeToReplace)->left;
    }
    // ��������� �������� � ��������� ����
    (*current)->key = (*nodeToReplace)->key;
    // ���������� �������� ����-����������� �� ������
    *nodeToReplace = (*nodeToReplace)->right;
  }
}

#endif

