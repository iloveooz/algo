/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 2. ������� ���������                              *
*          2.4. ���������                                      *
*                                                              *
*  �����       : �. ���������                                  *
*  ����        : Actor.h                                       *
*  ��������    : ����������� ����� ��� ������� ��������        *
*                � ��������� ������ ��� ��������               *
***************************************************************/

#ifndef __ACTOR_H
#define __ACTOR_H

//**************************************************************
// �������� ������ Actor
//**************************************************************

class Actor {
public:
  virtual void action(int & element) = 0;
};

#endif
