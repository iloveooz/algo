/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.1. ������� ������������� �����                    *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : ListString.h                                     *
*  �������� : ������������� ������ � ���� ������ ���������,    *
*             ���������� ��������� ������                      *
***************************************************************/

#ifndef __LIST_STRING_H
#define __LIST_STRING_H

#include <stdlib.h>
#include <string.h>
#include <exception>
#include <iostream>

using namespace std;

class IndexException : public exception {
  const char * reason;

public:

  IndexException(const char * why) : exception(), reason(why) {}
  IndexException() : exception(), reason("Wrong index") {}
  const char * what() const throw() { return reason; }
};

class ListString {

  friend ostream & operator <<= (ostream & out, const ListString & src);

public :
  #define ITEM_SIZE 16        // ������������ ������ ��������

protected :

  //-------------------------------------------------
  // ��������������� ������:
  // - StringItem ������������ ������� ������,
  //   ���������� �� 1 �� 16 ��������;
  // - SymbolPosition ������������ ����� ������� ������ 
  //   ������ - ���� �� ��������� �� ������� � ������
  //   ������� ������ ��������.
  //-------------------------------------------------

  struct StringItem {
    char symbols[ITEM_SIZE];  // ������ ��������
    StringItem *next;         // ��������� �� ��������� �������
    unsigned short size;      // ���������� ��������

    //--------------------------------------------------
    // ����������� ��� �������� ������� ��������� ������
    // �������� ������, ����� �� �� ��������� ������
    // ITEM_SIZE, � ��������� �� � ������ ���������
    //--------------------------------------------------
    StringItem(const char *src, StringItem *nextItem = NULL);
  };

  struct SymbolPosition {
    StringItem *item;      // ������� ������
    unsigned short pos;    // ������� ������ �������� ������

    // ������� �����������
    SymbolPosition(StringItem *i, unsigned short int p) 
      : item(i), pos(p) {}
  };

  // ���������� ������������� ������

  StringItem *first;           // ��������� �� ������ �������

public:
 
  //-------------------------------------------------------
  // ������������ �����
  //-------------------------------------------------------
  ListString() : first(NULL) {}

  ListString(const ListString & src) : first(NULL) {
    *this = src;
  }

  ListString(const char *s) : first (NULL) {
    if (s != NULL && *s != 0) {
      first = new StringItem(s);
    }
  }
 
  //-------------------------------------------------------
  // ����������
  //-------------------------------------------------------
  ~ListString() { destroy(); }

  //-------------------------------------------------------
  // ���������� �������� �������� ��� ��������
  //-------------------------------------------------------
  
  char & operator [] (int index);
  char operator [] (int index) const;

  ListString & operator = (const ListString & src);
  ListString & operator = (const char * src);

  ListString substr(int begin, int end = -1) const;

  int length() const;

  ListString & operator += (const ListString & src);
  ListString & operator += (const char * src);
  ListString & operator += (char ch);

  ListString & insert (int index, const ListString & src);
  ListString & insert (int index, const char * src);

  operator char* () const;

protected:

  //--------------------------------------------------------------
  // ��������������� �������
  //--------------------------------------------------------------

  // ����������� ������, ������� ���������� ������
  void destroy();

  // ���� ��������� ������� � ������������� ������
  StringItem * getLast() const;

  // ���� ������� ������� ������ � �������� ��������
  SymbolPosition findPos(int index) const;
};

//-------------------------------------------------------
// ��� ��������, �������� � �������� ���������� �����
// ������������ ��������� ������ (����� ���������)
//-------------------------------------------------------

ostream & operator <<= (ostream & out, const ListString & src);

#endif
