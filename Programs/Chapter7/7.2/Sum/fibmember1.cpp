/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 7. ����� ����������� � ��������� ���������        *
*          7.2. �� ����� ������� ���������� �������� ����      *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : fibmember1.cpp                                   *
*  �������� : ���������� ��������� �������-����� ����� ������  *
*             ������ ������������������ ����� ���������        *
***************************************************************/

#include "fibmember1.h"
#include "dispatcher.h"
#include "summator.h"
#include <stdlib.h>

//--------------------------------------------------------------
// ��������� ��������� ��������� � ������� ��������, ������ ����
// ����� ����� ���� ������ ���� ��� ��� ������ �������� �����
// ���������� ������ �����. ��������� ����������� ������ ���� ���.
//--------------------------------------------------------------
Message * FibMember1::generate() {
  Message * result = NULL;

  if (number == 0 || number == 1) {
    // ��� ������ ������ ����� �������� ����������� ����� ��
    result = new SumMessage(MemberValue(number, 1));
  } else if (accepted1 && accepted2) {
    // ���������� ����� ����� ��� ���������;
    // ��������� �������� ������� ����� ����� �� �� ������
    result = new SumMessage(MemberValue(number, pred + predPred));
  }
  if (result) {
    Dispatcher::getInstance()->removeGenerator(this);
    Dispatcher::getInstance()->removeHandler(this);
    delete this;
  }
  return result;
}

//--------------------------------------------------------------
// ���������� ��������� �������� ���������� ����� �����, �
// ���� ����� ����� ����� �� 1 ��� 2 ������ ������������
// ������, ���������� ��� ��� ����������� ����������.
//--------------------------------------------------------------
bool FibMember1::handle(const Message & msg) {
  // ��������, �� ���� �� ��� ��������� �������� ���������� ������
  if (accepted1 && accepted2) return false;

  // �������� ������ ���������
  if (msg.getMsgClass() != SumMessage::msgMemberReady) return false;
  const SumMessage & myMsg = (const SumMessage &)msg;

  // ������ � ����������� ��������� ���������
  MemberValue value = myMsg.getValue();
  if (!accepted1 && value.getNumber() == number-1) {
    pred = (int)value.getValue();
    accepted1 = true;
  } else if (!accepted2 && value.getNumber() == number-2) {
    predPred = (int)value.getValue();
    accepted2 = true;
  }

  // �� ���� ������� ��������� ���������� ������ ��� ������� ��� 
  // ������� �������������.
  return false;
}
