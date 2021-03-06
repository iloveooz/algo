/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.1. ������������� ���������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : lexanalizer.cpp                                  *
*  �������� : ����������� ���������� ��� ������� ���������     *
***************************************************************/

#include <ctype.h>
#include "lexanalizer.h"

//==============================================================
// ���������� ������������ ��� ������������� ��������� �����
// ������: ����� ��� �����; �������������; ������� ������;
// ����� �������� �������������� ��������.
//==============================================================
void LexAnalizer::getNextLexema() {
  // 1. ���������� ������� � "������" �������
  while (ptr < srcLen && isspace(src[ptr])) ptr++;
  // 2. ����������� ��������� �������� ������
  if (ptr < srcLen && isdigit(src[ptr])) {
    // 2�. ��� ����� - ����������� ����� ��� �����
    int val = 0;
    while (ptr < srcLen && isdigit(src[ptr])) {
      val *= 10;
      val += src[ptr++]-'0';
    }
    nextLexema = new LexNumber(val);
  } else if (ptr < srcLen && isalpha(src[ptr])) {
    // 2�. ��� ����� - ����������� �������������
    int oldPtr = ptr;
    while (ptr < srcLen && (isalnum(src[ptr]))) {
      ptr++;
    }
    nextLexema = new LexVariable(src.substr(oldPtr, ptr-oldPtr));
  } else if (ptr < srcLen && strchr("+-*/()", src[ptr]) >= 0) {
    // 2�. ��� ���� �������� ��� ������
    nextLexema = new LexOperator(src[ptr++]);
  } else {
    // 2�. ����������� ������ - ����������� �������
    ++ptr;
    nextLexema = NULL;
  }
}
