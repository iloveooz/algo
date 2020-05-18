/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.3. ����� � �������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : lexical.h                                        *
*  �������� : ����������� ������� Lexical � LexAnalyzer        *
***************************************************************/

#ifndef __LEXICAL_H
#define __LEXICAL_H

//==============================================================
// ����� Lexical ������������ ���� �������
//==============================================================

class Lexical {
  int lexClass;    // ����������� �����
  int value;       // ��������, �������������� ������� - ����� ��� ���� ��������

public:

  // ����������� ������
  enum LexType {
    OPERAND = 1,   // ������� (�����)
    OPERATOR,      // ���� ��������
    LEFTPAR,       // ����� (�����������) ������
    RIGHTPAR       // ������ (�����������) ������
  };

  // ����������� (������ ������� ������������ �����)
  Lexical(int lexClass = OPERAND, int value = 0) :
      lexClass(lexClass), value(value)
    {}

  // ����������� �����������
  Lexical(const Lexical & lexeme) :
      lexClass(lexeme.lexClass), value(lexeme.value)
    {}

  // ������� ������� - ������ ��� ������
  int getLexClass() const { return lexClass; }
  char getOperSign() const { return lexClass == OPERATOR ? (char)value : 0; }
  int getValue() const { return lexClass == OPERAND ? value : 0; }
};

//==============================================================
// ������ (��������) LexAnalyzer ���������� ������������������ ������
//==============================================================

class LexAnalyzer {
  // ��������� �� ������������� �����
  char * ptr;

private:

  // ������� ������ ��������� �� ������ �������� ������.
  void findSymbol();

public:

  // ����������� ������������� ��������� �� ������ ������ ������
  LexAnalyzer(char * src) : ptr(src) {}

  // ����������� ����������� ������ ��������� ��������� ���������
  LexAnalyzer(const LexAnalyzer & analyzer) : ptr(analyzer.ptr) {}

  // ������� ������ ��������� �������
  Lexical next();

  // ���� �� ��� �������?
  bool hasNext();
};

#endif
