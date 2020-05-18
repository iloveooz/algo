/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.3. �������, �������������� �������� � ���������   *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : treedictionary.h                              *
*  ��������    : �������, ������������� � ���� ���������       *
*                ������ ������                                 *
***************************************************************/

#ifndef __TREE_DICTIONARY_H
#define __TREE_DICTIONARY_H

#include <string>
#include "tree.h"
#include "pair.h"

using namespace std;

//==============================================================
// ����������� ������� TreeDictionary �������� �� ��������
// ������ ������, ���������� � ����� ���� �� ���������� ����� �
// ���������� � ��� ��������.
//==============================================================

template <class Object>
class TreeDictionary {
  // ������ tree �������� ������������� ������ ���
  Tree<Pair<Object> > tree;

public :
  // ������� ��������� � ������ ����� ����
  void add(string key, const Object & obj) {
    tree.insertLeaf(Pair<Object>(key, obj));
  }

  // ������� ������������ ����� ���� �� ����� � �������
  // ��������� ����, ���� ��� � ������ ����
  void remove(string key) {
    tree.remove(Pair<Object>(key));
  }

  // ������� ������ ���������� ������� �� �����
  Object * find(string key) const {
    Pair<Object> * found = tree.search(Pair<Object>(key));
    return found ? &found->obj : NULL;
  }

  // ������� ������ ������� �������� ���, ��������� �������
  // �������� �������������� ������
  Iterator<Pair<Object> > * iterator() const {
    return tree.iterator();
  }
};

#endif
