/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.1. ������������� ���������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : dictionary.cpp                                   *
*  �������� : ���������� �������, ��������������� � ����       *
*             ���-�������                                      *
***************************************************************/

#include <string>
#include <iostream>
#include "dictionary.h"

using namespace std;

Iterator<string> & HashDictionary::KeysIterator::operator ++() {
  while (++pos < LENGTH && dict[pos] == NULL) {
//    cout << "pos=" << pos << ", contains:NULL" << endl;
  }
//  cout << "pos=" << pos << (pos < LENGTH ? string(", contains:") + *dict[pos] : "") << endl;
  return *this;
}

int HashDictionary::hash(const string & str) {
  int sum = 0;
  for (int i = 0; i < str.length(); i++) {
    sum += str[i] + i;
  }
  return (P * sum + Q) % LENGTH;
}

int HashDictionary::findPos(const string & word) const {
  int i = hash(word);  // ������� ������ ����� � �������
  for (int counter = 0; counter < LENGTH; counter++) {
    if (dict[i] == NULL || *dict[i] == word) {
      return i;        // ����� ��� ������� ��� ��� ������� �������
    } else if (++i == LENGTH) {
      i = 0;          // ������� � ���������� �������
    }
  }
  return -1;           // ��������� ��� ������� � �������!
}

void HashDictionary::add(const string & word) {
  int i = findPos(word);   // ������� ����� � �������
  if (i == -1) return;     // ������ � ������ ������������ �������!
  if (dict[i] == NULL) dict[i] = new string();
  *dict[i] = word;         // ���������� ����� ��� ��� ����������
}

bool HashDictionary::hasWord(const string & word) const {
  int i = findPos(word);    // ������� ����� � �������
  return i != -1 && dict[i] != NULL;
}

ostream & operator << (ostream & out, HashDictionary & dict) {
  bool printed = false;
  for (int i = 0; i < LENGTH; i++) {
    if (dict.dict[i]) {
      out << (printed ? ", " : "[") << *dict.dict[i];
      printed = true;
    }
  }
  return out << (printed ? "]" : "[]");
}
