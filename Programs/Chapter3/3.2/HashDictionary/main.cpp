/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.2. ����������� � ����� � ���-��������             *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : ������������ �������, ��������������� � ����     *
*             ���-�������                                      *
***************************************************************/

#include "dictionary.h"
#include "wordsiterator.h"
#include "hashtable.h"
#include <iostream>

using namespace std;

//===============================================================
// ������� twice ���� � �������� ����������� �����, �������������
// ����� ������ ����. ���� ����� ����� ���� - ������� ��� ������,
// ���� ������ ����� ��� - ������� ������ ������ �����
//===============================================================

string twice(const char * text) {
  // ���������� ������� ��� ��������� ������
  HashDictionary dict;

  // �������� ���� ������ ����� ������� ������������� �������,
  // ����� ����������, �������, ������ � ������ "������" �������
  for (WordsIterator iterator(text);
       iterator.hasMoreElements();
       ++iterator) {
    // ������� ��������� ����� � ����������� ��� � ������� �������� ����.
    string nextWord = strlwr((*iterator));
    if (dict.hasWord(nextWord)) {
      return nextWord;       // ����� ��� �����������
    } else {
      dict.add(nextWord);    // ��������� ����� �����
    }
  }
  return string();           // � ����������� ��� ���������� ����
}

int wordsCounter(const char * text, const char * word) {
  HashTable<int> dict;

  for (WordsIterator iterator(text);
       iterator.hasMoreElements();
       ++iterator) {
    // ������� ��������� ����� � ����������� ��� � ������� �������� ����.
    const char * nextWord = strlwr((*iterator));
    int * counter = dict.find(nextWord);
    if (counter == NULL) {
      dict.add(nextWord, new int(1));
    } else {
      ++*counter;
    }
  }
  int * counter = dict.find(word);
  return counter ? *counter : 0;
}

int main() {
  char * text1 = "It was many and many a year ago,\n"
                 "In a kingdom by the sea,\n"
                 "That a maiden there lived whom you may know\n"
                 "By the name of Annabel Lee.";
  char * text2 = "I know the only thing that I know nothing!";
  char * word = "a";

  cout << "Twice: " << twice(text1) << endl;
  cout << "Twice: " << twice(text2) << endl;
  cout << "The \"" << word << "\" word has " << wordsCounter(text1, word)
       << " entrances in the text \"" << text1 << "\"\n";

  return 0;
}
