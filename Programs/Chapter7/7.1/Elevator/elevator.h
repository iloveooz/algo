/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.1. Схема обмена сообщениями                       *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : elevator.h                                       *
*  Описание : Описание класса, определяющего поведение лифта   *
***************************************************************/

#ifndef __ELEVATOR_H
#define __ELEVATOR_H

#include "dispatcher.h"

//==============================================================
// Классы, описывающие состояние лифта
//==============================================================

enum EState {
  STATE_STOP = 1,   // Лифт стоит
  STATE_UP,         // Лифт поднимается
  STATE_DOWN        // Лифт опускается
};

class ElevatorState {
  EState state;      // Состояние лифта
  int level;         // Этаж, на котором он находится;
  bool doorsOpen;    // Состояние дверей
  int people;        // Количество людей в лифте

public :

  // Конструкторы состояния лифта
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
  // Функции доступа к элементам состояния и изменения состояния
  // реализованы совершенно примитивно. На самом деле изменение
  // состояния должно происходить согласно некоторым "правилам"
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
// Класс ElevatorMessage задает тип сообщений, генерируемых
// лифтом при изменении своего состояния
//==============================================================

class ElevatorMessage : public Message {

public :
  // Следующие константы задают классы сообщений
  // об изменении состояния лифта.
  static const int MSG_STATE_CHANGED = 1;

private :
  // Текущее состояние лифта
  ElevatorState eState;

public :
  // Конструктор
  ElevatorMessage(int msgType, const ElevatorState & state)
    : Message(msgType), eState(state)
  {}

  // Функция доступа к аргументу сообщения
  ElevatorState getState() const { return eState; }
};

//==============================================================
// Класс Elevator реализует поведение лифта. Лифт генерирует
// новое сообщение при изменении состояния и обрабатывает
// сообщения, полученные от потенциальных пассажиров лифта
//==============================================================

class Elevator : public Generator, public Handler {

  // Состояние лифта:
  ElevatorState state;

  // Признак изменения состояния
  bool stateChanged;

public :

  // Конструктор
  Elevator() : stateChanged(false) {}

  // Функция генерации нового сообщения
  Message * generate();

  // Функция обработки полученного от пассажиров сообщения
  bool handle(const Message & msg);
};

#endif
