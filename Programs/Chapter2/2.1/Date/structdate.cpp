/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.1. ����������� ���� ������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : structdate.cpp                                   *
*  �������� : ���������� ����������� ���� � ���� ���������     *
*             �� ��� ������ � ���� (d, m, y)                   *
***************************************************************/

#include <stdio.h>
#include "structdate.h"

//==============================================================
// � ��������� ���� �������� ����� ������������� ��������� ����
// ����� ����, ��� ����� �������� ���� ����� �����������
//==============================================================

void StructDate::setMonth(int month) { 
  m = month;
  // ��������, ����� ��������� ���� � ������, 
  // ���� ���� ����� �� ������� ������
  int limit = daysInMonth(m, y);
  if (d > limit) d = limit;
}

void StructDate::setYear(int year) {
  y = year;
  // �������� ��������� ���� � ������ 29 �������
  if (d == 29 && m == FEBRUARY && !leapYear(y))
    d = 28;
}

//==============================================================
// ������� ������
//==============================================================

// ������� addDate � subDate ����������� � ���� �����,
// ��������������� ����������� ���� ����� ����������� (��� ���������)
// ������� � ������ ������. ��� ����� ���� ������ ������������ 
// � ������ �������� ���������� ���� � ���������.

Date & StructDate::addDate(int days) {
  if (days < 0) return subDate(-days);
  // ���� �� �������
  while (days > 0) {
    int mDays = daysInMonth(m, y);
    if (d + days <= mDays) {
      // ����� �����: ����� �������� ������ �� �����
      d += days;
      days = 0;
    } else {
      // ��������� � ������� ����� ���������� ������
      days -= (mDays - d + 1);
      d = 1;
      // ��������, ��������� ������� ���
      if (++m > DECEMBER) {
        m = JANUARY;
        y++;
      }
    }
  }
  return *this;
}

Date & StructDate::subDate(int days) {
  if (days < 0) return addDate(-days);
  // ���� �� �������
  while (days > 0) {
    if (days < d) {
      // ����� �����: ����� �������� ������ �� �����
      d -= days;
      days = 0;
    } else {
      // ��������� � ���������� ����� ����������� ������,
      // ��� ����, ��������, ��������� ������� ���
      if (--m < JANUARY) {
        m = DECEMBER;
        y--;
      }
      days -= d;
      d = daysInMonth(m, y);
    }
  }
  return *this;
}

// ����� �� ������������ ����� ������� ��������������
// ������� ������������. ��������, ����������� ��������� ����

Date & StructDate::addMonth(int months) {
  if (months < 0) return subMonth(-months);
  // ��������� ������/����
  y += months / 12;
  m += months % 12;
  if (m > DECEMBER) {
    m -= 12; y++;
  }
  // ��������� ��������� ���� � ������, ���� ������� ����� 
  // ������� �� ������� �������� ������
  int limit = daysInMonth(m, y);
  if (d > limit) d = limit;
  return *this;
}

Date & StructDate::subMonth(int months) {
  if (months < 0) return addMonth(-months);
  // ��������� ������/����
  y -= months / 12;
  m -= months % 12;
  if (m < JANUARY) {
    m += 12; y--;
  }
  // ��������� ��������� ���� � ������, ���� ������� ����� 
  // ������� �� ������� �������� ������
  int limit = daysInMonth(m, y);
  if (d > limit) d = limit;
  return *this;
}

// ������� ������ ���� ������ ������ ���. ���������
// ���� ����� ������������ ������ � ������ 29 �������

Date & StructDate::addYear(int years) {
  y += years;
  if (d == 29 && m == FEBRUARY && !leapYear(y))
    d = 28;
  return *this;
}

Date & StructDate::subYear(int years) {
  y -= years;
  if (d == 29 && m == FEBRUARY && !leapYear(y))
    d = 28;
  return *this;
}

// �������� ������������ ���������� ��� ��������� ������
// ������, ������������ � ����������� ���� ������. �������
// ����� ���������� ������������ �� ������� �� �����������
// ������������� ���������.

Date & StructDate::operator = (const Date & date) {
  d = date.getDate();
  m = date.getMonth();
  y = date.getYear();
  return *this;
}

// ��������� ��������� ��� ����� ���������� ������ ������
// ������������ ���� ������ ��� ����������. ����������� ������
// ��� ��������� ���������, ���������� ��������� ������������ ��,
// ������� ���� ���������� � ������ Date.

bool StructDate::operator < (const Date & date) const {
  int date_d = date.getDate();
  int date_m = date.getMonth();
  int date_y = date.getYear();
  return y < date_y ||
        (y == date_y && (m < date_m ||
                        (m == date_m && d < date_d)));
}

bool StructDate::operator == (const Date & date) const {
  return y == date.getYear() && m == date.getMonth() && d == date.getDate();
}

bool StructDate::operator > (const Date & date) const {
  int date_d = date.getDate();
  int date_m = date.getMonth();
  int date_y = date.getYear();
  return y > date_y ||
        (y == date_y && (m > date_m ||
                        (m == date_m && d > date_d)));
}
