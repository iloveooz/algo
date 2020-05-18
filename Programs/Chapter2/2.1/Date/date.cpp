/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.1. ����������� ���� ������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : date.cpp                                         *
*  �������� : ����� ������� ���������� ��� ��� ������������    *
*             ���� ������ Date                                 *
***************************************************************/

#include <stdio.h>
#include "date.h"

//==============================================================
// ������� leapYear ���������, �������� �� �������� ���
// ���������� � ������������ � ��������� �������������� ���������
//==============================================================
bool leapYear(int year) {
  return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

//==============================================================
// ������� daysInMonth ��������� ���������� ����
// � �������� ������ ��������� ����
//==============================================================
int daysInMonth(int month, int year) {
  // ����� ������� � ���� (��� ������������� ����)
  static int monthLengths[] =
     { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  // � ������ ������� ����������� ���� ����������� ���� ����
  return monthLengths[month-1] + (month == FEBRUARY && leapYear(year));
}

//==============================================================
// �������������� ����. 
// �������������� ������ ���� ������� ������ ���: dd-mmm-yyyy
//==============================================================

const char * Date::format() const {
  // �������� ������� � ������� mmm
  static const char * monthNames[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" 
  };

  // ��� ���������� ������������� ���������� �����
  char * result = new char[12];
  // ���� ������������� � ������������ � �����
  sprintf(result, "%2d-%s-%4d", 
          getDate(), monthNames[getMonth() - 1], getYear());
  return result;
}