/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : context.h                                        *
*  �������� : ������������� ������� ��� ������ ����������      *
*             � ���������                                      *
***************************************************************/

#ifndef __CONTEXT
#define __CONTEXT

#include "hashtable.h"
#include "expression.h"

class Context : public HashTable<Expression> {
// public :
//   Expression * add(const char * key, Object * obj);
//   Expression * find(const char * key) const;
//   Expression * remove(const char * key);
};

#endif
