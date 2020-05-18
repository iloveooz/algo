/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.1. ����������� ���� ������                        *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : date.h                                           *
*  �������� : ����������� ������������ ������ ���              *
*             ������������� ������������ ���� ������ Date      *
***************************************************************/

#ifndef __DATE_H
#define __DATE_H

// ������ �������, ������������ � ������� ������������� ��������
enum Month {
  JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE,
  JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER,
};

//==============================================================
// ����������� ����� Date ���������� ����������� ��� ������
// '���� �������������� ���������' � ����� �������� ��� ������
//==============================================================

class Date {

public:
  // ����������� ������ ���������� ��� ��������������� � �������-�����������
  virtual ~Date() {}

  // ������� ������� � "�����" ����.

  // ������/������ �����. �������� ������ ���������� � �������� �� 1 
  // �� ���������� ����� �������� ������.
  virtual int getDate() const = 0;
  virtual void setDate(int day) = 0;

  // ������/������ ������. �������� ������ ����� �������� �� 1 �� 12.
  virtual int getMonth() const = 0;
  virtual void setMonth(int month) = 0;

  // ������/������ ����.   
  // �������� ���������� ��� ������������ ���������� �����������.
  // �� ������ ��������� �� ������� ���� �������� ����� 1900 � 2100 ������.
  virtual int getYear() const = 0;
  virtual void setYear(int year) = 0;

  // ������� ������ ��� �� ������������ ��������� ��������.
  // ���� ����� ���������� �� ����� ����� ���� ��������������� ���, �����
  // ��� �� ��������� ���������� ���� � ����� ������������� ������.
  virtual Date & addDate(int days = 1) = 0;
  virtual Date & subDate(int days = 1) = 0;
  virtual Date & addMonth(int months = 1) = 0;
  virtual Date & subMonth(int months = 1) = 0;
  virtual Date & addYear(int years = 1) = 0;
  virtual Date & subYear(int years = 1) = 0;

  // ������������ ������� ����� ����
  virtual Date & operator = (const Date & date) = 0;

  // ��������� 4 ��������� �������� ������ ������������ ��� ��������������� ������� ������.
  // ����� ����� �� ���������� ������� ����� � ����������� ������
  // (� ����������������� ����������� ������ ������� � ����������)
  virtual Date & operator += (int days) { return addDate(days); }
  virtual Date & operator -= (int days) { return subDate(days); }
  virtual Date & operator ++ () { return addDate(); }
  virtual Date & operator -- () { return subDate(); }

  // ��� ��������� ��������� ���������� ���� ����� �����.
  // ��� ��������� � ���������� ���������� ������ "����������� �����"
  // �� ���� ����������, ��������, <, <= � ==. ����������, ������ 
  // ���������� ������ ���������� � ������ ����� ���� ��������.
  virtual bool operator < (const Date & date) const { return !(*this >= date); }
  virtual bool operator == (const Date & date) const { return !(*this != date); }
  virtual bool operator > (const Date & date) const { return !(*this <= date); }
  virtual bool operator <= (const Date & date) const { return !(*this > date); }
  virtual bool operator != (const Date & date) const { return !(*this == date); }
  virtual bool operator >= (const Date & date) const { return !(*this < date); }

  // ������� �������������� ��������� ����������� ���� � ���� ������.
  virtual const char * format() const;
};

// ��������� ����� ������� ��� ������:
// ����������� ������������ ���� �
bool leapYear(int year);
// ���������� ����� ���� � ������
int daysInMonth(int month, int year);

#endif
