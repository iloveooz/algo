/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : lexical.h                                        *
*  �������� : �������� ��������� ������, ������������ ���      *
*             ������� ���������                                *
***************************************************************/

#ifndef __LEXICAL_H
#define __LEXICAL_H

#include <string>

using namespace std;

//=============================================================
// ����������� ����� Lexical ������������ ����������� �������
// � ���������� ��������� ����������� ������ ��� �����������
//=============================================================
class Lexical {
public :
  // ���������� ��������� ����������� ������
  enum LexClass {
    NUMBER = 1,
    VARIABLE,
    OPERATOR,
    LEFTPAR,
    RIGHTPAR
  };

  virtual int getLexClass() const = 0;
};

//=============================================================
// ����� LexNumber ������������ ������� - ����� �����
//=============================================================
class LexNumber : public Lexical {
protected :
  int number;     // �������������� �����

public :
  // ����������� �������
  LexNumber(int num) : number(num) {}

  // ������� ����������� ������ �������
  int getLexClass() const { return Lexical::NUMBER; }
  // ������� �������
  int getNumber() const { return number; }
};

//=============================================================
// ����� LexVariable ������������ ������� - �������������
//=============================================================
class LexVariable : public Lexical {
protected :
  string variable;   // �������������� �������������

public :
  // ����������� �������
  LexVariable(const string & v) : variable(v) {}

  // ������� ����������� ������ �������
  int getLexClass() const { return Lexical::VARIABLE; }
  // ������� �������
  string getVariable() const { return variable; }
};

//=============================================================
// ����� LexOperator ������������ ������� - ���� �������� ��� ������
//=============================================================
class LexOperator : public Lexical {
protected :
  char oper;   // �������������� ���� �������� ��� ������

public :
  // ����������� �������
  LexOperator(char oper) : oper(oper) {}

  // ������� ����������� ������ �������
  int getLexClass() const {
    return
      (oper == '(' ? Lexical::LEFTPAR :
       oper == ')' ? Lexical::RIGHTPAR :
       Lexical::OPERATOR);
  }

  // ������� ���������� ���������� ��������
  int getPrio() const {
    return (oper == '-' || oper == '+' ? 1 :
            oper == '*' || oper == '/' || oper == '%' ? 2 : 0);
  }

  // ������� �������
  char getOperSign() const { return oper; }
};

#endif
