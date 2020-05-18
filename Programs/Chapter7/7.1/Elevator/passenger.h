/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 7. ����� ����������� � ��������� ���������        *
*          7.1. ����� ������ �����������                       *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : passenger.h                                      *
*  �������� : �������� ������, ������������� ���������         *
*             ���������� �����                                 *
***************************************************************/

#ifndef __PASSENGER_H
#define __PASSENGER_H

#include <stdlib.h>
#include "message.h"
#include "generator.h"
#include "handler.h"

//==============================================================
// �����, ����������� ��������� ���������
//==============================================================

class PassengerState {
  bool inElevator;   // ��������� ��������� (��� ��� ������ �����)
  int  level;        // ����� �����
  int  wish;         // ���� �������� ����� ������� (���� �����)

public :

  // ������������ ��������� ���������
  PassengerState(bool inElevator = false,
                 int level = 1,
                 int wish = 0)
    : inElevator(inElevator), level(level), wish(wish)
  {}

  PassengerState(const PassengerState & state)
    : inElevator(state.inElevator), level(state.level), wish(state.wish)
  {}

  //=============================================================
  // ������� ������� � ��������� ��������� � ��������� ���������
  // ����������� ���������� ����������. �� ����� ���� ���������
  // ��������� ������ ����������� �������� ��������� "��������"
  //=============================================================
  int getLevel() const { return level; }
  void setLevel(int lev) { level = lev; }
  bool isInElevator() const { return inElevator; }
  void enter() { inElevator = true; }
  void exit() { inElevator = false; }
  int getDestination() const { return wish; }
  void setDestination(int newLevel) { wish = newLevel; }
};

//===============================================================
// ����� PassengerMessage ������ ��� ���������, ������������
// ���������� ��� ������ ������, ����������� � ����� � �.�.
//===============================================================

class PassengerMessage : public Message {

public :
  // ��������� ��������� ������ ������ ��������� ���������
  static const int MSG_DEMAND = 101;
  static const int MSG_DEMAND_CANCELLED = 102;

private :
  // ������� ��������� ���������
  PassengerState pState;

public :
  // �����������
  PassengerMessage(int msgType, const PassengerState & state)
    : Message(msgType), pState(state)
  {}

  // ������� ������� � ��������� ���������
  PassengerState getState() const { return pState; }
};

//===============================================================
// ����� Passenger ��������� ��������� ������ ��������� � ��� ���������.
// ������� ����� ������ ����� ��������� � ������������ ���������
//===============================================================

class Passenger : public Handler, public Generator {
  PassengerState state;
  long wait;              // ����� �������� ������������

public :

  // ����������� ������ ���������
  Passenger() : wait(0) {}
  
  // ������� ��������� � ��������� ���������
  Message * generate(); 
  bool handle(const Message & msg);
};

#endif

