/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.1. Схема обмена сообщениями                       *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : passenger.h                                      *
*  Описание : Описание класса, определяющего поведение         *
*             пассажиров лифта                                 *
***************************************************************/

#ifndef __PASSENGER_H
#define __PASSENGER_H

#include <stdlib.h>
#include "message.h"
#include "generator.h"
#include "handler.h"

//==============================================================
// Класс, описывающий состояние пассажира
//==============================================================

class PassengerState {
  bool inElevator;   // Состояние пассажира (вне или внутри лифта)
  int  level;        // Номер этажа
  int  wish;         // Куда пассажир хочет попасть (если хочет)

public :

  // Конструкторы состояния пассажира
  PassengerState(bool inElevator = false,
                 int level = 1,
                 int wish = 0)
    : inElevator(inElevator), level(level), wish(wish)
  {}

  PassengerState(const PassengerState & state)
    : inElevator(state.inElevator), level(state.level), wish(state.wish)
  {}

  //=============================================================
  // Функции доступа к элементам состояния и изменения состояния
  // реализованы совершенно примитивно. На самом деле изменение
  // состояния должно происходить согласно некоторым "правилам"
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
// Класс PassengerMessage задает тип сообщений, генерируемых
// пассажиром при подаче заявок, перемещение в лифте и т.п.
//===============================================================

class PassengerMessage : public Message {

public :
  // Следующие константы задают классы сообщений пассажира
  static const int MSG_DEMAND = 101;
  static const int MSG_DEMAND_CANCELLED = 102;

private :
  // Текущее состояние пассажира
  PassengerState pState;

public :
  // Конструктор
  PassengerMessage(int msgType, const PassengerState & state)
    : Message(msgType), pState(state)
  {}

  // Функция доступа к аргументу сообщения
  PassengerState getState() const { return pState; }
};

//===============================================================
// Класс Passenger описывает структуру модели пассажира и его поведение.
// Объекты этого класса могут создавать и обрабатывать сообщения
//===============================================================

class Passenger : public Handler, public Generator {
  PassengerState state;
  long wait;              // Время ожидания обслуживания

public :

  // Конструктор нового пассажира
  Passenger() : wait(0) {}
  
  // Функции генерации и обработки сообщений
  Message * generate(); 
  bool handle(const Message & msg);
};

#endif

