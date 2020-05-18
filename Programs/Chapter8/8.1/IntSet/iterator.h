/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 8. ������� ��� �������� ����������                *
*          8.1. ��� � ������������� ��������                   *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : iterator.h                                    *
*  ��������    : �������� ������������ ���������               *
***************************************************************/

#ifndef __ITERATOR_H
#define __ITERATOR_H

template <class Element>
class Iterator {
public :
  virtual ~Iterator() {}
  virtual bool hasMoreElements() const = 0;
  virtual Iterator<Element> & operator ++() = 0;
  virtual Element operator *() = 0;
};

#endif
