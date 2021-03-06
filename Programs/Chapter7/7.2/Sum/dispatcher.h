/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 7. ����� ����������� � ��������� ���������        *
*          7.2. �� ����� ������� ���������� �������� ����      *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : dispatcher.h                                     *
*  �������� : �������� ������, ������������� ���������         *
*             ���������                                        *
***************************************************************/

#ifndef __DISPATCHER_H
#define __DISPATCHER_H

#include "list.h"
#include "generator.h"
#include "handler.h"
#include "message.h"

//=============================================================
// ����� Dispatcher ��������� ��������� ������� ���������
//=============================================================

class Dispatcher {
public :
  static const int msgQuit = -1;  // ����� ������������ ���������

private:  
  List<Generator *> generators;   // ������ �����������
  List<Handler *> handlers;       // ������ ������������
  List<Message *> messages;       // ������� ���������
  
  //=================================================
  // ���������� "��������"
  //=================================================
  static Dispatcher * dispatcher;
  
  Dispatcher() {}
  
public :

  static Dispatcher * getInstance() {
    if (dispatcher == NULL) {
      dispatcher = new Dispatcher();
    }
    return dispatcher;
  }
  
  //=================================================
  //  ������� ��� ������ �� ������� ������������
  //=================================================
  void addHandlerHead(Handler * hnd) {
    handlers.addFirst(hnd);
  }
  
  void addHandlerTail(Handler * hnd) {
    handlers.addLast(hnd);
  }
  
  Handler * removeHandler(Handler * hnd);
  
  //=================================================
  //  ������� ��� ������ �� ������� �����������
  //=================================================
  void addGenerator(Generator * gen) {
    generators.addLast(gen);
  }
  
  Generator * removeGenerator(Generator * gen);
  
  //=================================================
  //  �������� ��������� � ������� ���������
  //=================================================
  void sendMessage(Message * msg) {
    messages.addLast(msg);
  }
  
  //=================================================
  //  �������� ���� ������ ���������� ���������
  //=================================================
  void run();
  
  //=================================================
  //  ������� ���� �������
  //=================================================
  void clear() {
    messages.destroy();
    generators.destroy();
    handlers.destroy();
  }
};

#endif
