/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.3. �������, �������������� �������� � ���������   *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : �������� ������ �������, ��������������� ������� *
***************************************************************/

#include <string>
#include <iostream>
#include "listdictionary.h"
#include "wordsiterator.h"
#include "pair.h"
#include "iterator.h"

using namespace std;

//==============================================================
// ������� frequentWord ������� � �������� ������ �����,
// ������������� � ��� ������������ ����� ���. � ����������
// ������ ������� ������ ���� �� ���������� ����� �
// ����� ��� ���������� � ������.
//==============================================================

Pair<int> frequentWord(char * text) {
  WordsIterator iterator(text);  // �������� ���� ������
  ListDictionary<int> dict;      // ������� �� ���������� ����
  
  // 1. ��������� ���� � �������
  while (iterator.hasMoreElements()) {
    // ����� ���������� �����:
    char * token = strlwr(*iterator);
    // ���� � ������� ��� ����� � ���������� ��������� � ��� �������:
    int * wordCounter = dict.find(token);
    if (wordCounter == NULL) {
      // ����� ��� �� ����; ������� ��� � ������� �� ��������� = 1
      dict.add(token, 1);
    } else {
      // ����� ��� ����; ����������� �������� �������� �� 1
      ++*wordCounter;
    }
    // ��������� � ���������� �����
    ++iterator;
  }
  
  // 2. ����� ����� � ������������ ��������
  Pair<int> maxPair("", 0);         // ���� � ������������ ������ ����������
  Iterator<Pair<int> > *i = dict.iterator(); // �������� �������
  while (i->hasMoreElements()) {
    Pair<int> &nextPair = **i;
    // ���������� �������� ���� ���
    if (nextPair.obj > maxPair.obj) {
      maxPair = nextPair;
    }
    // ��������� � ��������� ����
    ++*i;
  }
  delete i;
  
  // 3. ������ ����������
  return maxPair;
}

//==============================================================
// ������������ ������� frequentWord � ������ �������.
// ��� ������� ��� �������� ������������� ������ �� "�����"
//==============================================================

int main() {
  char * text =
    "Deep into that darkness peering, long I stood there wondering, fearing,\n"
    "Doubting, dreaming dreams no mortal ever dared to dream before;\n"
    "But the silence was unbroken, and the stillness gave no token,\n"
    "And the only word there spoken was the whispered word, \"Lenore?\"\n"
    "That I whispered, and the echo murmured back the word, \"Lenore!\"\n"
    "Merely this and nothing more.\n";
  Pair<int> maximum = frequentWord(text);
  cout << "Word " << maximum.key << " has " << maximum.obj << " entrances in the text\n" << text;

  return 0;
}
