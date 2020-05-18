/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.4. ���������                                      *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : Iterator.h                                    *
*  ��������    : �������� ������������ ���������               *
***************************************************************/

#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <stdlib.h>

//**************************************************************
// �������� ������ Iterator
//**************************************************************

template <class Element>
class Iterator {
public :
  virtual ~Iterator() {}
  virtual bool hasMoreElements() const = 0;
  virtual void nextElement() = 0;
  virtual const Element & getCurrent() const = 0;
  virtual Element & getCurrent() = 0;
  virtual void remove() = 0;
};

#endif
