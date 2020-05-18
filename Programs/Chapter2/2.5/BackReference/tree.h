/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.5. ����������� ��������                           *
*                                                              *
*  �����    : A.Koubenski                                      *
*  ����     : tree.h                                           *
*  �������� : ����������� ������� ������� ��� �������������    *
*             �������� � �������� �������                      *
***************************************************************/

#ifndef __TREE_H
#define __TREE_H

#include <stdlib.h>
#include <iostream>
#include "iterator.h"
#include <exception>

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
    Node *son;      // ��������� �� ����
    Node *brother;  // ��������� �� �����
    bool youngest;  // ������� "������ �������� �����"

    // ����������� ����
    Node(T i, Node *s = NULL, Node *b = NULL) {
      item = i; son = s; setBrother(b);
    }

    void setBrother(Node *b) {
      brother = b;
      youngest = (b == NULL);  // ���� �������, ���� ����������� ������ �� �����
    }
  };

  // ������ ����������� � ���� ��������� �� �������� ����.
  Node *root;

public :
  // ����� Analizer ������ ��������������� ���� - ��� ������ ���
  // ���������� �������, ������� ������ ���� ������ �� ����������
  // ������������� ������. ����������� ������� parse ���������� 
  // ���������� ����� ������.
  class Analizer {
  public :
    virtual Node * parse() = 0;
  };

  // ����� BackRefIterator �������� ����������� �������� ��������� ��� 
  // ������ ������ "� �������" � �������������� �������� ������.
  class BackRefIterator : public Iterator<T> {
    Node* curNode;    // ������� ���� ��� ������

  public:
    // ����������� ��������� ���������� ������ �� ������� ����
    BackRefIterator(Tree<T> & t) { curNode = t.root; }

    // �������� ����� �������� - ��� �������� ������� ���������� ��������.
    bool hasMoreElements() const { return curNode != NULL; }

    // ������� � ���������� �������� ������� � ������ ��������� �� ������� ����
    Iterator<T> & operator ++ ();

    // ������ � ���������� (��������) ����.
    const T & operator *() const;
    T & operator *();
  };
  friend class BackRefIterator;

  // ����������� "�� ���������" ������� ������ ������
  Tree() : root(NULL) {}

  // ��������� ����������� ������ ������ �� ��������� ������ ���������
  // � ������� ������� ������ Analizer
  Tree(Analizer & a) : root(a.parse()) {}

  // ���������� ������ ���������� ������, ������� ������ ������
  ~Tree() { deleteSubtree(root); }

  // ������ ���������� ����������� ������ � �������� ����� out.
  void print(ostream & out) { printRec(out, root); out << endl; }

  // ������� ���������� �������� ��������� BreadthFirst:
  BackRefIterator * iteratorBR() { return new BackRefIterator(*this); }

private :

  //-----------------------------------------------------------
  // ��������� ����������� ������� ������������ ����� 
  // ����������� ���� �������� ������������ �������
  //-----------------------------------------------------------

  // ����������� ������� ��� ������������ ������
  void deleteSubtree(Node *node);

  // ����������� ������� ��� ������ ����������� ������ � �������� �����
  void printRec(ostream & out, Node * root);
}; // ����� ������ Tree

// ���� ������� ������

// ������� � ���������� ���� ������.
template <class T>
Iterator<T> & Tree<T>::BackRefIterator::operator ++ () {
  if (curNode != NULL) {
    // ���� ��������� �������
    if (curNode->son) {
      curNode = curNode->son;
    } else {
      while (curNode != NULL && curNode->youngest) {
        curNode = curNode->brother;   // ������� � ������������� ����
      }
      if (curNode != NULL) curNode = curNode->brother;  // ������� � �����
    }
  }
  return *this;
}

// ������ � ���������� ����.
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

// ����������� ������� ��� ������������ ������
template <class T>
void Tree<T>::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->son);
    if (!node->youngest) deleteSubtree(node->brother);
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
    if (root->youngest) out << '\'';
    for (Node * son = root->son; son; son = (son->youngest ? NULL : son->brother)) {
      printRec(out, son);
    }
  }
  out << ')';
}

#endif

