/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.6. �������� ������� ������                        *
*                                                              *
*  �����    : A.Koubenski                                      *
*  ����     : words.cpp                                        *
*  �������� : ���������� ���������� ��������� ���� � ������    *
*             ����� � ���������� �������� �����                *
***************************************************************/

#include "words.h"

bool operator < (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) < 0;
}

bool operator == (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) == 0;
}

bool operator > (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) > 0;
}

bool operator <= (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) <= 0;
}

bool operator >= (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) >= 0;
}

bool operator != (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) != 0;
}

ostream & operator << (ostream & out, const Word & w) {
  return out << w.src;
}

