/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 7. ����� ����������� � ��������� ���������        *
*          7.1. ����� ������ �����������                       *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : elevator.h                                       *
*  �������� : �������� ������, ������������� ��������� �����   *
***************************************************************/

#ifndef __ELEVATOR_H
#define __ELEVATOR_H

#include "dispatcher.h"

//==============================================================
// ������, ����������� ��������� �����
//==============================================================

enum EState {
  STATE_STOP = 1,   // ���� �����
  STATE_UP,         // ���� �����������
  STATE_DOWN        // ���� ����������
};

class ElevatorState {
  EState state;      // ��������� �����
  int level;         // ����, �� ������� �� ���������;
  bool doorsOpen;    // ��������� ������
  int people;        // ���������� ����� � �����

public :

  // ������������ ��������� �����
  ElevatorState(EState state = STATE_STOP,
                int level = 1,
                bool doorsOpen = true,
                int people = 0)
    : state(state), level(level), doorsOpen(doorsOpen), people(people)
  {}

  ElevatorState(const ElevatorState & state)
    : state(state.state), level(state.level),
      doorsOpen(state.doorsOpen), people(state.people)
  {}

  //=============================================================
  // ������� ������� � ��������� ��������� � ��������� ���������
  // ����������� ���������� ����������. �� ����� ���� ���������
  // ��������� ������ ����������� �������� ��������� "��������"
  //=============================================================
  EState getState() const { return state; }
  void setState(EState st) { state = st; }
  int getLevel() const { return level; }
  void setLevel(int lev) { level = lev; }
  bool isDoorsOpen() const { return doorsOpen; }
  void setDoorsOpen() { doorsOpen = true; }
  void setDoorsClose() { doorsOpen = false; }
  int getPeople() const { return people; }
  void setPeople(int pple) { people = pple; }
};

//==============================================================
// ����� ElevatorMessage ������ ��� ���������, ������������
// ������ ��� ��������� ������ ���������
//==============================================================

class ElevatorMessage : public Message {

public :
  // ��������� ��������� ������ ������ ���������
  // �� ��������� ��������� �����.
  static const int MSG_STATE_CHANGED = 1;

private :
  // ������� ��������� �����
  ElevatorState eState;

public :
  // �����������
  ElevatorMessage(int msgType, const ElevatorState & state)
    : Message(msgType), eState(state)
  {}

  // ������� ������� � ��������� ���������
  ElevatorState getState() const { return eState; }
};

//==============================================================
// ����� Elevator ��������� ��������� �����. ���� ����������
// ����� ��������� ��� ��������� ��������� � ������������
// ���������, ���������� �� ������������� ���������� �����
//==============================================================

class Elevator : public Generator, public Handler {

  // ��������� �����:
  ElevatorState state;

  // ������� ��������� ���������
  bool stateChanged;

public :

  // �����������
  Elevator() : stateChanged(false) {}

  // ������� ��������� ������ ���������
  Message * generate();

  // ������� ��������� ����������� �� ���������� ���������
  bool handle(const Message & msg);
};

#endif
