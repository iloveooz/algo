/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.2. Об одном способе вычисления конечных сумм      *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : dispatcher.h                                     *
*  Описание : Описание класса, определяющего диспетчер         *
*             сообщений                                        *
***************************************************************/

#ifndef __DISPATCHER_H
#define __DISPATCHER_H

#include "list.h"
#include "generator.h"
#include "handler.h"
#include "message.h"

//=============================================================
// Класс Dispatcher реализует обработку очереди сообщений
//=============================================================

class Dispatcher {
public :
  static const int msgQuit = -1;  // Класс стандартного сообщения

private:  
  List<Generator *> generators;   // Список генераторов
  List<Handler *> handlers;       // Список обработчиков
  List<Message *> messages;       // Очередь сообщений
  
  //=================================================
  // Реализация "одиночки"
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
  //  Функции для работы со списком обработчиков
  //=================================================
  void addHandlerHead(Handler * hnd) {
    handlers.addFirst(hnd);
  }
  
  void addHandlerTail(Handler * hnd) {
    handlers.addLast(hnd);
  }
  
  Handler * removeHandler(Handler * hnd);
  
  //=================================================
  //  Функции для работы со списком генераторов
  //=================================================
  void addGenerator(Generator * gen) {
    generators.addLast(gen);
  }
  
  Generator * removeGenerator(Generator * gen);
  
  //=================================================
  //  Передача сообщения в очередь сообщений
  //=================================================
  void sendMessage(Message * msg) {
    messages.addLast(msg);
  }
  
  //=================================================
  //  Основной цикл работы диспетчера сообщений
  //=================================================
  void run();
  
  //=================================================
  //  Очистка всех списков
  //=================================================
  void clear() {
    messages.destroy();
    generators.destroy();
    handlers.destroy();
  }
};

#endif
