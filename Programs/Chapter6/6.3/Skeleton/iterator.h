/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 6. ��������� ��������� ������� ����������         *
*          6.3. ����������� �������� ��������                  *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : Iterator.h                                    *
*  ��������    : �������� ������������ ���������               *
***************************************************************/

#ifndef __ITERATOR_H
#define __ITERATOR_H

//==============================================================
// ������ ������� Iterator ���������� ����������� ���������
// ��������� ���������. �������� ������������� ��������
// ��������� ���������� ��������� � ����� �����������.
//==============================================================

template <class Element>
class Iterator {
public :
  // ����������� ����������
  virtual ~Iterator() {}

  // �������� ��������� ��������
  virtual bool hasMoreElements() const = 0;

  // ����� ��������� �� ��������� �������
  virtual Iterator<Element> & operator ++() = 0;

  // ������ � �������� ��������
  virtual const Element & operator *() const = 0;
};

#endif
