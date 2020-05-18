/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 4. ���������� ��������������                      *
*          4.2. ���������� �� ��������                         *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : context.h                                        *
*  �������� : ������������� ������� ��� ������ ��������        *
*             ����������                                       *
***************************************************************/

#ifndef __CONTEXT_H
#define __CONTEXT_H

#include "hashtable.h"
#include "expression.h"

class Context : public HashTable<Constant> {
// public :
//   Constant * add(const char * key, Object * obj);
//   Constant * find(const char * key) const;
//   Constant * remove(const char * key);
};

#endif
