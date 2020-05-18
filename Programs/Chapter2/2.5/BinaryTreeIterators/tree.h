/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.5. ����������� ��������                           *
*                                                              *
*  �����    : A.Koubenski                                      *
*  ����     : tree.h                                           *
*  �������� : ����������� ������� ������� ��� �������������    *
*             ��������                                         *
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
// �����, ������������ �������������� �������� NoElementException,
// ������� ����� ��������� ��� �������� ������� � ���������� 
// �������� ��������� ����� ���������� ��������.
//==============================================================

class NoElementException : public exception {
  char * reason;
public:
  NoElementException() : reason("Iterator: No current element exists") {}
  const char * what() const throw() { return reason; }
};

//**************************************************************
// ����������� ������ Tree
//**************************************************************

template <class T>
class Tree {

protected:

  // �������� ��������� ���� �� �������� �� ���� � �����
  struct Node {
    T item;         // ��������, ������������ � ����
    Node *left;     // ��������� �� ����� ���������
    Node *right;    // ��������� �� ������ ���������

    // ����������� ����
    Node(T i, Node *l = NULL, Node *r = NULL) {
      item = i; left = l; right = r;
    }
  };

  // ������ ����������� � ���� ��������� �� �������� ����.
  Node *root;

  // ������� �������� ��������� ������������� ��� ��������� ��������,
  // ����������� ��� ���������� �������� ��������� ��� ������ "� ������"
  static QueueFactory<Node*> *queueFactory;

public :
  // ����� BreadthFirst �������� ����������� �������� ��������� ��� 
  // ������ ������ "� ������". ��� �������� ������������� ��� ��
  // ���������� ����� �� ���������� ������� ���������� �� ����.
  class BreadthFirst : public Iterator<T> {
    Queue<Node*> *queue;    // ������� ������������ �����������

  public:
    // ����������� ��������� ���������� �������...
    BreadthFirst(Tree<T> & t);
    // ...� ���������� - ����������� ������, ������� ���.
    ~BreadthFirst() { delete queue; }

    // �������� ����� �������� - ��� �������� ������� �������.
    bool hasMoreElements() const { return !queue->empty(); }

    // ������� � ���������� �������� ������� � ���, ��� ���������
    // ��������� ����������� �� �������, � ��� ������� �������� � �������.
    Iterator<T> & operator ++ ();

    // ������ � ���������� ���� - ��� ������ � ����, �������� � ������ �������.
    const T & operator *() const;
    T & operator *();
  };

  // ����� Analizer ������ ��������������� ���� - ��� ������ ���
  // ���������� �������, ������� ������ ���� ������ �� ����������
  // ������������� ������. ����������� ������� parse ���������� 
  // ���������� ����� ������.
  class Analizer {
  public :
    virtual Node * parse() = 0;
  };

  // ����������� "�� ���������" ������� ������ ������
  Tree() : root (NULL) {}

  // ��������� ����������� ������ ������ �� ��������� ������ ���������
  // � ������� ������� ������ Analizer
  Tree(Analizer & a) : root(a.parse()) {}

  // ���������� ������ ���������� ������, ������� ������ ������
  ~Tree() { deleteSubtree(root); }

  // ������ ���������� ����������� ������ � �������� ����� out.
  void print(ostream & out) { printRec(out, root); out << endl; }

  // ������������� ����� � ������� ����������� ���������,
  // �������������� � ���� ����� ��������������� �����������
  // ���������, ��������� ���� � ���� ������ ����� �� ������.
  void traverseInfixLeft(Actor<T> & a) {
    recTraverseInfixLeft(root, a);
  }

  // ���������� �������� ��� ����������� 
  // ������ � ��������� ����� � �����
  void traverseUpDown(Actor<T> & actor);

  // ���������� �������� ��� ��������������
  // ������ � ��������� ����� � �����
  void traverseInfix(Actor<T> & actor);

  // ������� ���������� �������� ��������� BreadthFirst:
  BreadthFirst * iteratorBF() { return new BreadthFirst(*this); }

private :

  //-----------------------------------------------------------
  // ��������� ����������� ������� ������������ ����� 
  // ����������� ���� �������� ������������ �������
  //-----------------------------------------------------------

  // ����������� ������� ��� ������������ ������
  void deleteSubtree(Node *node);

  // ����������� ������� ��� ������ ����������� ������ � �������� �����
  void printRec(ostream & out, Node * root);

  // ����������� ������� ��� ����������� ���������� �������� � �������
  // �������������� ������ ����� ������.
  void recTraverseInfixLeft(Node *pNode, Actor<T> & a);
}; // ����� ������ Tree

template <class T>
QueueFactory<Tree<T>::Node *> * Tree<T>::queueFactory = new ListQueueFactory<Node *>;

// ���� ������� ������

// ����������� ��������� ���������� �������.
template <class T>
Tree<T>::BreadthFirst::BreadthFirst(Tree<T> & t) {
  queue = queueFactory->newQueue();
  if (t.root) {
    queue->enqueue(t.root);
  }
}

// ������� � ���������� �������� ������� � ���, ��� ���������
// ��������� ����������� �� �������, � ��� ������� �������� � �������.
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

// ������ � ���������� ���� - ��� ������ � ����, �������� � ������ �������.
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

// ����������� ������� ��� ������������ ������
template <class T>
void Tree<T>::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
  }
}

// ����������� ������� ��� ������ ����������� ������ � �������� �����
template <class T>
void Tree<T>::printRec(ostream & out, Node *root) {
  // ����������� ������ ����������� � ������� ������.
  out << '(';
  if (root) {
    // ��� ����� ������ ������ ���� ���������� (��� ��������������)
    // �������� ������ � �������� ����� <<
    out << root->item;
    printRec(out, root->left);
    printRec(out, root->right);
  }
  out << ')';
}

// ����������� ������� ��� ����������� ���������� �������� � �������
// �������������� ������ ����� ������.
template <class T>
void Tree<T>::recTraverseInfixLeft(Node *pNode, Actor<T> & a) {
  if (pNode) {
    recTraverseInfixLeft(pNode->left, a);  // ����� ������ ���������
    a.action(pNode->item);                 // ����� ����
    recTraverseInfixLeft(pNode->right, a); // ����� ������� ���������
  }
}

// ���������� �������� ��� ����������� 
// ������ � ��������� ����� � �����
template <class T>
void Tree<T>::traverseUpDown(Actor<T> & actor) {
  // ���� ��� �������� �����; ��� �������������� �������, ���
  // � �������� ���������� ����� ���������� ListStack � ����,
  // ������������� � ���� ������ ���������.
  ListStack<Node*> stack;
  // ������� �������:
  Node *current = root;                       
  // �������� ����
  for (;;) {
    //----------- ������� ������� �������
    actor.action(current->item);
    //----------- ��������� � ���������� ����
    if (current->right != NULL && current->left != NULL) {
      stack.push(current->right);
      current = current->left;
    } else if (current->left != NULL) {
      current = current->left;
    } else if (current->right != NULL) {
      current = current->right;
    } else try {
      //----------- ��� �������� ������� ��������� ������� �� �����
      current = stack.top();
      stack.pop();
    } catch (StackUnderflow & ex) {
      //--------- ���� ����, ����������� ������ ����� � �������
      break;
    }
  }
}

// ���������� �������� ��� ��������������
// ������ � ��������� ����� � �����
template <class T>
void Tree<T>::traverseInfix(Actor<T> & actor) {
  // ���� ��� �������� ����������
  ListStack<Node*> stack;
  // ������� �������
  Node *current = root;
  // �������� ����
  bool stackEmpty = false;
  while (!stackEmpty) {
    //----------- ������ � ���� ������� �������
    stack.push(current);
    //----------- ��������� � ������ ���������, ���� ��� ����
    if (current->left != NULL) {
      current = current->left;
    }
    //----------- ��� ��������� ��������� ������� �� �����
    else do {
      try {
        current = stack.top();
        stack.pop();
        //----------- � ������� ������� �������
        actor.action(current->item);
      } catch (StackUnderflow & ex) {
        stackEmpty = true;
      }
    } while (!stackEmpty && (current = current->right) == NULL);
  }
}

#endif

