/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.6. �������� ������� ������                        *
*                                                              *
*  �����    : A.Koubenski                                      *
*  ����     : main.cpp                                         *
*  �������� : ������� �������� ������ ������� ������ � ������  *
*             �� �����.                                        *
***************************************************************/

#include "tree.h"
#include <iostream>
#include "iterator.h"
#include "words.h"

using namespace std;

// ������� ������ ������ ����� � ������ ������ � ������ �������
void binSearch(Tree<int> & t, int key) {
  int * keyFound = t.search(key);
  cout << "Key " << key
       << (keyFound ? " found successfully" : " not found")
       << " in the tree" << endl;
}

// ������� ������ ���� ������ � �������� �����
// � ������������������ (����������) �������.
void sortWords(char * source, ostream & out) {
  Tree<Word> words;
  char * delimeters = ",.?!;:-\'\" \t\n\r\f";
  for (char * nextToken = strtok(source, delimeters);
       nextToken;
       nextToken = strtok(NULL, delimeters)) {
    words.insertLeaf(Word(nextToken));
  }
  out << words << endl;
}

int main() {
  // ������ ������ �� �����
  Tree<int> t;
  t.insertLeaf(10);
  t.insertLeaf(3);
  t.insertLeaf(20);
  t.insertLeaf(15);
  t.insertLeaf(30);
  t.insertLeaf(2);
  t.insertLeaf(5);
  t.insertLeaf(32);
  t.insertLeaf(22);
  // ����� ����� ������ � �������� ����� � ������� �������������� ������
  cout << t << endl;

  // ����� � ������ �� �����
  binSearch(t, 15);    // ����� ������ ���� ��������
  binSearch(t, 23);    // ����� ������ ���� ���������

  // ��������� � ������ ������ ����� ������� 17...
  t.insertLeaf(17);
  // ...� ���������, ��� ������ �� ��������
  cout << t << endl;

  // ������ ������� ���� ������� �� �����...
  t.remove(22);
  // ...����� �� ���� � ������������ ����������...
  t.remove(20);
  // ...�, �������, �� �����
  t.remove(17);

  // ���������, ��� ����������
  cout << t << endl;

  sortWords("Jackdaws love my big sphinx of quartz. "
            "A quick brown fox jumps over the lazy dog", cout);

  return 0;
}
