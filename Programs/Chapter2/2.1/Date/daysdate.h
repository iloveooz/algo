/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.1. ����������� ���� ������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : daysdate.h                                       *
*  �������� : ���������� ���������� ��� ��� ������������� ���� *
*             � ���� �������� ���� - �������� ������           *
***************************************************************/

#ifndef __DAYS_DATE_H
#define __DAYS_DATE_H

#include "date.h"

//==============================================================
// � ���� ������ ���� �������������� ��������� ����������� � ���� 
// �������� ����, ��������� � ������ 1600 ����
// (�� 31 ������� 1599 ����). ����������� ������ ��������� ���� �
// ��������� �� 1 ������ 1600 ���� �� 31 ������� 9999 ����.
//==============================================================

class DaysDate : public Date {
  // ������� ����, ��������� � 31 ������� 1599 ����
  long days;

public:

  // ����������� ������� "�����������" ����.
  DaysDate();

  // ����������� �����������
  DaysDate(const DaysDate & date) { days = date.days; }

  // ����������� ���� "�� �����"
  DaysDate(int d, int m, int year);

  // �������, ���������� ��������������� ��� �������������.

  // ������� ������� � �����
  void setDate(int day);
  int getDate() const;
  void setMonth(int month);
  int getMonth() const;
  void setYear(int year);
  int getYear() const;

  // ������� ������ ����
  Date & addDate(int days = 1);
  Date & subDate(int days = 1);
  Date & addMonth(int months = 1);
  Date & subMonth(int months = 1);
  Date & addYear(int years = 1);
  Date & subYear(int years = 1);

  // �������� ������������
  Date & operator = (const Date & date);

  // ��������� ���������
  bool operator < (const Date & date) const;
  bool operator == (const Date & date) const;
  bool operator > (const Date & date) const;
  bool operator <= (const Date & date) const;
  bool operator != (const Date & date) const;
  bool operator >= (const Date & date) const;
};

#endif
