/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.2. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : treedictionary.h                                 *
*  �������� : ���������� �������� ������� �� ���� ���������    *
*             ������ ������ � ��������� ��������� � �������    *
*             ������������� ������ � ������� ���������� �����  *
***************************************************************/

#ifndef __TREE_DICTIONARY_H
#define __TREE_DICTIONARY_H

#include "blockbuffer.h"
#include <string>
#include <iostream>

//==============================================================
// ����� Actor ������ ����������� ��������,
// ����������� ��� ������� �� �������
//==============================================================

class Actor {
public :
  virtual void act(string & s) = 0;
};

//==============================================================
// ����� TreeDictionary ��������� ������� �������� ������ ����
// � ��������� ����� ������ � ������� ������������� ������,
// �������������� �������� ������ BlockBuffer
//==============================================================

class TreeDictionary {
  // ��������� ��������� TreeItem ������������ ���� ������
  struct TreeItem {
    string word;      // ���������� � ������� �����
    TreeItem * left,  // ������ �� ����� ��������� (������� �����)
             * right; // ������ �� ������ ��������� (������� �����)
    // ����������� ������ ���������� ����
    TreeItem(string word, TreeItem * left = NULL, TreeItem * right = NULL)
      : word(word), left(left), right(right) {}
  };

  // ������ ������:
  TreeItem * root;
  // ������� ���������� ������� ��� ����� ������
  BlockBuffer<sizeof(TreeItem)> * memoryManagement;

public :

  // ����������� ������ ������� ������ ������
  // � ������� ������� ���������� �������
  TreeDictionary(int capacity)
    : root(NULL),
      memoryManagement(new BlockBuffer<sizeof(TreeItem)>(capacity)) {}

  // ���������� ������� ���������� ������� ���������� �������
  ~TreeDictionary() { delete memoryManagement; }

  // ������� ���������� ������ ����� � �������:
  void addWord(string w);
  // ���������� �������� ���� � ������� �����������:
  void intIterator(Actor & actor);

private:

  // ��������������� ����������� �������, ����������� �������
  // �������� ���������� ������ ���� � ������ �������
  void addWord(const string & w, TreeItem ** root);

  // ��������������� ����������� �������,
  // ����������� ������������� ����� ����� ������
  void traverse(TreeItem * root, Actor & actor);
};

// ������� ������ ���� �� ������� � �������� ����� � ������� �����������
ostream & operator << (ostream & out, TreeDictionary & dict);

#endif