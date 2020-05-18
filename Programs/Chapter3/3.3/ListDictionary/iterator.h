/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.3. �������, �������������� �������� � ���������   *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : iterator.h                                       *
*  �������� : ��������� �������� ���������                     *
***************************************************************/

#ifndef __ITERATOR_H
#define __ITERATOR_H

//=============================================================
// �����, �������������� ����������� ��������� �������� ���������
//=============================================================

template <class T>
class Iterator {
public :
  // �������� ��������� ��������
  virtual bool hasMoreElements() const = 0;

  // "�����" ��������� �� ��������� �������
  virtual Iterator<T> & operator ++() = 0;

  // ������ � ������������ ��������
  virtual T & operator *() = 0;
};

#endif
