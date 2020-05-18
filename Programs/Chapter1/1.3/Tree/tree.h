/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 1. ������� ������������� �������� ������          *
*          1.3. �������                                        *
*                                                              *
*  �����    : A.���������                                      *
*  ����     : tree.h                                           *
*  �������� : ����������� ������� ������� ��� �������������    *
*             ��������                                         *
***************************************************************/

#ifndef __TREE_H
#define __TREE_H

//**************************************************************
// Tree class definition
//**************************************************************

template <class T>
class Tree {
  // �������� ��������� ���� �� �������� �� ���� � �����
  struct Node {
    T item;         // ��������, ������������ � ����
    Node *son;      // ��������� �� ����
    Node *brother;  // ��������� �� �����

    // ����������� ����
    Node(T i, Node *s = NULL, Node *b = NULL) {
      item = i; son = s; brother = b;
    }
  };

  // ������ ����������� � ���� ��������� �� �������� ����.
  Node *root;

public :

  // ����������� "�� ���������" ������� ������ ������
  Tree() { root = NULL; }

  // ���������� ������ ���������� ������, ������� ������ ������
  ~Tree() { deleteSubtree(root); }

  // ���������� ������
  int height() { return height(root); }

  // ������� ��� ���������� ���������� �����,
  // ����������� � ������ �� �������� ������
  int nodesOnLevel(int level) { return nodesOnLevel(root, level); }

  // ������� ��� ���������� ����� � ������ - 
  // ������������ ������ � �������� �����.
  void add(const T &elem) { add(root, elem); }

private :

  //-----------------------------------------------------------
  // ��������� ����������� ������� ������������ ����� 
  // ����������� ���� �������� ������������ �������
  //-----------------------------------------------------------

  // ����������� ������� ��� ���������� �����
  void add(Node *&node, const T &elem);

  // ����������� ������� ��� ������������ ������
  void deleteSubtree(Node *node);

  // ����������� ������� ���������� ������ ������
  int height(Node *node);

  // ����������� ������� ���������� ���������� ����� �� �������� ������
  int nodesOnLevel(Node *node, int level);
}; // ����� ������ Tree

// ���� ������� ������

// ����������� ������� ��� ������������ ������
template <class T>
void Tree<T>::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->son);
    deleteSubtree(node->brother);
    delete node;
  }
}

// ����������� ������� ���������� ������ ������
template <class T>
int Tree<T>::height(Node *node) {
  if (node == NULL) return 0;
  int max = 0;
  for (Node *current = node->son; current; current = current->brother) {
    int curHeight = height(current);
    if (curHeight > max) max = curHeight;
  }
  return max + 1;
}

// ����������� ������� ���������� ���������� ����� �� �������� ������
template <class T>
int Tree<T>::nodesOnLevel(Node *node, int level) {
  if (node == NULL) return 0;     // ������ ����� - ����� ���
  if (level <= 0) return 0;       // ��� ������ ������!
  // � ��������� ������ ��������� �������� � ������� ������� ����
  return nodesOnLevel(node->son, level-1) +   // ���������� ��� �������� ������� ����
         (level == 1) +                       // ��� ���� ����������� � ����� ������ ���� level==1
         nodesOnLevel(node->brother, level);  // ���������� ��� ��������� �������
}

// ����������� ������� ��� ���������� �����
template <class T>
void Tree<T>::add(Node *&node, const T &item) {
  if (node == NULL) {
    // ���� �� ���� ������ ��� - ������� ����� ���� � 
    // ������������ ��� � ������ � ��������� �����.
    node = new Node(item);
  } else if (item < node->item) {
    // ��������� ���� � ����� ����� ���������
    add(node->son, item);
  } else {
    // ���� ����������� ����-�� � ������� ��������� ����
    add(node->brother, item);
  }
}

#endif

