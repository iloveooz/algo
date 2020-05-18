/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.3. �������, �������������� �������� � ���������   *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : pair.h                                           *
*  �������� : ���� �� ����� � ��������, ����������� ���������  *
*             �� �����                                         *
***************************************************************/

#ifndef __PAIR_H
#define __PAIR_H

#include <string>

using namespace std;

//==============================================================
// ����� Pair ������������ ������� ������ ���� - ���� �� �����
// � ���������� � ��� �������. ��� ��������� ��� ���������������
// ��������� ���������, ������� ���������� ���������� ������
// ������ �������� ��� - �����.
//==============================================================

template <class Object>
struct Pair {
  string key;    // ����
  Object obj;    // ��������� ������

  // ������������
  Pair() {}
  Pair(const string & _key) : key(_key) {}
  Pair(const string & _key, const Object & _obj) : key(_key), obj(_obj) {}
  Pair(const Pair & pair2) : key(pair2.key), obj(pair2.obj) {}

  // �������� ������������
  Pair<Object> & operator = (const Pair<Object> & src) {
    key = src.key;  obj = src.obj;
    return *this;
  }

  // ��������� ���������:

  bool operator == (const Pair<Object> & pair2) const {
    return key == pair2.key;
  }

  bool operator != (const Pair<Object> & pair2) const {
    return key != pair2.key;
  }

  bool operator < (const Pair<Object> & pair2) const {
    return key < pair2.key;
  }

  bool operator <= (const Pair<Object> & pair2) const {
    return key <= pair2.key;
  }

  bool operator > (const Pair<Object> & pair2) const {
    return key > pair2.key;
  }

  bool operator >= (const Pair<Object> & pair2) const {
    return key >= pair2.key;
  }
};

#endif
