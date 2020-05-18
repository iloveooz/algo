/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.5. ����������� ��������                           *
*                                                              *
*  �����    : A.Koubenski                                      *
*  ����     : tree.h                                           *
*  �������� : ����������� ������� ������� ��� �������������    *
*             �������� � ������������ �������� �������         *
***************************************************************/

#ifndef __TREE_H
#define __TREE_H

#include <stdlib.h>
#include <iostream>
#include "actor.h"

using namespace std;

//**************************************************************
// ����������� ������ Tree
//**************************************************************

template <class T>
class Tree {

protected:

  // �������� ��������� ���� �� �������� �� ����� � ������ �����������
  struct Node {
    T item;         // ��������, ������������ � ����
    Node *left;     // ��������� �� ����� ���������
    Node *right;    // ��������� �� ������ ���������
    bool flag;      // ������ ��� ������

    // ����������� ����
    Node(T i, Node *l = NULL, Node *r = NULL) :
        item(i), left(l), right(r), flag(false) {}
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

  // ����������� "�� ���������" ������� ������ ������
  Tree() : root(NULL) {}

  // ��������� ����������� ������ ������ �� ��������� ������ ���������
  // � ������� ������� ������ Analizer
  Tree(Analizer & a) : root(a.parse()) {}

  // ���������� ������ ���������� ������, ������� ������ ������
  ~Tree() { deleteSubtree(root); }

  // ������ ���������� ����������� ������ � �������� ����� out.
  void print(ostream & out) { printRec(out, root); out << endl; }

  // ����� ����� ������ � ������������ ���������� ������  
  void traverseWithInversion(Actor<T> & actor);

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

// ����� ����� ������ � ������������ ���������� ������  
template <class T>
void Tree<T>::traverseWithInversion(Actor<T> & actor) {
  Node *processed = NULL;   // ��������� ����� �� ������
  Node *current = root;     // ��������� �� ������� �������
  bool down = true;         // ����������� ��������
  // ���� ������ ����� ����������, ����� ��� �������� �����
  // ��������, ��� ��� ��� ���� ��������
  while (down || processed != NULL) {
    if (down) {
      if (current == NULL) {
        // ������ ����������� ��������
        down = false;
      } else {
        // ���������� ���� �� ������ �� ���� ���
        Node *w = current->left;
        current->left = processed;
        processed = current;
        current = w;
      }
    } else {
      if (processed->flag) {
        // ��������������� ��������� � ������������ ����� �� ������
        processed->flag = false;
        Node *w = processed->right;
        processed->right = current;
        current = processed;
        processed = w;
      } else {
        // �������� ������� ��� �������� �� ������ ��������� � ������
        actor.action(processed->item);
        // ��������� � ��������� ������� ���������
        Node *w = processed->right;
        processed->flag = true;
        processed->right = processed->left;
        processed->left = current;
        current = w;
        // ����� ��������� ����
        down = true;
      }
    }
  }
}

#endif

