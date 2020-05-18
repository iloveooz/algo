/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 7. ����� ����������� � ��������� ���������        *
*          7.2. �� ����� ������� ���������� �������� ����      *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : fibmember1.h                                     *
*  �������� : �������� ������ �������-����� ����� ������       *
*             ������ ������������������ ����� ���������        *
***************************************************************/

#ifndef __FIBMEMBER1_H
#define __FIBMEMBER1_H

#include "member.h"
#include "message.h"

//-------------------------------------------------------------
// ����� FibMember ��������� ��������� �������-����� �����
// ������������������ ����� ��������� ��� ��������� �������
// ������ ����������� ��� ������������
//-------------------------------------------------------------

class FibMember1 : public Member {
  int number;      // ����� ����� ����� (�� ���� �� ���������� n)
  int pred;        // ����������� �������� ����������� �����
  int predPred;    // ����������� �������� ����-����������� �����
  bool accepted1;  // ���������� �������� ��������?
  bool accepted2;  // ����-���������� �������� ��������?

public :
  // ����������� ���������� �����
  FibMember1(int i = 0)
    : number(i), accepted1(false), accepted2(false)
  {}

  FibMember1(const FibMember1 & src)
    : number(src.number), pred(src.pred), predPred(src.predPred),
      accepted1(src.accepted1), accepted2(src.accepted2)
  {}

  // ���������� �������� �� ������ �����������
  Message * generate();
  bool handle(const Message & msg);
};

//-------------------------------------------------------------
// ����� FibMemberFactory ��������� ������� ��� �������� ��������-
// ������ ����� ������������������ ������ n ����� ���������
//-------------------------------------------------------------

class FibMemberFactory1 : public MemberFactory {
public :
  Member * createMember(int i) const { return new FibMember1(i); }
};

#endif
