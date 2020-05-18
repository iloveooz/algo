/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.2. ���������� �� ��������                         *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : hashtable.h                                      *
*  �������� : ���-������� �������� ������������� ���� � ������ *
*             ������ ���� "������". ���������� � �������       *
*             �������� ������ �� �������� �������              *
***************************************************************/

#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <string>
#include <exception>

using namespace std;

class NullValueException : public exception {
  const char * reason;

public :
  NullValueException(const char * why = "Null value is not valid")
    : reason(why) {}
  const char * what() const throw() { return reason; }
};

//=============================================================
// �����, �������������� ���-������� ��� (����, ��������),
// ������ ������ �������� ������, � ��������� ����� ����
// ������������ ������. � ������� �������� �� ���� ��� �������,
// � ������ �� ���.
//=============================================================
template <class Object>
class HashTable {

protected:

#ifndef P
#define P        557
#endif
#ifndef Q
#define Q        811
#endif
#ifndef LENGTH
#define LENGTH   1000
#endif

  //============================================================
  // ������� ������, ���������� ���� � ��������� � ��� ������
  //============================================================
  struct ListElem {
    string key;        // ����
    Object *obj;       // ��������� ������
    ListElem *next;    // ������ �� ��������� �������

    // ������� ����������� ��� �������� ��������� ������
    ListElem(const string & k, Object *o, ListElem *n) {
      key = k;
      obj = o;
      next = n;
    }
  };

  // ������ �������, ���������� ����� �������
  ListElem * dict[LENGTH];

public:

  //============================================================
  // �����������
  //============================================================
  HashTable() { memset(dict, 0, sizeof(dict)); }

  //============================================================
  // ����������
  //============================================================
  virtual ~HashTable() { destroy(); }

  //============================================================
  // ������� �����������, ���������� �� �������� ����� ��������
  //============================================================
  static int hash(const string str);

  //============================================================
  // ������� ���������� ������ ������� �� �����. ���� ������,
  // ��������� � ���� ������, ��� ���������� � �������,
  // �� ����� ������ �������� ����� ������, � ������ ��������
  // ������������ � �������� ���������� ������ �������.
  //============================================================
  Object * add(const string key, Object * obj);

  //============================================================
  // ������� ������ ������� �� �����. ���� ���� �� ������,
  // �� ������� ���������� ������ ������
  //============================================================
  Object * find(const string key) const;

  //============================================================
  // ������� �������� ������� �� ��������� �����.
  // ��������� ������� - ��������� �� ��������� ������.
  // ���� ���� �� ������, �� ������� ���������� ������ ������
  //============================================================
  Object * remove(const string key);

protected :
  //============================================================
  // ��� ������� ��������� ��������� ������� ��� ������
  // �����������. �������, ���������� � �������, ����� �����������.
  //============================================================
  void destroy();
};

template <class Object>
int HashTable<Object>::hash(const string str) {
  int sum = 0;
  for (int i = 0; str[i]; i++) {
    sum += str[i] + i;
  }
  return ((P * sum + Q) & 0x7FFF) % LENGTH;
}

template <class Object>
Object * HashTable<Object>::add(const string key, Object * obj) {
  if (key == "" || obj == NULL) {
    throw NullValueException();
  }

  int index = hash(key);            // �������� hash-�������
  ListElem *current = dict[index];  // ������� ������� ������

  // ����� ����� � �������:
  while (current && key != current->key) {
    current = current->next;
  }

  Object * result = NULL;
  if (current) {                    // ���� ��� ���� � �������
    result = current->obj;
    current->obj = obj;
  } else {
    // ������� ����� ������� ������ � ��������� � ������ ������
    ListElem * newElem = new ListElem(key, obj, dict[index]);
    dict[index] = newElem;
  }
  return result;
}

template <class Object>
Object * HashTable<Object>::find(const string key) const {
  if (key == "") {
    throw NullValueException();
  }

  int index = hash(key);            // �������� hash-�������
  ListElem *current = dict[index];  // ������� ������� ������

  // ����� ����� � �������:
  while (current && key != current->key) {
    current = current->next;
  }
  if (current == NULL) return NULL;  // ���� �� ������
  return current->obj;
}

template <class Object>
Object * HashTable<Object>::remove(const string key) {
  if (key == "") {
    throw NullValueException();
  }

  int index = hash(key);            // �������� hash-�������
  ListElem *current = dict[index];  // ������� ������� ������
  ListElem *pred = NULL;            // ���������� ������� ������

  // ����� ����� � �������:
  while (current && key != current->key) {
    pred = current;
    current = current->next;
  }
  if (current == NULL) return NULL;  // ���� �� ������
  // ���������� �������� �� ������:
  if (pred == NULL) {
    dict[index] = current->next;
  } else {
    pred->next = current->next;
  }
  // ������� ����������:
  Object * result = current->obj;
  delete current;
  return result;
}

template <class Object>
void HashTable<Object>::destroy() {
  for (int i = 0; i < LENGTH; i++) {
    ListElem * current = dict[i];
    ListElem * pred = NULL;
    while (current) {
      delete current->obj;
      pred = current;
      current = current->next;
      delete pred;
    }
    dict[i] = NULL;
  }
}

#endif
