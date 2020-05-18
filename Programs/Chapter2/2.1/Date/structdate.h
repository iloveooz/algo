/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.1. ����������� ���� ������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : structdate.h                                     *
*  �������� : ���������� ����������� ���� � ���� ���������     *
*             �� ��� ������ � ���� (d, m, y)                   *
***************************************************************/

#ifndef __STRUCT_DATE_H
#define __STRUCT_DATE_H

#include <time.h>      // ��� ������� time ����������� ������� ����
#include "date.h"

class StructDate : public Date {
  int d;    // ����� ��� 1-31
  int m;    // ����� ������ 1-12 (JANUARY - DECEMBER)
  int y;    // ����� ���� (1600-9999)

public:

  // ������������

  StructDate(int d, int m, int y) {
    StructDate::d = d;
    StructDate::m = m;
    StructDate::y = y;
  }

  StructDate() {
    // ������� ���� ������� � ������� ������� 'time' �� ������ TIME
    time_t tm;
    time(&tm);
    struct tm * dt = localtime(&tm);
    d = dt->tm_mday;
    m = dt->tm_mon + 1;
    y = dt->tm_year + 1900;
  }

  StructDate(const Date & date) {
    // ����������� ����������� ����� ������������
    *this = date; 
  }

  //============================================================
  // ������� �������, ������ ������, ����������� ����������������
  // ���������� � ��������������� �����. ������, ��� ���������
  // ������ � ���� ����� ����� ������������� ��������� ���.
  //============================================================

  void setDate(int day) { d = day; }
  int getDate() const { return d; }
  void setMonth(int month);
  int getMonth() const { return m; }
  void setYear(int year);
  int getYear() const { return y; }

  //============================================================
  // ������� ������ ���
  //============================================================

  Date & addDate(int days = 1);
  Date & addMonth(int months = 1);
  Date & addYear(int years = 1);
  Date & subDate(int days = 1);
  Date & subMonth(int months = 1);
  Date & subYear(int years = 1);

  // �������� ������������ ���������� � ������������ � ������������
  // ��� ������� ���������: �� ���������� ������ �� ���������� ����.

  Date & operator = (const Date & date);

  // ��������� ��������� ��� ���������� ������������������ ������� ���

  bool operator < (const Date & date) const;
  bool operator == (const Date & date) const;
  bool operator > (const Date & date) const;
};

#endif
