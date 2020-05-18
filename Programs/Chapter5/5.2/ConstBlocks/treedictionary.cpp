/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.2. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : treedictionary.cpp                               *
*  �������� : ���������� �������� ������� �� ���� ���������    *
*             ������ ������ � ��������� ��������� � �������    *
*             ������������� ������ � ������� ���������� �����  *
***************************************************************/

#include "treedictionary.h"
#include "printer.h"

// ������� ���������� ������ ����� � ������� ������ ����������
// � ������������ �������� ������� � ��� �� ������
void TreeDictionary::addWord(string w) {
  addWord(w, &root);
}

// ���������� �������� ���� � ������� ����������� ������� ��
// ������������� ������ � ������� ����������� ������� traverse
void TreeDictionary::intIterator(Actor & actor) {
  traverse(root, actor);
}

// ����������� ������� ���������� ������ ����� � �������
void TreeDictionary::addWord(const string & w, TreeItem ** root) {
  if (*root == NULL) {
    // ��������� ���� ������. ����� ���� ��������� � ������,
    // ���������� �������� ���������� ������ memoryManagement
    TreeItem *item = new (memoryManagement->get()) TreeItem(w);
    *root = item;
  } else if (w < (*root)->word) {
    // ����� ����������� � ����� ���������
    addWord(w, &(*root)->left);
  } else {
    // ����� ����������� � ������ ���������
    addWord(w, &(*root)->right);
  }
}

// ����������� ������� �������������� ������ ������
void TreeDictionary::traverse(TreeDictionary::TreeItem * root, Actor & actor) {
  if (root) {
    traverse(root->left, actor);  // ����� ������ ���������
    actor.act(root->word);        // ����� �����
    traverse(root->right, actor); // ����� ������� ���������
  }
}

// ������� ������ ������� � �������� ����� ���������� � ��������� ����� ������
ostream & operator << (ostream & out, TreeDictionary & dict) {
  Printer p(& out);    // ��������, ����������� �� ����� ��������
  dict.intIterator(p); // ����� ���������
  return out;
}
