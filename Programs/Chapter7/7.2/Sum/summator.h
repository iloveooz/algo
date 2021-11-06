/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.2. Об одном способе вычисления конечных сумм      *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : summator.h                                       *
*  Описание : Описание абстрактного сумматора конечной суммы   *
***************************************************************/

#ifndef __SUMMATOR_H
#define __SUMMATOR_H

#include "handler.h"
#include "message.h"

//--------------------------------------------------------------
// Класс, определяющий структуру параметра сообщения -
// объекта, содержащего номер и значение члена суммы
//--------------------------------------------------------------

class MemberValue {
  int number;     // номер члена суммы
  double value;   // значение члена суммы

public :

  // Конструкторы:
  MemberValue(int num = 0, double val = 0.0)
    : number(num), value(val) {}
  MemberValue(const MemberValue & src)
    : number(src.number), value(src.value) {}

  // Доступ к элементам параметра сообщения
  int getNumber() const { return number; }
  double getValue() const { return value; }
};

//--------------------------------------------------------------
// Класс, определяющий сообщение о готовности
// очередного члена суммы для суммирования
//--------------------------------------------------------------

class SumMessage : public Message {
public :
  // Определение нового класса сообщения от члена суммы
  static const int msgMemberReady = 1;

private :
  // Параметр сообщения
  MemberValue value;

public :
  // Конструктор сообщения
  SumMessage(const MemberValue & val)
    : Message(msgMemberReady), value(val) {}

  // Доступ к параметру сообщения
  MemberValue getValue() const { return value; }
};

//--------------------------------------------------------------
// Класс, определяющий абстрактный сумматор
//--------------------------------------------------------------

class Summator : public Handler {
  int n;           // количество членов суммы
  int ready;       // количество уже вычисленных членов суммы
  double sum;      // накапливаемая сумма

public :
  // Конструктор сумматора задает количество ожидаемых им членов суммы
  Summator(int n) : n(n), ready(0), sum(0) {}

  // Метод обработки сообщения
  bool handle(const Message & msg);

  // Результат суммирования
  double getResult() const { return sum; }
};

#endif
