/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : lexanalizer.h                                    *
*  �������� : ����������� ���������� ��� ������� ���������     *
***************************************************************/

#ifndef __LEX_ANALIZER_H
#define __LEX_ANALIZER_H

#include <string>
#include "lexical.h"
#include "iterator.h"

using namespace std;

typedef Lexical * PLexical;

class LexAnalizer : public Iterator<PLexical> {
  string src;
  int srcLen;
  int ptr;
  PLexical nextLexema;

public :
  // �����������
  LexAnalizer(const string & source) : src(source), ptr(0), srcLen(source.length()), nextLexema(NULL) {
    getNextLexema();
  }

  // �������, ����������� ��������� ���������
  bool hasMoreElements() const { return nextLexema != NULL; }
  // ��������������, ��� �������� ���������� ������� ������ Lexical
  PLexical & operator *() { return nextLexema; }
  const PLexical & operator *() const { return nextLexema; }
  Iterator<PLexical> & operator ++() { getNextLexema(); return *this; }
  // ������� ������� ��� ������� ������:
  int getCurrentPosition() const { return ptr; }

private :
  void getNextLexema();
};

#endif
