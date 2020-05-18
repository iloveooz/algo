/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.2. ����� � �������                                *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : boundstackfactory.cpp                            *
*  �������� : ����� ������������ ����������, ����������        *
*             ��������� �� ������� ������ ���������� ��������� *
***************************************************************/

#include "boundstack.h"

//==============================================================
// ��� ���������� - StackFactory<char> �� ���� �����������
// ������� ������, ��������� (�����������) ����� ��������.
// ������������� ���������� ����������, ��� ������ ����������
// ������������� ����� ���������� ��� ������������� ������.
//==============================================================

StackFactory<char> * stackFactory = new BoundStackFactory<char>;
