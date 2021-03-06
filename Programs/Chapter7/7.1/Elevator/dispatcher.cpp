/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 7. ����� ����������� � ��������� ���������        *
*          7.1. ����� ������ �����������                       *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : dispatcher.h                                     *
*  �������� : �������� ������, ������������� ���������         *
*             ���������                                        *
***************************************************************/

#include "dispatcher.h"
#include "iterator.h"

//======================================================
//  �������� ��������� ����������� ��������� �� ������:
//======================================================
  
Handler * Dispatcher::removeHandler(Handler * hnd) {
  // ��������� ������ ����� hnd, ���� ����������
  // ��������� ������ � ������, � NULL, ���� ��� ��� ���
  Handler * result = NULL;

  // �������� ������ ������������ ���������:
  Iterator<Handler *> *it = handlers.iterator();

  // ���� ������ � �������� ��������� ����������� ���������
  while (it->hasMoreElements()) {
    if (**it == hnd) {
      // ���������� ��������� ������; �� ��������� �� ������
      it->remove();
      result = hnd;
      break;
    } else {
      ++*it;
    }
  }
  delete it;
  return result;
}
  
//======================================================
//  �������� ��������� ���������� ��������� �� ������:
//======================================================
  
Generator * Dispatcher::removeGenerator(Generator * gen) {
  // ��������� ������ ����� gen, ���� ���������
  // ��������� ������ � ������, � NULL, ���� ��� ��� ���
  Generator * result = NULL;

  // �������� ������ ����������� ���������:
  Iterator<Generator *> *it = generators.iterator();

  // ���� ������ � �������� ��������� ���������� ���������
  while (it->hasMoreElements()) {
    if (**it == gen) {
      // ��������� ��������� ������; �� ��������� �� ������
      it->remove();
      result = gen;
      break;
    } else {
      ++*it;
    }
  }
  delete it;
  return result;
}

//======================================================
//  �������� ���� ������ ���������� ���������
//======================================================

void Dispatcher::run() {
  // ���� ����� ����������� ������ �� ��������� ��������� �������
  for (;;) {
    //----- 1. ���������� ����� �����-���� ���������
    Message * msg = NULL;
    if (!messages.isEmpty()) {
      // ������� ��������� �� ����� � ����� ��������� �� ���
      msg = messages.head();
      messages.remove();
    } else {
      // ������� ��������� �����, ����������� ����������
      Iterator<Generator *> * it = generators.iterator();
      while (it->hasMoreElements()) {
        Generator * generator = **it;
        if (msg = generator->generate()) {
          break;
        }
        ++*it;
      }
    }
    
    if (msg) {
      //----- 2. �������� ���������
      if (msg->getMsgClass() == msgQuit) {
        // ������������� ������ ����������,
        // � ������ � ��� � ���� ���������
        break;
      }
    
      //----- 3. �������� ��������� �� ���������
      Iterator<Handler *> * it = handlers.iterator();
      while (it->hasMoreElements()) {
        Handler * handler = **it;
        if (handler->handle(*msg)) {
          break;
        }
        ++*it;
      }
    }
  }
}
