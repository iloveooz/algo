/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.2. ������ � ����������� ������ �� ��������� ����� *
*               � ������ ������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : main.cpp                                         *
*  �������� : ������� ���������� ��������������� ��������      *
*             ���������                                        *
***************************************************************/

#include "grammar.h"
#include <iostream>

using namespace std;

// ��������� ����, �������������� ����� ������� ������.
// � ���� ������� �������� ��������� ����� 'a', 'o' � 'e'
class Vowel : public Lang {
public :
  bool contains(const string & word) const {
    return word == "a" || word == "o" || word == "e";
  }
};

// ��������� ����, �������������� ����� ��������� ������.
// � ���� ������� ���������� ��������� ����� 'b', 'c' � 'd'
class Consonant : public Lang {
public :
  bool contains(const string & word) const {
    return word == "b" || word == "c" || word == "d";
  }
};

// ������� info ������������� ��� ������ ���������� � ���,
// ������ �� �������� ����� w � �������� ���� lang.
void info(const Lang & lang, const string & w) {
  cout << w << " - a "
       << (lang.contains(w) ? "write" : "wrong")
       << " word\n";
}

//--------------------------------------------------------------
// ����� Digit ������������ ���� ��� ����,
// ��������� �� ������������� ������� - �����
//--------------------------------------------------------------
class Digit : public Lang {
public :
  bool contains(const string & s) const {
    return s.length() == 1 && s[0] >= '0' && s[0] <= '9';
  }
};

int main() {
  SmartPtr<Lang> vow(new Vowel);
  SmartPtr<Lang> cons(new Consonant);

  // ��������� ����, �������������� �������� ���� ����������� �����.
  // � ���� ������� �������, ��� �������� ���� ������� �� ����� ���������
  // � ����� ��� ���� ������� ����
  SmartPtr<Lang> cyllable = (cons & vow) | (cons & vow & vow);
  SmartPtr<Lang> word = ~cyllable;

  info(*word, "do");
  info(*word, "bee");
  info(*word, "bead");
  info(*word, "coca");
  info(*word, "cola");
  info(*word, "boodoo");

  cout << endl;

  SmartPtr<Lang> plus(new OneLetterLang('+'));    // ���� "+"
  SmartPtr<Lang> minus(new OneLetterLang('-'));   // ���� "-"
  SmartPtr<Lang> point(new OneLetterLang('.'));   // ���������� �����
  SmartPtr<Lang> digit(new Digit);                // ���������� �����

  // ���������� ������� ��������� �� ���� �������:
  SmartPtr<Lang> sign = plus | minus;               // ���� �����
  SmartPtr<Lang> pos_sign = +sign;                  // ���� ��� �����
  SmartPtr<Lang> unSigned = ~digit;                 // ����������� �����
  SmartPtr<Lang> integral = pos_sign & unSigned;    // ����� �� ������
  SmartPtr<Lang> fraction = point & unSigned;       // ������� ����� �����
  SmartPtr<Lang> pos_fraction = +fraction;          // ������� ����� ��� �����
  SmartPtr<Lang> number = integral & pos_fraction;  // ���������� �����

  // ��������� ����������� ���������� ����� �� ��������:
  string testNumbers[] = {"+12", "-22222222222.33333333333333", "3.141693", "", "333-", "-11111+222222"};
  for (int i = 0; i < sizeof(testNumbers)/sizeof(string); i++) {
    string nextWord = testNumbers[i];
    cout << "<" << nextWord << "> ";
    // ���������, ����������� �� �������� ����� ���������� �����
    cout << (number->contains(nextWord) ? "Number" : "Not number") << endl;
  }
  cout << endl;

  return 0;
}
