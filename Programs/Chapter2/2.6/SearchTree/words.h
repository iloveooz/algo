/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.6. �������� ������� ������                        *
*                                                              *
*  �����    : A.Koubenski                                      *
*  ����     : words.h                                          *
*  �������� : ����������� ���������� ��������� �������� ���    *
*             ������������� �����                              *
***************************************************************/

#ifndef __WORDS_H
#define __WORDS_H

#include <string.h>
#include <iostream>

using namespace std;

class Word;    // ��������������� �������� ������

// ���������� ����������, ����������� ��� ��������� ����
// � ������ ���� � ���������� �������� �����
bool operator < (const Word &, const Word &);
bool operator > (const Word &, const Word &);
bool operator <= (const Word &, const Word &);
bool operator >= (const Word &, const Word &);
bool operator == (const Word &, const Word &);
bool operator != (const Word &, const Word &);
ostream & operator << (ostream &, const Word &);

/***************************************************************
*  ����������� ������ ��� ����� - ��������� �� ������������    *
*  ������ ��� ��������� � ������ � ���������� �����            *
***************************************************************/
class Word {
  // ��������� ��������� � ������ ���� � �������� �����
  // ������ ����� ������ � ���������� ��������� ����� 
  friend bool operator < (const Word &, const Word &);
  friend bool operator > (const Word &, const Word &);
  friend bool operator <= (const Word &, const Word &);
  friend bool operator >= (const Word &, const Word &);
  friend bool operator == (const Word &, const Word &);
  friend bool operator != (const Word &, const Word &);
  friend ostream & operator << (ostream &, const Word &);

  const char * src;    // ��������� �� ������

public:

  // ������������ ����
  Word() : src("") {}
  Word(const Word & w) : src(w.src) {}
  Word(char * s) : src(s) {}
};

#endif
